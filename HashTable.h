#pragma once
#include "userData.h"
#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
struct HashTable
{
	
	userData* Table;
	int size;
	
	int numOfElements{0};
	float loadFactor = numOfElements / size;
	HashTable():Table(new userData[23]),size(23),numOfElements(0){}
	//clears the hash table and resets the size
	void clear()
	{
		delete[] Table;
		size = 23;
		numOfElements = 0;
		Table = new userData[size];
		std::cout << "Hash table cleared\n";
	}
	//utility function to check if a user is present in the table
	bool isAuser(std::string name)
	{
		for(int i = 0; i < size; i++)
		{
			if(name == Table[i].name)
			{
				return true;
			}

		}
		return false;
	}
	//util funtion to check if a number is prime
	bool checkPrime(int n)
	{
		bool isPrime = true;
		if(n == 0 || n == 1)
		{
			return false;
		}
		else for(int i = 2; i <= n / 2; ++i)
		{
			if(n % i == 0)
			{
				isPrime = false;
				break;
			}
		}
		return isPrime;
	}
	//util function to make a number prime if it isn't already
	int makePrime(int n)
	{
		if(checkPrime(n))
		{
			return n;
		}
		else
		{
			n += 1;
			makePrime(n);

		}


	}
	//hashs the value based on size of table
	int Hash(int key)
	{
		return key % size;
	}
	//funtion to insert into the hash table and also handle collisions 
	void insert(userData* UD)
	{

		int idx = Hash(UD->nameAsInt);
		int probeCount{ 0 };
		while(true)
		{
			if(Table[idx].currentStatus == userData::Statuses::empty)
			{
				if(idx > size)
				{
					idx = size;
				}
				else
				{
					UD->currentStatus = userData::Statuses::unmodified;
					Table[idx] = *UD;
					numOfElements++;
					probeCount = 0;
					loadFactor = (float)numOfElements / (float)size;
				}

				if(loadFactor >= .5f)
				{
					resize();
				}
				break;
			}
			else
			{

				probeCount++;
				idx += Hash(UD->nameAsInt) + (probeCount * probeCount);
				if(idx > size)
				{
					idx = (probeCount * probeCount);
				}

			}
		}
	}
	//function to remove the specified user from the table
	void remove(std::string ToRemove)
	{
		for(int i = 0; i < size; i++)
		{
			if(ToRemove == Table[i].name)
			{
				Table[i].currentStatus = userData::Statuses::empty;
				std::cout << ToRemove << " has been removed from the hash table\n";
				numOfElements--;
				return;
			}
			else continue;
		}
		std::cout << ToRemove << " Is not present in the has table\n";
	}

	//updates the home directory of the specified user
	void setHome(std::string user, std::string newHomeDir)
	{
		for(int i = 0; i < size; i++)
		{
			if(Table[i].name == user)
			{
				Table[i].homeDir = newHomeDir;
				Table[i].currentStatus = userData::Statuses::modified;
				std::cout << "Home directory updated for user\n";
				break;
			}
			else continue;
		}

	}
	//updates the password of the specified user
	void setPassword(std::string user, std::string newPassword)
	{
		for(int i = 0; i < size; i++)
		{
			if(Table[i].name == user)
			{
				Table[i].password = newPassword;
				Table[i].currentStatus = userData::Statuses::modified;
				std::cout << "Password for user updated\n";
				break;
			}
		}
	}
	//converts the password to stars for printing
	std::string printStars(std::string password)
	{
		std::string passAsStars;
		for(int j = 0; j < password.length(); j++)
		{
			passAsStars += '*';
		}
		return passAsStars;
	}
	//displays the entire table
	void display()
	{
		std::cout << "Displaying the user table\n";
		std::cout << std::setw(15) << std::left << "Ele" << std::setw(15) << std::left << "MOD" << std::setw(15) << std::left << "User" << std::setw(15) << std::left << "Dir" << std::setw(15) << std::left << "Pwd" << "\n";
		for(int i = 0; i < size; i++)
		{
			std::cout << std::setw(15) << std::left << i <<
				std::setw(15) << std::left << Table[i].getStatusWord(Table[i].currentStatus) <<
				std::setw(15) << std::left << Table[i].name <<
				std::setw(15) << std::left << Table[i].homeDir <<
				std::setw(15) << std::left << printStars(Table[i].password) << "\n";


		}
	}
	//displays the specified user
	void displayUser(std::string user)
	{
		for(auto x = 0; x < size; x++)
		{
			if(Table[x].name == user)
			{
				std::cout << "The User Was found\n";
				std::cout << std::setw(15) << std::left << "Ele" << std::setw(15) << std::left << "MOD" << std::setw(15) << std::left << "User" << std::setw(15) << std::left << "Dir" << std::setw(15) << std::left << "Pwd" << "\n";
				std::cout << std::setw(15) << std::left << x <<
					std::setw(15) << std::left << Table[x].getStatusWord(Table[x].currentStatus) <<
					std::setw(15) << std::left << Table[x].name <<
					std::setw(15) << std::left << Table[x].homeDir <<
					std::setw(15) << std::left << printStars(Table[x].password) << "\n";
				return;
			}
			else continue;
		}
		std::cout << "User could not be found\n";
	}
	//verifies the specified user has the specified password and returns false if otherwise
	bool Verify(std::string name, std::string password)
	{
		for(auto x = 0; x < size; x++)
		{
			if(Table[x].name == name && Table[x].password == password)
			{
				return true;
			}
			else continue;
		}
		return false;
	}
	//util function to resize the table when the loadfactor reaches the threshold 
	void resize()
	{
		userData* old = this->Table;
		int oldSize = this->size;
		this->size = makePrime(2 * size);

		this->Table = new userData[size];
		numOfElements = 0;
		loadFactor = (float)numOfElements / size;
		for(int i = 0; i < oldSize; i++)
		{
			if(old[i].currentStatus != userData::Statuses::empty)
			{
				if(old[i].nameAsInt < 0)
				{
					old[i].nameAsInt = 0;
				}
				else
				{
					this->insert(&old[i]);

				}
			}

		}
		delete[] old;


	}
};