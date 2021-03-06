// Day 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

#include "md5.h"

int FindNumberHashStartingWithLeadingZeros( std::string inputKey, int leadingZeros)
{
	auto notFound = true;
	auto counter = 1;
	auto retVal = counter;
	std::string prefix = "000000";

	while (notFound)
	{
		auto combined = inputKey + std::to_string(counter);
		auto hash = md5(combined);

		if (!hash.compare(0, prefix.size(), prefix))
		{
			notFound = false;
			retVal = counter;
		}
		counter++;
	}

	return retVal;
}

int main()
{
	std::cout << "2015 Day 5: We need to help Santa Mine AdventCoin: \n";
	auto key = "yzbqklnj";
	//key = "abcdef";
	std::cout << "Secret Key is: " << key;
	
	/*std::cout << "\n The Answser for 5 leading zeros is: ";
	auto answer = FindNumberHashStartingWithLeadingZeros(key, 5);
	std::cout << answer;*/

	std::cout << "\n Part2: The Answser for 6 leading zeros is: ";
	auto answer = FindNumberHashStartingWithLeadingZeros(key, 6);
	std::cout << answer;


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
