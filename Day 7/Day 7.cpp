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
#include "Day7Inputs.h"

using namespace std;

bool IsNumber( int &value, const std::string& token )
{
	auto isNumber = true;
	try
	{
		value = boost::lexical_cast<int>( token );
	}
	catch( const boost::bad_lexical_cast & )
	{
		isNumber = false;
	}

	return isNumber;
}

bool DoesNotExist(std::string key, const map<std::string, unsigned int>& wires)
{
	auto it = wires.find(key);
	return (it == wires.end()) ? true : false;
}

bool ProcessSignal( std::vector<std::string> tokens, map<std::string, unsigned int>& wires )
{
	if (tokens.size() != 3 && tokens.at(1).compare("->") !=0 )
		return false;

	auto signal = 0;
	if (IsNumber(signal, tokens.at(0)))
		wires[tokens.at(2)] = signal;
	else
	{
		auto in1 = tokens.at(0);
		if (DoesNotExist(in1, wires))
			return false;

		wires[tokens.at(2)] = wires.at(in1);
	}
	return true;
}


bool ProcessAnd( const std::vector<std::string>& tokens, map<std::string, unsigned int>& wires )
{
	if( tokens.at( 1 ).compare( "AND" ) != 0 )
		return false;

	auto in1 = tokens.at( 0 );
	auto in2 = tokens.at( 2 );
	auto output = tokens.at( 4 );

	auto val1 = -1;
	auto val2 = -1;
	IsNumber( val1, in1 );
	IsNumber( val2, in2 );

	if( ( val1 == -1 && DoesNotExist( in1, wires ) ) || ( val2 == -1 && DoesNotExist( in2, wires ) ))
		return false;

	auto first = ( val1 == -1 ) ? wires.at( in1 ) : val1;
	auto second = ( val2 == -1 ) ? wires.at( in2 ) : val2;


	wires[output] = first & second;
	return true;
}

        bool ProcessOr( const std::vector<std::string>& tokens, map<std::string, unsigned int>& wires )
{
	if( tokens.at( 1 ).compare( "OR" ) != 0 )
		return false;

	auto in1 = tokens.at( 0 );
	auto in2 = tokens.at( 2 );
	auto output = tokens.at( 4 );

	auto val1 = -1;
	auto val2 = -1;
	IsNumber( val1, in1 );
	IsNumber( val2, in2 );

	if( ( val1 == -1 && DoesNotExist( in1, wires )) || ( val2 == -1 && DoesNotExist( in2, wires ) ))
		return false;

	auto first = ( val1 == -1 ) ? wires.at( in1 ) : val1;
	auto second = ( val2 == -1 ) ? wires.at( in2 ) : val2;

	wires[output] = first | second;
	return true;
}

        bool ProcessRSHIFT( const std::vector<std::string>& tokens, map<std::string, unsigned int>& wires )
{
	if( tokens.at( 1 ).compare( "RSHIFT" ) != 0 )
		return false;

	auto in1 = tokens.at( 0 );
	auto value = 0;
	if( !IsNumber( value, tokens.at( 2 ) ) )
		return false;
	if( DoesNotExist( in1, wires ) )
		return false;

	auto output = tokens.at( 4 );
	wires[output] = wires.at( in1 ) >> value;

	return true;
}

bool ProcessLSHIFT( const std::vector<std::string>& tokens, map<std::string, unsigned int>& wires )
{
	if( tokens.at( 1 ).compare( "LSHIFT" ) != 0 )
		return false;

	auto in1 = tokens.at( 0 );
	auto value = 0;
	if( !IsNumber( value, tokens.at( 2 ) ) )
		return false;
	if( DoesNotExist( in1, wires ) )
		return false;

	auto output = tokens.at( 4 );
	wires[output] = wires.at( in1 ) << value;

	return true;
}

bool ProcessNOT( const std::vector<std::string>& tokens, map<std::string, unsigned int>& wires )
{
	if( tokens.at( 0 ).compare( "NOT" ) != 0 )
		return false;

	auto in1 = tokens.at( 1 );
	if( DoesNotExist( in1, wires ) )
		return false;

	auto output = tokens.at( 3 );
	uint16_t outputValue = ~wires.at(in1);
	wires[output] = outputValue;

	return true;
}

bool ProcessInstruction( string instruction, map<std::string, unsigned int>& wires )
{
	istringstream iss( instruction );
	vector<string> tokens{ istream_iterator<string>{iss},
	                       istream_iterator<string>{} };

	if( ProcessSignal( tokens, wires ) )
		return true;
	else if( ProcessAnd( tokens, wires ) )
		return true;
	else if( ProcessOr( tokens, wires ) )
		return true;
	else if( ProcessRSHIFT( tokens, wires ) )
		return true;
	else if( ProcessLSHIFT( tokens, wires ) )
		return true;
	else if( ProcessNOT( tokens, wires ) )
		return true;

	return false;
}

int main()
{
	cout << "Day 7 : Some Assembly required\n";
	cout << "Today we help Bobby Tables with his wire kit.\n";

	map<std::string, unsigned int> wires;

	std::vector<std::string> instructions = { "123 -> x", "456 -> y", "x AND y -> d", "x OR y -> e",
	                                          "x LSHIFT 2 -> f", "y RSHIFT 2 -> g", "NOT x -> h", "NOT y -> i"
	                                        };
	instructions = inputs::GetInstructions();
	//for( auto instruction : instructions )
	//{
	//	ProcessInstruction( instruction, wires );
	//}
	cout << "Instruction loop with count: " << instructions.size();

	while( instructions.size() > 0 )
	{
		
		vector<string> toProcess;
		for( auto instruction : instructions )
		{
			if( !ProcessInstruction( instruction, wires ) )
				toProcess.push_back( instruction );
		}

		instructions = toProcess;
		cout << " " << instructions.size();
	}

	cout << endl;
	for( auto it = wires.begin(); it != wires.end(); it++ )
		cout << it->first << ": " << it->second << endl;

	cout << "part 1 answer is a has a signal value of: " << wires.at("a") <<endl<<endl;

	instructions = inputs::GetInstructions();
	instructions.at(3) = "3176 -> b";

	map<std::string, unsigned int> wires2;
	while (instructions.size() > 0)
	{

		vector<string> toProcess;
		for (auto instruction : instructions)
		{
			if (!ProcessInstruction(instruction, wires2))
				toProcess.push_back(instruction);
		}

		instructions = toProcess;
		cout << " " << instructions.size();
	}

	cout << endl;
	//for (auto it = wires.begin(); it != wires.end(); it++)
	//	cout << it->first << ": " << it->second << endl;

	cout << "part 2 answer is a has a signal value of: " << wires2.at("a") << endl << endl;

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
