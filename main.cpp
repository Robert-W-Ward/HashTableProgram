#include <iostream>
#include<string>
#include <sstream>
#include <fstream>
#include "HashTable.h"
using std::string;
using std::stringstream;
using std::cin;
using std::cout;
using std::fstream;
string TOKEN;


bool isRunning = true;
HashTable ht;
//function to parse all commands from console or file
void parse(string ToBeParsed );
//function to save the hash table as a file
void savePWDFile(string filename)
{
	fstream File;
	File.open(filename,fstream::out);
	for(int i = 0;i < ht.size; i++)
	{
		if(ht.Table[i].name == "")
		{

		}
		else
		{
			File << ht.Table[i].name<<" " << ht.Table[i].homeDir<< ht.Table[i].password<<"\n";
		}
	}
	cout << "File Saved\n";
	File.close();
}
//loads a file with usernames homedirectries and passwords into the has table
void loadPWDFile(string FileToLoad)
{
	fstream File;
	string tmp;
	stringstream FileContents;
	File.open(FileToLoad);
	if(File.is_open())
	{
		cout << "Successfully opened: " << FileToLoad << "\n";
		while(getline(File, tmp))
		{
			FileContents << "new"<<" ";
			FileContents << tmp;
			parse(FileContents.str());
			FileContents.clear();
			FileContents.str(std::string());
		}
		File.close();
	}
	else
	{
		cout << "File ERROR: \"" << FileToLoad << "\" could not be loaded or located\n";
	}

}
//loads a file of commands
void loadFile(string FileToLoad)
{
	fstream File;
	string tmp;
	stringstream FileContents;
	File.open(FileToLoad);
	if(File.is_open())
	{
		cout << "Successfully opened: " << FileToLoad << "\n";
		while(getline(File, tmp))
		{
			FileContents << tmp;
			parse(FileContents.str());
			FileContents.clear();
			FileContents.str(std::string());
		}
		File.close();
	}
	else
	{
		cout << "File ERROR: \"" << FileToLoad << "\" could not be loaded or located\n";
		//return FileToLoad;
	}

	//return  FileContents.str();
}
//function to parse all commands from console or file
void parse(string ToBeParsed)
{
	stringstream parseStream(ToBeParsed);
	while(getline(parseStream, TOKEN,' '))
	{
		
			if(TOKEN == "exit")
			{
				cout << "GOODBYE!\n";
				isRunning = false;
				break;
			}
			else if(TOKEN == "load")
			{
				getline(parseStream, TOKEN, ' ');
				if(TOKEN == "pwd")
				{
					getline(parseStream, TOKEN, ' ');
					loadPWDFile(TOKEN);
				}
				else
				{
					loadFile(TOKEN);
				}

			}
			else if(TOKEN == "new")
			{

				std::string name ;
				std::string homeDir ;
				std::string password;


				getline(parseStream, TOKEN, ' ');
				if(TOKEN != "")
				{
					name=TOKEN;
					getline(parseStream, TOKEN,' ');
					if(TOKEN.find("/")!=string::npos)
					{
						homeDir = TOKEN;
						getline(parseStream, TOKEN, ' ');
						if(TOKEN != "")
						{
							password = TOKEN;
							userData tmp = userData(name, homeDir, password);
							ht.insert(&tmp);

						}
					}
					else 
					{
						getline(parseStream, TOKEN, ' ');
						
							password = TOKEN;
							userData tmp = userData(name, password);
							ht.insert(&tmp);
							
					}

				}
				else cout<<"Unrecognized command\n";
			}
			else if(TOKEN=="display")
			{
				//TOKEN.clear();
				getline(parseStream, TOKEN, ' ');
				if(TOKEN == ""||TOKEN=="display")
				{
					ht.display();
					break;
				}
				else if(TOKEN != "")
				{
					if(ht.isAuser(TOKEN))
					{
						ht.displayUser(TOKEN);
					}
				}
				
				
			}
			else if(TOKEN == "verify")
			{
				getline(parseStream, TOKEN, ' ');
				string name = TOKEN;
				getline(parseStream, TOKEN, ' ');
				string password = TOKEN;
				if(ht.Verify(name, password))
				{
					std::cout << "User successfully validated\n";
				}
				else
				{
					std::cout << "Validation has failed\n";
				}
			}
			else if(TOKEN == "password")
			{
				getline(parseStream, TOKEN, ' ');
				std::string user =TOKEN;
				getline(parseStream, TOKEN, ' ');
				std::string newPassword=TOKEN;
				ht.setPassword(user, newPassword);
			}
			else if(TOKEN == "home")
			{
				getline(parseStream, TOKEN, ' ');
				std::string user = TOKEN;
				getline(parseStream, TOKEN, ' ');
				std::string newHomeDir = TOKEN;
				ht.setHome(user, newHomeDir);
			}
			else if(TOKEN == "save")
			{
				getline(parseStream, TOKEN, ' ');
				if(TOKEN == "pwd")
				{
					getline(parseStream, TOKEN, ' ');
					savePWDFile(TOKEN);
				}
			}
			else if(TOKEN == "clear")
			{
				ht.clear();
			}
			else if(TOKEN == "remove")
			{
				getline(parseStream, TOKEN, ' ');
				ht.remove(TOKEN);
			}
	}
}
int main()
{
	HashTable* ht = new HashTable;
	while(isRunning)
	{
		

		string inputStr;
		cout << ">>";
		getline(cin, inputStr);
		std::stringstream inputStream;
		inputStream << inputStr;
		parse(inputStream.str());
	}
}

