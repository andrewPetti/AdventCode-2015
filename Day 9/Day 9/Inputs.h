#pragma once
#include <vector>
#include <map>

namespace inputs
{
	const std::map< std::string, int> cityIndex
	{
		{ "Faerun", 0},
		{"Norrath", 1},
		{"Tristram", 2},
		{"AlphaCenrauri", 3},
		{"Arbre", 4},
		{"Snowdin", 5},
		{"Tambi", 6},
		{"Straylight", 7}
	};

	const std::vector<std::vector<int>> distances
	{
		{0, 129, 58, 13, 24, 60, 71, 67 },
		{129, 0, 142, 15, 135, 75, 82, 54},
		{58, 142, 0, 118, 122, 103, 49, 97},
		{13, 15, 118, 0, 116, 12, 18, 91},
		{24, 135, 122, 116, 0, 129, 53, 40},
		{60, 75, 103, 12, 129, 0, 15, 99},
		{71, 82, 49, 18, 53, 15, 0, 70},
		{67, 54, 97, 91, 40, 99, 70, 0}
	};

	int GetDistanceBetween( std::string place1, std::string place2 )
	{
		auto pos1 = cityIndex.find( place1 );
		if( pos1 == cityIndex.end() )
			return -1;

		auto pos2 = cityIndex.find( place2 );
		if( pos2 == cityIndex.end() )
			return -1;

		if( pos1->second >= ( int )distances.size() )
			return -1;

		if( pos2->second >= ( int ) distances[pos1->second].size() )
			return -1;

		return distances[pos1->second][pos2->second];
	}
}