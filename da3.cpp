/*
da3.cpp
Mark Underwood
9.25.17
Contains definitions of various da3 functions.
*/

#include <functional>
using std::function;

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


int gcd(int a, int b)
{
	return 0;
}
