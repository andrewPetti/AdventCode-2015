// Day 9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "inputs.h"

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
	std::cout << "Day 9: Help Santa find the optimal distance for deliveries.\n";
	std::cout << "Processing to find the minimal distance to visit all the cities only once .....\n";

	std::vector<std::string> cities;
	for( auto city : inputs::cityIndex )
		cities.push_back( city.first );

	std::sort( cities.begin(), cities.end() );
	auto minDist = 1e10;
	auto maxDist = 0;
	do
	{

		auto sumDist = 0;
		auto err = false;
		for( int i = 0; i < ( int )cities.size() - 1; i++ )
		{
			auto dist = inputs::GetDistanceBetween( cities[i], cities[i + 1] );
			if( dist == -1 )
			{
				err = true;
				break;
			}
			sumDist += dist;
		}

		if( err == false )
		{
			if( sumDist < minDist )
				minDist = sumDist;

			if( sumDist > maxDist )
				maxDist = sumDist;
		}
	}
	while( std::next_permutation( cities.begin(), cities.end() ) );

	std::cout << "The minimum distance found is: " << minDist;
	std::cout << "\nThe maximum distance found is: " << maxDist;
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
