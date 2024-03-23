#include "PGMimageProcessor.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <queue>
#include<iterator> 

namespace DNGMAZ001
{
    PGMimageProcessor::PGMimageProcessor()
    {

    }
    PGMimageProcessor::PGMimageProcessor(std::string inFilename) : filename(inFilename)
    {

    }
    PGMimageProcessor::~PGMimageProcessor()
    {
        for (int i=0; i < imageHeight; ++i)
        {
            delete selectedPixels[i];
        }
        delete selectedPixels;
    }

    void PGMimageProcessor::printAll()
    {
        std::cout<< "Total components: "<<getComponentCount()<<std::endl;
        std::cout<< "No. of pixel of smallest component: "<<getSmallestSize()<<std::endl;
        std::cout<< "No. of pixel of largest component: "<<getLargestSize()<<std::endl;
        std::cout << "Components:" << std::endl;
        for (int i = 0; i < connectedComponents.size(); ++i)
        {
            printComponentData(*connectedComponents.at(i));
        }
    }

    int PGMimageProcessor::assignID()
    {
        return lastId++;
    }

    int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
    {
        std::ifstream image(filename);
        std::stringstream ss;
        if (image.is_open())
        {
            std::string line;

            // Read version line
            getline(image,line);
            imageVersion = line;
            // Read the comments lines
            std::string  comment;
            while (getline(image, line) && line.find("#") == 0)
            {
                comment += line;
            }
            // read width and height
            size_t spacePos = line.find(' ');  // Find the position of the space character

            if (spacePos != std::string::npos) 
            {
                // Extract substrings before and after the space
                std::string widthStr = line.substr(0, spacePos);
                std::string heightStr = line.substr(spacePos + 1);

                imageWidth = std::stoi(widthStr);
                imageHeight = std::stoi(heightStr);
            }
            ss << image.rdbuf();
            // read max intensity value
            int maxIntensity;
            ss >> maxIntensity;

            unsigned char **pixels = new unsigned char *[imageHeight];
            for (int i=0; i < imageHeight; ++i)
            {
                pixels[i] = new unsigned char[imageWidth];
            }
            for (int x=0; x < imageHeight; ++x)
            {
                for (int y=0; y < imageWidth; ++y)
                {
                    char pixel;
                    ss >> pixel;
                    pixels[x][y] = static_cast<unsigned char>(pixel);
                }
            }
            std::shared_ptr<ConnectedComponent> temp;
            ConnectedComponent component;
            // Create visited array
            selectedPixels = new int *[imageHeight];
            for (int i=0; i < imageHeight; ++i)
            {
                selectedPixels[i] = new int[imageWidth];
            }

            for (int x=0; x < imageHeight; ++x)
            {
                for (int y=0; y < imageWidth; ++y)
                {
                    selectedPixels[x][y] = 0;
                }
            }

            for (int x=0; x < imageHeight; ++x)
            {
                for (int y=0; y < imageWidth; ++y)
                {
                    if (pixels[x][y] >= threshold)
                    {
                        component = bfs(imageHeight, imageWidth,pixels,x,y,maxIntensity,selectedPixels);
                        temp.reset(new ConnectedComponent(component.numOfPixels,component.pixelID,component.coordinates));
                        connectedComponents.push_back(temp);
                    }
                }
            } 

            for (int i=0; i < imageHeight; ++i)
            {
                delete pixels[i];
            }
            delete pixels;  
        }
        image.close();
        return connectedComponents.size();


    }

    int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
    {
        std::vector<std::shared_ptr<ConnectedComponent>>::iterator ptr;
        int reduction = 0; 
        // Filtering vector elements using begin() and end()
        for (ptr = connectedComponents.begin(); ptr < connectedComponents.end(); ++ptr)
            {
                int pixelNo = (*ptr)->numOfPixels;
                if( pixelNo < minSize || pixelNo > maxSize){
                    for (int i = 0; i < (*ptr)->coordinates.size(); ++i)
                    {
                        std::cout << "I'm here" << std::endl;
                        int x = (*ptr)->coordinates.at(i).first;
                        int y = (*ptr)->coordinates.at(i).second;
                        selectedPixels[x][y]= 0;
                    }
                    connectedComponents.erase(ptr);
                    reduction++;
                }
            }
        
        return connectedComponents.size()-reduction;
    }

    bool PGMimageProcessor::writeComponents(const std::string & outImageName)
    {
        std::string filename = outImageName;
        std::ofstream outfile(filename);
        if (outfile.is_open())
        {
            // Write the image
            outfile << imageVersion << std::endl;
            outfile << imageWidth << " " << imageHeight << std::endl;
            outfile << "255" << std::endl;

            for (int x = 0; x < imageHeight; ++x)
            {
                for (int y = 0; y < imageWidth; ++y)
                {
                    if (selectedPixels[x][y] == 0) 
                        outfile << char(0);
                    else 
                        outfile << char(255);
                }
            }

            
        }
        outfile.close();
        return true;
    }

    int PGMimageProcessor::getComponentCount(void) const
    {
        return connectedComponents.size();
    }     

    int PGMimageProcessor::getLargestSize(void) const
    {
        int largestSize = (*connectedComponents.at(0)).numOfPixels;
        for (int i = 1; i < connectedComponents.size(); ++i)
        {
            if ((*connectedComponents.at(i)).numOfPixels > largestSize)
                largestSize = (*connectedComponents.at(i)).numOfPixels;
        }
        
        return largestSize;
    }

    int PGMimageProcessor::getSmallestSize(void) const 
    {
        if (connectedComponents.size() == 0) return 0; 

        int smallestSize = (*connectedComponents.at(0)).numOfPixels;

        for (int i = 1; i < connectedComponents.size(); ++i)
        {
            if ((*connectedComponents.at(i)).numOfPixels < smallestSize) 
                smallestSize = (*connectedComponents.at(i)).numOfPixels;
        }
        
        return smallestSize;
    }

    void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const
    {
        std::cout<< " ID: "<< theComponent.pixelID<< " number of pixels = "<< theComponent.numOfPixels<<std::endl;
    }

    ConnectedComponent PGMimageProcessor::bfs(int h, int w, unsigned char ** data,int x, int y, int color, int ** selectedPixels)
    {
        ConnectedComponent temp;
        temp.pixelID = assignID();
        temp.numOfPixels = 0;

        // Create queue for bfs
        std::queue<std::pair<int, int> > obj;

        // Pushing pair of {x, y}
        obj.push({ x, y });

        // Marking {x, y} as visited
        selectedPixels[x][y] = 1;
        temp.numOfPixels = data[x][y];
        // Until queue is empty
        while (obj.empty() != 1)
        {

        // Extracting front pair
        std::pair<int, int> coord = obj.front();
        int x = coord.first;
        int y = coord.second;
        int preColor = data[x][y];

        data[x][y] = color;
            
        // Pop front pair of queue
        obj.pop();

        // Upside Pixel or Cell
        if (validCoord(x + 1, y, h, w)
            && selectedPixels[x + 1][y] == 0
            && data[x + 1][y] >= preColor)
        {
            obj.push({ x + 1, y });
           selectedPixels[x + 1][y] = 1;
            temp.coordinates.push_back(std::make_pair(x + 1,y));
        }
            
        // Downside Pixel or Cell
        if (validCoord(x - 1, y, h, w)
            && selectedPixels[x - 1][y] == 0
            && data[x - 1][y] >= preColor)
        {
            obj.push({ x - 1, y });
            selectedPixels[x - 1][y] = 1;
            temp.coordinates.push_back(std::make_pair(x - 1,y));
        }
            
        // Right side Pixel or Cell
        if (validCoord(x, y + 1, h, w)
            && selectedPixels[x][y + 1] == 0
            && data[x][y + 1] >= preColor)
        {
            obj.push({ x, y + 1 });
            selectedPixels[x][y + 1] = 1;
            temp.coordinates.push_back(std::make_pair(x,y+1));
        }
            
        // Left side Pixel or Cell
        if (validCoord(x, y - 1, h, w)
            && selectedPixels[x][y - 1] == 0
            && data[x][y - 1] >= preColor)
        {
            obj.push({ x, y - 1 });
            selectedPixels[x][y - 1] = 1;
            temp.coordinates.push_back(std::make_pair(x,y- 1));
        }
        }
        return temp;
    }

    int PGMimageProcessor::validCoord(int x, int y, int width, int height)
    {
    
        if (x < 0 || y < 0 || x >= width || y >= height ) {
            return 0;
        }
        return 1;
    }
 
}