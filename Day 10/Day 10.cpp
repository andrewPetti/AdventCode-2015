// Day 10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "boost\format.hpp"

int main()
{
	std::cout << "Day 10 : Elves play look and say!\n";

	std::string result = "1113122113";
	auto loops = 50;
	for( int i = 0; i < loops; i++ )
	{
		std::cout << "Loop " << i << std::endl;

		int strSize = result.size();
		std::string newString = "";

		for( int j = 0; j < strSize; j++ )
		{
			auto digit = result.at( j );
			auto digitCount = 1;

			if( j < strSize - 1 )
			{
				auto cont = true;
				do
				{
					auto nextdigit = result.at( j + 1 );
					if( nextdigit != digit )
						cont = false;
					else
					{
						j++;
						digitCount++;
					}
				}
				while( cont );
			}
			newString.append( ( boost::format( "%s%s" ) % digitCount % digit ).str() );

		}
		result = newString;
	}

	std::cout << "After " << loops << " rounds the result is this long: " << result.size();
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
