#include "csptest.h"
#include <iostream>

namespace Q201612_2
{

void f_201612_2()
{
	int T = 0;
	std::cin >> T;
	int S = 0;
	if (T > 0 && T <= 3500)
	{	S = (double(T)); }
	else if (T <= 4955)
	{	S =  ((double(T) - 105) / 0.97); }
	else if (T <= 7655)
	{	S = ((double(T) - 455) / 0.9); }
	else if (T <= 11255)
	{	S = ((double(T) - 1255) / 0.8); }
	else if (T <= 30755)
	{	S = ((double(T) - 1880) / 0.75); }
	else if (T <= 44755)
	{	S = ((double(T) - 3805) / 0.7); }
	else if (T <= 61005)
	{	S = ((double(T) - 6730) / 0.65); }
	else
	{	S = ((double(T) - 15080) / 0.55); }
	std::cout << S;
}

}
