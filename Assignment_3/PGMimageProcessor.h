#ifndef PGMIMAGEPROC_H
#define PGMIMAGEPROC_H

#include "ConnectedComponent.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

namespace DNGMAZ001
{
    class PGMimageProcessor
    {
        private:
            // DATA
            std::vector<std::shared_ptr<ConnectedComponent>> connectedComponents;
            std::string filename;
            int imageWidth, imageHeight;
            std::string imageVersion;
            int ** selectedPixels;
            int lastId = 0;
                
        public:
            PGMimageProcessor();
            PGMimageProcessor(std::string inFilename);
            ~PGMimageProcessor();
                    //Method declaration
        
            // prints out all the component data (entries do not have to be sorted) as well as the total
            // component number and the sizes of the smallest and largest components.
            void printAll();
            // Assigns id to components
            int assignID();

            // Process the input image to extract all the connected components,
            // based on the supplied threshold (0...255) and excluding any components
            // of less than the minValidSize. The final number of components that
            // you store in your container (after discarding undersized one)
            // must be returned.
            int extractComponents(unsigned char threshold, int minValidSize);

            // Iterate - with an iterator - though your container of connected
            // components and filter out (remove) all the components which do not
            // obey the size criteria pass as arguments. The number remaining
            // after this operation should be returned.
            int filterComponentsBySize(int minSize, int maxSize);

            // Create a new PGM file which contains all current components
            // (255=component pixel, 0 otherwise) and write this to outFileName as a
            // valid PGM. the return value indicates success of operation
            bool writeComponents(const std::string & outImageName);

            // Retrieve number of components
            int getComponentCount(void) const;     

            // Retrieve number of pixels in largest component
            int getLargestSize(void) const;

            // Retrieve number of pixels in smallest component
            int getSmallestSize(void) const;

            //print the data for a component to std::cout
            // see ConnectedComponent class;
            // print out to std::cout: component ID, number of pixels
            void printComponentData(const ConnectedComponent & theComponent) const;
            // Check valid coordinates
            int validCoord(int x, int y, int width, int height);
            ConnectedComponent bfs(int h, int w, unsigned char ** data,int x, int y, int color, int ** visitedPixels);  
        
    };
}
#endif
