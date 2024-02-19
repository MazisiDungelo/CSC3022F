#include <iostream>   //a system header file - needed to do simple I/O
#include "myWC.h"	         //header file - contains decl of fib()

int main (void)
{
      using namespace DNGMAZ001;
	std::cout << "Please enter a sentence" << std::endl;
      std::cout << countLines() << " " << countWords()  <<  " " << countChars() << std::endl;

      return 0; 
}