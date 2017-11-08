#include "csptest.h"
#include <string>
#include <iostream>
#include <vector>

namespace Q201703_3
{

typedef std::vector<std::string>::size_type VSize;
typedef std::string::size_type SSize;
typedef std::vector<std::string> TextType;

enum BlockFormat
{
	PARA_BLOCK,
	HEAD_BLOCK,
	ULIST_BLOCK,
};

enum InlineFormat
{
	EMPH_INLINE,
	LINK_INLINE,
};

// find next bolck, return true when success, return false when fail
bool findNextBlock(const TextType &text, VSize &blockPos, VSize &blockLineCount);
// first strp: block process
// textIn: original markdown text
// textOut: half done, still need line process
void blockProcess(const TextType &textIn, const VSize blockPos, const VSize blockLineCount, TextType &textOut);
void blockProcess_para(const TextType &textIn, const VSize blockPos, const VSize blockLineCount, TextType &textOut);
void blockProcess_head(const TextType &textIn, const VSize blockPos, const VSize blockLineCount, TextType &textOut);
void blockProcess_ulist(const TextType &textIn, const VSize blockPos, const VSize blockLineCount, TextType &textOut);
// second step: line process
// before: the line before process
// after: the line after process
// return: true if the line needs to be processed and it was done successfully, false when otherwise
bool lineProcess1(const std::string &before, std::string &after);
// a simpler line process function
std::string lineProcess2(const std::string &before);
// does this line need a "lineProcess"?
SSize isSpecialLine(const std::string &line);
// return the index of the next line mark, similiar to "isSpecialLine()"
SSize nextLineMark(const std::string &line, SSize pos);
// make a link, the link starts at line[pos]
// return: the index of the char right after the link. (right after the ')')
SSize makeLink(const std::string &line, const SSize pos, std::string &result);

// tell the type of the block
BlockFormat getBlockType(const TextType &text, const VSize blockPos, const VSize blockLineCount);

void f_201703_3()
{
	using std::cin;
	using std::cout;
	using std::endl;
	using std::string;
	using std::vector;
	
	TextType inputText;
	TextType outputText;// result of "lineProcess"
	
	// read input
	string line;
	while (std::getline(cin, line)) { inputText.push_back(line); }
	
//	cout << endl << "inputText:" << endl;
//	for (VSize i = 0; i < inputText.size(); ++i)
//		cout << i << ":\t" << inputText[i] << endl;
	
	// make block, do block process
	VSize blockPos = 0, blockLineCount = 0;
	while (findNextBlock(inputText, blockPos, blockLineCount))
	{
		blockProcess(inputText, blockPos, blockLineCount, outputText);
	}
	
	// output
	for (VSize i = 0; i < outputText.size(); ++i)
		cout << outputText[i] << endl;
}

bool findNextBlock(const TextType &text, VSize &blockPos, VSize &blockLineCount)
{
	// skip current block
	blockPos += blockLineCount;
	blockLineCount = 0;
	// locate the head of next block
	while (blockPos < text.size() && text[blockPos].empty()) { ++blockPos; }
	if (blockPos >= text.size()) { return false; }// cannot find the next block
	else
	{
		blockLineCount = 1;
		while (blockPos + blockLineCount < text.size() && !text[blockPos + blockLineCount].empty()) { ++blockLineCount; }
	}
	return true;
}

void blockProcess(const TextType &textIn, const VSize blockPos, const VSize blockLineCount, TextType &textOut)
{
	switch (getBlockType(textIn, blockPos, blockLineCount))
	{
		case HEAD_BLOCK:
			blockProcess_head(textIn, blockPos, blockLineCount, textOut);
			break;
		case ULIST_BLOCK:
			blockProcess_ulist(textIn, blockPos, blockLineCount, textOut);
			break;
		case PARA_BLOCK:
			blockProcess_para(textIn, blockPos, blockLineCount, textOut);
			break;
		default:
			std::cout << "unrecognizable block type" << std::endl;
	}
}

void blockProcess_para(const TextType &textIn, const VSize blockPos, const VSize blockLineCount, TextType &textOut)
{
	textOut.push_back(std::string("<p>") + lineProcess2(textIn[blockPos]));
	for (VSize i = blockPos + 1; i < blockPos + blockLineCount; ++i)
		textOut.push_back(lineProcess2(textIn[i]));
	textOut.back() += std::string("</p>");
}

void blockProcess_head(const TextType &textIn, const VSize blockPos, const VSize blockLineCount, TextType &textOut)
{
	SSize numSignCount = 1;
	while (numSignCount < textIn[blockPos].size() && textIn[blockPos][numSignCount] == '#') { ++numSignCount; }
	SSize headPos = numSignCount;
	while (headPos < textIn[blockPos].size() && textIn[blockPos][headPos] == ' ') { ++headPos; }
	std::string line = std::string("<h") + (char)('0' + numSignCount) + ">" +
		lineProcess2(textIn[blockPos].substr(headPos)) +
		std::string("</h") + (char)('0' + numSignCount) + ">";
	textOut.push_back(line);
}

void blockProcess_ulist(const TextType &textIn, const VSize blockPos, const VSize blockLineCount, TextType &textOut)
{
	textOut.push_back(std::string("<ul>"));
	std::string li_a("<li>"), li_b("</li>");
	for (VSize i = blockPos, itemPos = 1; i < blockPos + blockLineCount; ++i, itemPos = 1)
	{
		while (itemPos < textIn[i].size() && textIn[i][itemPos] == ' ') { ++itemPos; }
		textOut.push_back(std::string("<li>") + lineProcess2(textIn[i].substr(itemPos)) + "</li>");
	}
	textOut.push_back(std::string("</ul>"));
}

std::string lineProcess2(const std::string &before)
{
	std::string result;
	SSize lastPos = 0, currentPos = 0;
	bool emFlag = false;
	if (isSpecialLine(before) == std::string::npos) { return before; }
	else
	{
		while ((currentPos = nextLineMark(before, lastPos)) != std::string::npos)
		{
			// now currentPos points to a line mark
			// load normal part into "result"
			result += before.substr(lastPos, currentPos - lastPos);
			// put the HTML mark according to the Markdown mark
			switch (before[currentPos])
			{
				case '_':
					if (!emFlag)// it is a "left part of an emphasize"
					{
						emFlag = true;// when next time we meet a '_', we know it is a "right part"
						result += "<em>";
					}
					else// right part
					{
						emFlag = false;
						result += "</em>";
					}
					lastPos = currentPos = currentPos + 1;
					break;
				case '[':// make a link
					{
						std::string link;
						lastPos = currentPos = makeLink(before, currentPos, link);
						// push the link string into the "result"
						result += link;
						break;
					}
				default:
					break;
			}
		}
		// no other linemarks, push remaining characters into "result"
		result += before.substr(lastPos);
		return result;
	}
}

SSize isSpecialLine(const std::string &line)
{
	return line.find_first_of("_[");
}

SSize nextLineMark(const std::string &line, SSize pos)
{
	return line.find_first_of("_[]", pos);
}

SSize makeLink(const std::string &line, const SSize pos, std::string &result)
{
	// make the url
	std::string url = line.substr(
		line.find_first_of('(', pos) + 1,// begin of the url
		line.find_first_of(')', pos) - line.find_first_of('(', pos) - 1);// the length of the url = index of ')' - index of '(' - 1
	// make the text part of the link
	std::string text;
	bool emFlag = false;
	for (SSize i = pos + 1; line[i] != ']'; ++i)
	{
		if (line[i] != '_') { text.push_back(line[i]); }
		else
		{
			if (!emFlag)
			{
				text += "<em>";
				emFlag = true;
			}
			else
			{
				text += "</em>";
				emFlag = false;
			}
		}
	}
	// make the result
	result = std::string("<a href=\"") + url + "\">" + text + "</a>";
	return line.find_first_of(')', pos) + 1;
}

BlockFormat getBlockType(const TextType &text, const VSize blockPos, const VSize blockLineCount)
{
	switch (text[blockPos][0])
	{
		case '#':
			return HEAD_BLOCK;
		case '*':
			return ULIST_BLOCK;
		default:
			return PARA_BLOCK;
	}
}

}
