/*
da3.cpp
Mark Underwood
9.25.17
Contains definitions of various da3 functions.
*/

#include <functional>
using std::function;
#include <stdexcept>

//callBetween
//Documentation in header file
void callBetween(const function<void()> & start,
	const function<void()> & middle,
	const function<void()> & finish)
{
	try
	{
		start();
	}
	catch (...)
	{
		throw;
	}

	try
	{
		middle();
	}
	catch (...)
	{
		finish();
		throw;
	}
	
	finish();
}

//gcd
//Documentation in header file
int gcd(int a, int b)
{
	if (a == 0)
	{
		return b;
	}

	if (a > b)
	{
		return gcd(b, a);
	}

	return gcd(b % a, a);
	
}
