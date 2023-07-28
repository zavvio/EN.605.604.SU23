// EN.605.604.SU23_Assignment2_P2.cpp

#include "UserInterface.h"

using namespace std;

int main()
{
	Counter c;
	Memory m;
	UserInterface anInterface { c, m };
	anInterface.executeSelection();
	
	return 0;
}
