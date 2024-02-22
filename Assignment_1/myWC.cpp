//myWC.cpp - implemenation  file for my word count application 
#include "myWC.h"

namespace DNGMAZ001{
    int noOflines = 0;
    int noOfwords = 0;
    int noOfchars = 0;



    std::vector<std::string> lines;
    std::vector<std::string> words;
    std::vector<char> chars;

    std::vector<charInfo> charCounts;

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
                chars.push_back(tolower(c));
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
    void countCharOccurances(){
        char holder;
        if (!chars.empty()){
            charCounts.push_back({chars[0],1});
            for (int i=1; i < chars.size();i++){
                for (int j=0; j < charCounts.size();j++){
                    if (chars[i] == charCounts[j].character){
                        charCounts[j].count++;
                        holder = '\0';
                    }
                    else{
                        holder = chars[i];
                    }
                }
                if (holder != '\0'){
                  charCounts.push_back({holder,1});
                  holder = '\0';  
                }
                
            } 
        }
        if (!charCounts.empty()){
            char lastChar = charCounts[0].character;
            for (int n=0; n < charCounts.size(); n++){
                if (charCounts[n].character > lastChar){lastChar=charCounts[n].character;}
            }
            for (char c = '0'; c <= 'z'; ++c) {
                for (int x=0; x < charCounts.size(); x++){
                    if (charCounts[x].character == c){
                        if (c == lastChar){
                            std::cout << charCounts[x].character << ":" << charCounts[x].count;
                            break;
                        }
                        std::cout << charCounts[x].character << ":" << charCounts[x].count << " ";
                        break;
                        
                    }
                }
            } 
        }

        

    }


}
