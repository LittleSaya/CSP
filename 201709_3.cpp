#include "csptest.h"
#include "SimpleJSONObject.h"
#include <iostream>
#include <string>
#include <vector>

// There are BUGs
// please comment out evey cout statement in this page

void f_201709_3()
{
	int lineN = 0, queryN = 0;
	std::cin >> lineN >> queryN;
	while (std::cin.get() != '\n')
	{ }
	
	std::string raw, line;
	for (int i = 0; i < lineN; ++i)
	{
		std::getline(std::cin, line);
		raw += (line + '\n');
	}
	
	std::vector<std::string> queries;
	for (int i = 0; i < queryN; ++i)
	{
		std::cin >> line;
//		std::getline(std::cin, line);
		queries.push_back(line);
//		std::cout << "query read: " << line << std::endl;
	}
	
//	std::cout << "raw input:\n" << raw << std::endl;
	SimpleJSONObject jobj(raw, raw.find_first_of('{'));
//	jobj.print();
	
	for (int i = 0; i < queryN; ++i)
	{
		SimpleJSONObject *p = jobj.query(queries[i]);
//		std::cout << "result of \"" << queries[i] << "\" is:" << std::endl;
		if (p == NULL)
		{ std::cout << "NOTEXIST" << std::endl; }
		else if (STR_T == p->getType())
		{ std::cout << "STRING " << *((PString_t)(p->getValuePointer())) << std::endl; }
		else if (LST_T == p->getType())
		{ std::cout << "OBJECT" << std::endl; }
		else
		{ std::cout << "NOTEXIST???" << std::endl; }
	}
}
