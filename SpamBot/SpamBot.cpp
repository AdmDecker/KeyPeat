// SpamBot.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <iostream>
#include <Psapi.h>
#include <string>
#include <vector>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int timer;
	
	while(0 == 0)
	{

		//Get input
		std::string Input;
		std::vector<bool> ifShift;
	
		std::cout << "Spam Message: ";
		getline(std::cin, Input);

		int cycles = -1;

		std:: cout << "\nNumber of Cycles: ";
		std:: cin >> cycles;

		//Time between cycles
		std::cout << "\nTime between cycles (minutes)";
		std::cin >> timer;

		std::cout << "\nPrepare target location...\n";
	
		for(int x = 5; x > 0; x--)
		{
			std::cout << x << "...";
			Sleep(1000);
		}



		//Parse input
		std::vector<DWORD> Output;

		for(int x = 0; x < Input.length(); x++)
		{
			if(isalpha(Input[x]))
			{
				if(isupper(Input[x]))
				{
					Output.push_back(Input[x]);
					ifShift.push_back(true);
				}
				else
				{
					Output.push_back(toupper(Input[x]));
					ifShift.push_back(false);
				}
			}
			else if(isdigit(Input[x]))
			{
				Output.push_back(Input[x]);
				ifShift.push_back(false);
			}
			else if(Input[x] == ' ')
			{
				Output.push_back(VK_SPACE);
				ifShift.push_back(false);
			}
			else if(Input[x] == ';' || Input[x] == ':')
			{
				Output.push_back(VK_OEM_1);

				if(Input[x] == ';')
					ifShift.push_back(false);
				else
					ifShift.push_back(true);
			}
			else if(Input[x] == '!')
			{
				Output.push_back('1');
				ifShift.push_back(true);
			}
			else if(Input[x] == '?' || Input[x] == '/')
			{
				Output.push_back(VK_OEM_2);

				if(Input[x] == '/')
					ifShift.push_back(false);
				else
					ifShift.push_back(true);
			}


			else
			{
				std::cout << "Invalid Character: " << Input[x] << "\n";
			}
		}
	
		


		//Spam it up
		std::cout << "\nSpamming...";
		Output.push_back(VK_RETURN);
		ifShift.push_back(false);

		if(ifShift.size() != Output.size())
		{
			std::cout << "ifShift does not equal Output. Aborting";
			std::cin.get();
			return 0;
		}


		if(cycles > 0)
		{
			for(int y = 0; y < cycles; y++)
			{
				Sleep(timer * 60000);
				for(int x = 0;  x < Output.size(); x++)
				{

					INPUT shift;
					if(ifShift.at(x))
					{
						shift.type = INPUT_KEYBOARD;
						shift.ki.wVk = VK_SHIFT;
						shift.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
						SendInput(true, &shift, sizeof(shift));
						Sleep(10);
					}



					INPUT input;
					input.type = INPUT_KEYBOARD;

					input.ki.wVk = Output.at(x);
	
					input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;

					SendInput(true, &input, sizeof(input));

					Sleep(5);

					input.ki.dwFlags = KEYEVENTF_KEYUP;
				
					SendInput(true, &input, sizeof(input)); 

					if(ifShift.at(x))
					{
						Sleep(10);
						shift.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_EXTENDEDKEY;
						SendInput(true, &shift, sizeof(shift));
					}



					Sleep(10);
				}
			}
		}
		

		std::cin.get();
		system("cls");
	}
		return 0;
}
