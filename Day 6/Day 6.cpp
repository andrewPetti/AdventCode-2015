// Day 6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Day6-Input.h"
#include <iostream>
#include <vector>

void Process(Instruction instruction, std::vector<std::vector<int>>& lights)
{
	auto actionType = instruction.m_Action;

	if (actionType == turn_on || actionType == turn_off)
	{
		auto onOff = 1;
		if (actionType == turn_off)
			onOff = 0;

		for (std::vector<std::vector<int>>::iterator it = lights.begin() + instruction.m_Start.second;
			it != lights.begin() + instruction.m_End.second+1;
			it++)
		{
			std::fill((*it).begin() + instruction.m_Start.first, (*it).begin() + instruction.m_End.first+1, onOff);
		}
	}

	else if (actionType == toggle)
	{
		for (std::vector<std::vector<int>>::iterator it = lights.begin() + instruction.m_Start.second;
			it != lights.begin() + instruction.m_End.second + 1;
			it++)
		{
			for (std::vector<int>::iterator itInside = (*it).begin() + instruction.m_Start.second;
				itInside != (*it).begin() + instruction.m_End.second + 1;
				itInside++)
			{
				auto newSetting = 1;
				if (*itInside == 1)
					newSetting = 0;

				*itInside = newSetting;
			}
		}
	}
}

int GetCountOfLightsOn(std::vector < std::vector<int>>& lights)
{
	auto count = 0;
	auto i = 0;
	for (std::vector<std::vector<int>>::iterator it = lights.begin(); it != lights.end(); it++, i++)
		count += std::count((*it).begin(), (*it).end(), 1);

	return count;
}

int main()
{
    std::cout << "Day 6: Lighting instructions from Santa\n";

	std::cout << "\nFollowing Santa's instrcutions for the lights at the end this many lights are still on: ";

	std::vector<std::vector<int>> lights;
	for (auto i = 0; i < 1000; i++)
	{
		std::vector<int> row(1000, 0);
		lights.push_back(row);
	}

	auto instructions = GetInstructions();
	for (auto instruct : instructions)
		Process(instruct, lights);

	//Process(Instruction(turn_on, std::make_pair(0, 0), std::make_pair(4, 4)), lights);
	//Process(Instruction(turn_off, std::make_pair(0, 1), std::make_pair(4, 1)), lights);
	//Process(Instruction(turn_off, std::make_pair(0, 3), std::make_pair(4, 3)), lights);
	//Process(Instruction(toggle, std::make_pair(0, 0), std::make_pair(4, 4)), lights);
	//Process(Instruction(turn_off, std::make_pair(0, 0), std::make_pair(0, 0)), lights);
	auto lightsOn = GetCountOfLightsOn(lights);
	std::cout << lightsOn;

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
