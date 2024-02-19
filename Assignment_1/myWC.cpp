//myWC.cpp - implemenation  file for my word count application 
#include "myWC.h"

namespace DNGMAZ001{
    int noOflines = 0;
    int noOfwords = 0;
    int noOfchars = 0;

    std::vector<std::string> lines;
    std::vector<std::string> words;
    std::vector<std::string> chars;

    std::vector<char> specCharacters = { '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*',
                                        '+', ',', '-', '.', '/', ':', ';', '<', '=', '>',
                                        '?', '@', '[', '\\', ']', '^', '_', '{', '|', '}',
                                        '~'};
    int countLines()
    {
    
        std::string line;
        while (std::getline(std::cin, line)) {
            lines.push_back(line);
            noOflines++;

        }
        return noOflines;

    }

    int countWords(){
        std::string word;
        for (std::string line: lines){
            for (char c: line) {
                if (c != ' '  && !isSpecChar(c)) {
                    word += c;
                    
                }
                else {
                    if (word != "") {
                        words.push_back(word);
                        word.clear();
                        noOfwords++;
                    }
                }
            }
            if (word != "") {
                words.push_back(word);
                word.clear();
                noOfwords++;
            }
        }

        return noOfwords;
    }

    int countChars(){
        for (std::string word : words){
            for (char c : word){
                noOfchars++;
            }
        }
        return noOfchars;
    }

    bool isSpecChar(char ch){
        for (char c : specCharacters){
            if (ch == c){
                return true;
            }
        }
        return false;
    }

}
