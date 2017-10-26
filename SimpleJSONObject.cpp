#include "SimpleJSONObject.h"
#include <cctype>
#include <list>
#include <string>
#include <iterator>

void SimpleJSONObject::print() const
{
	print_internal(*this, 0, true);
}

SimpleJSONObject *SimpleJSONObject::query(const std::string &p_name)
{
//	std::cout << "query() called" << std::endl;
	if (LST_T != type)
	{
		std::cout << "LST_T != type" << std::endl;
		return NULL;
	}
	size_t dotIdx = p_name.find_first_of('.');
	bool multi = (dotIdx != std::string::npos);
	if (!multi)
	{
//		std::cout << "not multi " << std::endl;
		std::list<SimpleJSONObject>::iterator iter = ((PList_t)(valuePointer))->begin();
		std::list<SimpleJSONObject>::iterator iterEnd = ((PList_t)(valuePointer))->end();
		while (iter != iterEnd)
		{
			if (iter->getName().compare(p_name) == 0)
			{ return &(*iter); }
			++iter;
		}
//		std::cout << "not found" << std::endl;
		return NULL;
	}
	else
	{
//		std::cout << "multi " << std::endl;
		std::string mother(p_name.substr(0, dotIdx));
		std::string child(p_name.substr(dotIdx + 1));
		std::list<SimpleJSONObject>::iterator iter = ((PList_t)(valuePointer))->begin();
		std::list<SimpleJSONObject>::iterator iterEnd = ((PList_t)(valuePointer))->end();
		while (iter != iterEnd)
		{
			if (iter->getName().compare(mother) == 0)
			{ return iter->query(child); }
			++iter;
		}
//		std::cout << "not found" << std::endl;
		return NULL;
	}
}

PList_t SimpleJSONObject::buildFromString(const std::string &raw, const size_t begIdx)
{
	// a json object should starts with a '{'
	if (raw[begIdx] != '{')
	{
		std::cout << "raw[begIdx] != '{' in SimpleJSONObject::buildFromString()" << std::endl;
		return NULL;
	}
	// else, read it
	return createListValue(raw, begIdx, NULL);
}

PList_t SimpleJSONObject::createListValue(const std::string &raw, const size_t begIdx, size_t *endIdx)
{
	PList_t plist = new std::list<SimpleJSONObject>();
	size_t iter = begIdx;
	char ch = '\0';
	int type = UDE_T;
	std::string name;
	void *valuePointer;
	while ((ch = moveToNextChar(raw, iter)) != ' ')
	{
		if (ch == '\"')// a name
		{
//			std::cout << "name \"";
			name = createName(raw, iter, &iter);
//			std::cout << name << "\" created." << std::endl;
		}
		else if (ch == ':')// a value
		{
			if ((ch = moveToNextChar(raw, iter)) == '\"')// a string value
			{
				type = STR_T;
				valuePointer = createStringValue(raw, iter, &iter);
//				std::cout << "string ";
			}
			if (ch == '{')// a list value
			{
				type = LST_T;
				valuePointer = createListValue(raw, iter, &iter);
//				std::cout << "list ";
			}
//			std::cout << "value created." << std::endl;
		}
		else if (ch == ',')// we complete a name-value pair
		{
			plist->push_back(SimpleJSONObject(type, name));
			plist->back().setValuePointer(valuePointer);
			valuePointer = NULL;
		}
		else if (ch == '}')
		{
			if (type != UDE_T)// we complete the last name-value pair
			{
				plist->push_back(SimpleJSONObject(type, name));
				plist->back().setValuePointer(valuePointer);
				valuePointer = NULL;
			}
			break;
		}
		else
		{
			std::cout << "unexpected char \'" << (int)ch << "\'" << std::endl;
		}
	}
	if (ch == ' ')
	{
		std::cout << "miss \'}\' in SimpleJSONObject::createListValue()" << std::endl;
		delete plist;
		plist = NULL;
	}
	if (endIdx != NULL)
	{ *endIdx = iter; }
	return plist;
}

std::string SimpleJSONObject::createName(const std::string &raw, const size_t begIdx, size_t *endIdx)
{
	std::string name;
	size_t iter = begIdx;
	char ch = '\0';
	while ((ch = moveToNextChar(raw, iter)) != ' ' && ch != '\"')
	{
		if (ch == '\\')// escape
		{
			ch = moveToNextChar(raw, iter);
			name += ch;
		}
		else
		{ name += ch; }
	}
	if (ch == ' ')
	{ std::cout << "miss \'\'\' in SimpleJSONObject::createName()" << std::endl; }
	if (endIdx != NULL)
	{ *endIdx = iter; }
	return name;
}

PString_t SimpleJSONObject::createStringValue(const std::string &raw, const size_t begIdx, size_t *endIdx)
{
	// todo optimize
	return new std::string(createName(raw, begIdx, endIdx));
}

char SimpleJSONObject::moveToNextChar(const std::string &str, size_t &iter)
{
	while (true)
	{
		if (++iter >= str.size())
		{ return ' '; }
		if (!isblank(str[iter]) && str[iter] != '\r' && str[iter] != '\n')
		{ return str[iter]; }
	}
}

void SimpleJSONObject::print_internal(const SimpleJSONObject &obj, const int indent, bool last) const
{
	if (NULL == obj.valuePointer)
	{
		std::cout << "find NULL pointer at indent level (" << indent << ") in SimpleJSONObject::print_internal()" << std::endl;
		return;
	}
	if (STR_T == obj.type)
	{
		printIndent(indent);
		std::cout << '\"' << obj.name << "\" : \"" << *((PString_t)(obj.valuePointer)) << "\"";
		if (!last)
		{ std::cout.put(','); }
		std::cout << std::endl;
	}
	else if (LST_T == obj.type)
	{
		printIndent(indent);
		std::cout << '\"' << obj.name << "\" :" << std::endl;
		printIndent(indent);
		std::cout.put('{') << std::endl;
		std::list<SimpleJSONObject>::iterator iter = ((PList_t)(obj.valuePointer))->begin();
		std::list<SimpleJSONObject>::iterator iterBack = --(((PList_t)(obj.valuePointer))->end());
		while (iter != iterBack)
		{
			print_internal(*iter, indent + 1, false);
			++iter;
		}
		if (iter != ((PList_t)(obj.valuePointer))->end())
		{ print_internal(*iter, indent + 1, true); }
		printIndent(indent);
		std::cout.put('}');
		if (!last)
		{ std::cout.put(','); }
		std::cout << std::endl;
	}
}

void SimpleJSONObject::printIndent(const int indent) const
{
	size_t widthSave = std::cout.width();
	char fillSave = std::cout.fill();
	std::cout.width(4 * indent);
	std::cout.fill(' ');
	std::cout << ' ';
	std::cout.width(widthSave);
	std::cout.fill(fillSave);
}
