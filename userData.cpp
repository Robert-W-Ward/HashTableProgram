#include "userData.h"


void userData::CalcNameASCII()
{
	
	for(char x : name)
	{
		
		this->nameAsInt += (int)x;

	}
}
