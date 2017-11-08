#include "csptest.h"
#include <list>
#include <vector>
#include <iostream>
#include <string>

namespace Q201609_3
{

enum ActionType
{
	S,
	A,
	E
};

struct Action
{
	int type;
	std::vector<int> args;
	
	Action() : type(0), args()
	{
	}
};

struct Unit
{
	int H;
	int A;
	
	Unit(int h, int a) : H(h), A(a)
	{
	}
};

int actionN;
std::vector<Action> actionVec;

std::list<Unit> unitLists[2];

bool seq = 0;

void init();
void process();
void output();

void printList(std::list<Unit>& l)
{
	std::list<Unit>::iterator i = l.begin();
	while (l.end() != i)
	{
		std::cout << i->H << ' ';
		++i;
	}
	std::cout << std::endl;
}

void f_201609_3()
{
	init();
	
//	printList(unitLists[0]);
//	printList(unitLists[1]);
//	std::cout << std::endl;
	
	process();
	output();
}

void init()
{
//	std::cout << "input in" << std::endl;
	// actionN and actionVec
	std::cin >> actionN;
//	std::cout << "actionN=" << actionN << std::endl;
	for (int i = 0; i < actionN; ++i)
	{
//		std::cout << "before init \"act\"" << std::endl;
		Action act;
//		std::cout << "\"act\" init" << std::endl;
		
		std::string actStr;
//		std::cout << "\"actStr\" init" << std::endl;
		
		std::cin >> actStr;
//		std::cout << actStr << std::endl;
		
		switch (actStr[0])
		{
		case 's':
			{
//				std::cout << "s1" << std::endl;
				
				act.type = S;
				for (int j = 0; j < 3; ++j)
				{
					int val = 0;
					std::cin >> val;
					act.args.push_back(val);
				}
				
//				std::cout << "s2" << std::endl;
				break;
			}
		case 'a':
			{
//				std::cout << "a1" << std::endl;
				
				act.type = A;
				for (int j = 0; j < 2; ++j)
				{
					int val = 0;
					std::cin >> val;
					act.args.push_back(val);
				}
				
//				std::cout << "a2" << std::endl;
				break;
			}
		case 'e':
			{
//				std::cout << "e1" << std::endl;
				
				act.type = E;
				
//				std::cout << "e2" << std::endl;
				break;
			}
		default:
			{
//				std::cout << "Undefined action: " << actStr << std::endl;
				break;
			}
		}
//		std::cout << "before push" << std::endl;
		actionVec.push_back(act);
//		std::cout << "after push" << std::endl;
//		std::cout << std::endl;
	}
	// unitLst1 and unitLst2
	unitLists[0].push_back(Unit(30, 0));
	unitLists[1].push_back(Unit(30, 0));
//	std::cout << "input out" << std::endl;
}

void process()
{
	std::vector<Action>::iterator aiter = actionVec.begin();
	while (actionVec.end() != aiter)
	{
		switch (aiter->type)
		{
		case S:
			{
//				std::cout << "S: arg0=" << aiter->args[0] << ", arg1=" << aiter->args[1] << ", arg2=" << aiter->args[2] << std::endl;
				std::list<Unit>::iterator uiter = unitLists[seq].begin();
				for (int i = 0; i < aiter->args[0]; ++i)
				{
					++uiter;
				}
				unitLists[seq].insert(uiter, Unit(aiter->args[2], aiter->args[1]));
				break;
			}
		case A:
			{
//				std::cout << "A: arg0=" << aiter->args[0] << ", arg1=" << aiter->args[1] << std::endl;
				std::list<Unit>::iterator atkUnit = unitLists[seq].begin();
				for (int i = 0; i < aiter->args[0]; ++i)
				{
					++atkUnit;
				}
				std::list<Unit>::iterator defUnit = unitLists[!seq].begin();
				for (int i = 0; i < aiter->args[1]; ++i)
				{
					++defUnit;
				}
				atkUnit->H -= defUnit->A;
				defUnit->H -= atkUnit->A;
				if (unitLists[seq].begin() != atkUnit && atkUnit->H <= 0)
				{ 
					unitLists[seq].erase(atkUnit);
				}
				if (unitLists[!seq].begin() != defUnit && defUnit->H <= 0)
				{
					unitLists[!seq].erase(defUnit);
				}
				break;
			}
		case E:
			{
//				std::cout << "E" << std::endl;
				seq = !seq;
				break;
			}
		default:
			{
//				std::cout << "Undefined action type: " << aiter->type << std::endl;
			}
		}
		++aiter;
	
//		printList(unitLists[0]);
//		printList(unitLists[1]);
//		std::cout << std::endl;
	}
}

void output()
{
	// whois winner
	if (unitLists[0].begin()->H <= 0)
	{
		std::cout << -1 << std::endl;
	}
	else if (unitLists[1].begin()->H <= 0)
	{
		std::cout << 1 << std::endl;
	}
	else
	{
		std::cout << 0 << std::endl;
	}
	// first
	std::cout << unitLists[0].begin()->H << std::endl;
	int followCnt1 = unitLists[0].size() - 1;
	std::cout << followCnt1 << ' ';
	std::list<Unit>::iterator unitIter1 = unitLists[0].begin();
	for (int i = 0; i < followCnt1; ++i)
	{
		++unitIter1;
		std::cout << unitIter1->H << ' ';
	}
	std::cout << std::endl;
	// second
	std::cout << unitLists[1].begin()->H << std::endl;
	int followCnt2 = unitLists[1].size() - 1;
	std::cout << followCnt2 << ' ';
	std::list<Unit>::iterator unitIter2 = unitLists[1].begin();
	for (int i = 0; i < followCnt2; ++i)
	{
		++unitIter2;
		std::cout << unitIter2->H << ' ';
	}
	std::cout << std::endl;
}

}
