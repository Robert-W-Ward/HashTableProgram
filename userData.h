#pragma once
#include <iostream>
#include <string>

	struct userData
	{
		
		std::string name;
		int nameAsInt{ 0 };
		std::string homeDir;
		std::string password;
		int currentStatus{ empty };
		//enumeration of statuses
		enum Statuses
		{
			empty, modified, unmodified
		};



		userData() :name(""), homeDir(""), password("")
		{}
		//constructor for when username and passwor given
		userData(std::string name, std::string password) :name(name), password(password)
		{
			std::cout<<"New user created!\n";
			CalcNameASCII();
		}
		//constructor for when username password and homedirectory are given
		userData(std::string name, std::string homeDir, std::string password) :name(name), homeDir(homeDir), password(password)
		{
			std::cout << "New user created!\n";
			CalcNameASCII();
		}
		
		//function to convert enumeration value back into the corresponding word it represents
		std::string getStatusWord(int i)
		{
			switch (i)
			{
			case 0:
				return "empty";
				break;
			case 1:
				return "modified";
				break;
			case 2:
				return "unmodified";
				break;
			default:
				return "No Status";
			}
		}
		//function to turn name into ASCII value to be hashed
		void CalcNameASCII();
	};

