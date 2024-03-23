#include "PGMimageProcessor.h"

#include <iostream>
#include <fstream>
#include <utility>
#include <queue>
#include<iterator> 

using namespace DNGMAZ001
{
    PGMimageProcessor::PGMimageProcessor()
    {

    }
    PGMimageProcessor::PGMimageProcessor(std::string inFilename) : filename(inFilename)
    {

    }
    PGMimageProcessor::~PGMimageProcessor()
    {

    }

    void PGMimageProcessor::printAll();

    int PGMimageProcessor::assignID()
    {

    }

    int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
    {

    }

    int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
    {

    }

    bool writeComponents(const std::string & outFileName)
    {

    }

    int PGMimageProcessor::getComponentCount(void) const
    {

    }     

    int PGMimageProcessor::getLargestSize(void) const
    {

    }

    int PGMimageProcessor::getSmallestSize(void) const 
    {

    }

    void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const
    {

    }

    ConnectedComponent PGMimageProcessor::bfs(int n, int m, unsigned char ** data,int x, int y, int color, int ** visitedPixels)
    {
        
    }
}