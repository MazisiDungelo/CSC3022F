// myWC.h - header file for my word count application

#ifndef _MYWC_H
#define _MYWC_H

#include <iostream>
#include <vector>
#include <string>

namespace DNGMAZ001{
    extern int noOflines;
    extern std::vector<std::string> lines;

    extern int noOfwords;
    extern std::vector<std::string> words;

    extern int noOfchars;
    extern std::vector<char> chars;

    extern std::vector<char> specCharacters;

    struct charInfo{
        char character;
        long count;
    };

    extern std::vector<charInfo> charCounts;

    int countLines(); // function to count the lines that are in text 

    int countWords(); // function to count words in a sentence

    int countChars(); // function to count characcter in a word

    bool isSpecChar(char ch); // function to check is character ch is a special character or not

    void countCharOccurances();
}

     

#endif

