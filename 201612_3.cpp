#include "csptest.h"
#include "UserAndPriv.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

namespace Q201612_3
{

using namespace UnP;

int privN = 0, roleN = 0, userN = 0, queryN = 0;
std::vector<Priv> allPrivs;
std::vector<Role> allRoles;
std::vector<User> allUsers;
std::vector<Query> allQueries;

Priv createPriv();
Role createRole();
User createUser();
Query createQuery();
void execute();
std::vector<Priv> getUserPriv(const User &u);

void f_201612_3()
{
	// p and P
	std::cin >> privN;
	for (int i = 0; i < privN; ++i)
	{	allPrivs.push_back(createPriv()); }
	
	// r and R
	std::cin >> roleN;
	for (int i = 0; i < roleN; ++i)
	{	allRoles.push_back(createRole()); }
	
	// u and U
	std::cin >> userN;
	for (int i = 0; i < userN; ++i)
	{	allUsers.push_back(createUser()); }
	
	// q and Q
	std::cin >> queryN;
	for (int i = 0; i < queryN; ++i)
	{	allQueries.push_back(createQuery()); }
	
	// do query
	execute();
}

Priv createPriv()
{
	Priv p;
	std::string str;
	std::cin >> str;
	size_t idx = str.find_first_of(':');
	if (std::string::npos != idx)
	{
		p.type = P_LV;
		p.name = str.substr(0, idx);
		p.lv = std::atoi(str.substr(idx + 1).c_str());
	}
	else
	{
		p.type = P_NOLV;
		p.name = str;
	}
	return p;
}

Role createRole()
{
	Role r;
	std::cin >> r.name;
	int pn = 0;
	std::cin >> pn;
	for (int i = 0; i < pn; ++i)
	{	r.privList.push_back(createPriv()); }
	return r;
}

User createUser()
{
	User u;
	std::cin >> u.name;
	int rn = 0;
	std::cin >> rn;
	for (int i = 0; i < rn; ++i)
	{
		std::string rname;
		std::cin >> rname;
		u.roleList.push_back(rname);
	}
	return u;
}

Query createQuery()
{
	Query q;
	std::cin >> q.uname;
	q.priv = createPriv();
	return q;
}

void execute()
{
	for (int qi = 0; qi < allQueries.size(); ++qi)
	{
		User u;
		for (int ui = 0; ui < allUsers.size(); ++ui)
		{
			if (allQueries[qi].uname == allUsers[ui].name)
			{
				u = allUsers[ui];
				break;
			}
		}
		std::vector<Priv> privs = getUserPriv(u);
		bool success = false;
		bool typeNum = false;
		int maxNum = 0;
		for (int pi = 0; pi < privs.size(); ++pi)
		{
			if (allQueries[qi].priv.name == privs[pi].name)
			{
				if (P_NOLV == allQueries[qi].priv.type)
				{
					if (P_NOLV == privs[pi].type)
					{
						std::cout << "true" << std::endl;
						success = true;
						break;
					}
					else
					{
						maxNum = (privs[pi].lv > maxNum ? privs[pi].lv : maxNum);
						typeNum = true;
					}
				}
				else
				{
					if (P_LV == privs[pi].type && privs[pi].lv >= allQueries[qi].priv.lv)
					{
						std::cout << "true" << std::endl;
						success = true;
						break;
					}
				}
			}
		}
		if (typeNum)
		{	std::cout << maxNum << std::endl; }
		else if (!success)
		{	std::cout << "false" << std::endl; }
	}
}

std::vector<Priv> getUserPriv(const User &u)
{
	std::vector<Priv> privs;
	for (int ri = 0; ri < u.roleList.size(); ++ri)
	{
		for (int ri2 = 0; ri2 < allRoles.size(); ++ri2)
		{
			if (u.roleList[ri] == allRoles[ri2].name)
			{
				for (int pi = 0; pi < allRoles[ri2].privList.size(); ++pi)
				{
					privs.push_back(allRoles[ri2].privList[pi]);
				}
			}
		}
	}
	return privs;
}

}
