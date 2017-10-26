#ifndef _USERANDPRIV_H_
#define _USERANDPRIV_H_

#include <string>
#include <vector>

namespace UnP
{

enum
{
	P_LV = 0,
	P_NOLV,
};

struct Priv
{
	int type;
	std::string name;
	int lv;
};

struct Role
{
	std::string name;
	std::vector<Priv> privList;
};

struct User
{
	std::string name;
	std::vector<std::string> roleList;
};

struct Query
{
	std::string uname;
	Priv priv;
};

}
#endif
