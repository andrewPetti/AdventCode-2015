// Day 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include "Day 7.h"

using namespace std;

bool IsNumber(int &value, const std::string& token)
{
	auto isNumber = true;
	try
	{
		value = boost::lexical_cast<int>(token);
	}
	catch (const boost::bad_lexical_cast &)
	{
		isNumber = false;
	}

	return isNumber;
}

bool ProcessSignal(std::vector<std::string> tokens, map<std::string, int>& wires)
{
	if (tokens.size() != 3)
		return false;
	auto signal = 0;
	if (!IsNumber(signal, tokens.at(0)))
		return false;

	wires[tokens.at(2)] = signal;
	return true;
}

bool DoesNotExist(std::string key, const map<std::string, int>& wires)
{
	auto it = wires.find(key);
	return (it == wires.end()) ? true : false;
}
bool ProcessAnd(std::vector<std::string> tokens, map<std::string, int>& wires)
{
	if (tokens.at(1).compare("AND") != 0)
		return false;

	auto in1 = tokens.at(0);
	auto in2 = tokens.at(2);
	auto output = tokens.at(4);

	if (DoesNotExist(in1, wires) || DoesNotExist(in2, wires))
		return false;

	wires[output] = wires.at(in1) & wires.at(in2);
	return true;
}

bool ProcessOr(std::vector<std::string> tokens, map<std::string, int>& wires)
{
	if (tokens.at(1).compare("OR") != 0)
		return false;

	auto in1 = tokens.at(0);
	auto in2 = tokens.at(2);
	auto output = tokens.at(4);

	if (DoesNotExist(in1, wires) || DoesNotExist(in2, wires))
		return false;

	wires[output] = wires.at(in1) | wires.at(in2);
	return true;
}

void ProcessInstruction(string instruction, map<std::string, int>& wires)
{
	istringstream iss(instruction);
	vector<string> tokens{ istream_iterator<string>{iss},
					  istream_iterator<string>{} };

	if (ProcessSignal(tokens, wires))
		return;
	else if (ProcessAnd(tokens, wires))
		return;
	else if (ProcessOr(tokens, wires))
		return;

//	auto value = 0;
//	if ( IsNumber(value, tokens.at(0))
//		;
//
//	
//	if (isSignal)
//	{
//
//	}
}

int main()
{
    cout << "Day 7 : Some Assembly required\n";
	cout << "Today we help Bobby Tables with his wire kit.\n";

	map<std::string, int> wires;
	
	std::vector<std::string> instructions = { "123 -> x","456 -> y", "x AND y -> d" , "x OR y -> e"
											  " x LSHIFT 2 -> f", "y RSHIFT 2 -> g", "NOT x -> h", "NOT y -> i"};

	for (auto instruction : instructions)
		ProcessInstruction(instruction, wires);

	for (auto it = wires.begin(); it != wires.end(); it++)
		cout << it->first << ": " << it->second << endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
