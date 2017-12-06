// cuber_test_suites.cpp  INCOMPLETE
// Glenn G. Chappell
// 2 Dec 2017
//
// For CS 311 Fall 2017
// Tests for class Cuber: test suites
// For Assignment 8, Exercise B
// Uses the "Catch" unit-testing framework
// Requires cuber_test_main.cpp, catch.hpp, cuber.h

// Includes for code to be tested
#include "cuber.h"         // For class Cuber
#include "cuber.h"         // Double inclusion test

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework
#include <vector>
#include <iostream>
// Additional includes for this test program


// *********************************************************************
// Test Cases
// *********************************************************************

Cuber test;
float fl = test(-0.1123581321f);

TEST_CASE( "Cuber: Ints",
           "[int]" )
{
	Cuber cc;
	std::vector<int> posCubes = { 0,1,8,27,64,125,216,343,512,729 };
	std::vector<int> negCubes = { 0,-1,-8,-27,-64,-125,-216,-343,-512,-729 };
	std::vector<int> bigInts = {-1290, 1000, -567, 857, -800};
	std::vector<int> bigIntCubes = {-2146689000, 1000000000, -182284263, 629422793, -512000000};

	SECTION("Positive cubes less than 10")
	{
		for (int i = 0; i != 10; ++i)
		{
			INFO("Cubing ", i);
			REQUIRE(cc(i) == posCubes[i]);
		}
	}

	SECTION("Negative cubes less than 10")
	{
		for (int i = 0; i != 10; ++i)
		{
			REQUIRE(cc(-i) == negCubes[i]);
		}
	}

	SECTION("Selected Large ints")
	{
		for (auto i = 0; i != bigInts.size(); ++i)
		{
			REQUIRE(cc(bigInts[i]) == bigIntCubes[i]);
		}
	}
}

TEST_CASE("Cuber: Floats", "[float]")
{
	Cuber cc;
	std::vector<float> posCubes = { 0.0f, 1.0f, 8.0f, 27.0f, 64.0f, 125.0f, 216.0f, 343.0f, 512.0f, 729.0f };
	std::vector<float> negCubes = { -0.0f, -1.0f, -8.0f, -27.0f, -64.0f, -125.0f, -216.0f, -343.0f, -512.0f, -729.0f };
	std::vector<float> bigFloats = { -1290.0f, 1000.0f, -567.0f, 857.0f, -800.0f };
	std::vector<float> bigFloatCubes = { -2146689000.0f, 1000000000.0f, -182284263.0f, 629422793.0f, -512000000.0f };
	std::vector<float> decimals = {0.66f, -3.14159f, -0.1123581321f, 1010.34f};
	std::vector<float> decimalCubes = {0.287496030f, -31.0062027f, -0.00141844829f, 1.03134195e+9f};

	SECTION("Positive cubes less than 10")
	{
		for (size_t i = 0; i != 10; ++i)
		{
			REQUIRE(cc(i) == posCubes[i]);
		}
	}

	SECTION("Negative cubes less than 10")
	{
		for (int i = 0; i != 10; ++i)
		{
			REQUIRE(cc(-i) == negCubes[i]);
		}
	}

	SECTION("Selected Large Floats")
	{
		for (size_t i = 0; i != bigFloats.size(); ++i)
		{
			REQUIRE(cc(bigFloats[i]) == bigFloatCubes[i]);
		}
	}

	SECTION("Decimal Floats")
	{
		for (size_t i = 0; i != decimals.size(); ++i)
		{
			REQUIRE(cc(decimals[i]) == decimalCubes[i]);
		}
	}
}

TEST_CASE("Char Input", "[char]")
{
	Cuber cc;

	SECTION("Low-Value Chars")
	{
		INFO("Cube a space");
		REQUIRE(cc(' ') == 0);

		INFO("Cube an exclamation point");
		REQUIRE(cc('!') == 'a');

		INFO("Cube an ampersand");
		REQUIRE(cc('&') == 'X');
	}

	SECTION("High Value Chars")
	{

	}
}