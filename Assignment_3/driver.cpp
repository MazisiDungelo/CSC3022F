#include <iostream>
#include <string>
#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"


int main(int argc, char * argv[]){
    
    //Search for file name  from args use sample.pgm if not found

    std::cout<< "First file: "<< argv[argc-1]<<std::endl;
    bool hasNext = true;
    std::string option;
    std::string outImagefile;
    
    
    
    DNGMAZ001::PGMimageProcessor *imageProcessor = new DNGMAZ001::PGMimageProcessor(argv[argc-1]);
    int count = 1;
    int min,max, threshold;

    while (count < (argc-1)){
        try
        {
            option = argv[count];
            std::cout<< "Executing option: "<< option << std::endl;
            switch (option[1])
            {
            case 's':
                min = std::stoi(argv[count + 1 ]);
                max= std::stoi(argv[count + 2]);
                std::cout << "Reduced from: " << imageProcessor->getComponentCount() << std::endl;
                std::cout << "Reduced to: " <<imageProcessor->filterComponentsBySize(min,max)<<std::endl;
                count+=2;
                break;
            case 't':
                count++;
                threshold = std::stoi(argv[count]);
                imageProcessor->extractComponents(threshold,threshold);
                std::cout << "Stored : " << imageProcessor->getComponentCount()<< " components."<<std::endl;
                break;
            case 'p':
                imageProcessor->printAll();   
                break;
             case 'w':
                 outImagefile = argv[count + 1];
                 imageProcessor->writeComponents(outImagefile);
                 count++;
                 break;
            default:
                break;
            }
            count++;
        }
        catch(const std::exception& e)
        {
            std::cout << "Command input not recognized" << std::endl;
        }
        
    }
    return 0;
}