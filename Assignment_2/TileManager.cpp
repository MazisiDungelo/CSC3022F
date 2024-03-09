#include "TileManager.h"
#include "Tile.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <vector>

namespace DNGMAZ001
{
    TileManager::TileManager(int gridSize, const std::string& imageName, int numMoves)
        : gridSize(gridSize), numMoves(numMoves)
    {
        readPGM(imageName);
        initializeBoard(width, height);
    }


    TileManager::~TileManager() 
    {
        for (int i = 0; i < gridSize; ++i) 
        {
            delete[] board[i];
        }
        delete board;
    }

    void TileManager::playGame() 
    {
        int blankXpos, blankYpos;
        blankXpos = numCols*(float(gridSize-1)/gridSize);
        blankYpos = (float(gridSize-1)/gridSize)*numRows;
        for (int move = 1; move <= numMoves; ++move) 
        {
            // Perform random move of Tiles
            // Retrieve  the current position of blank Tile
            std::pair<int, int> blankPos = performRandomMove(blankXpos,blankYpos);
            blankXpos = blankPos.first;
            blankYpos = blankPos.second;
            // Save the current board
            saveCurrentState(move);
        }
    }

    void TileManager::readPGM(const std::string& imageName) 
    {
        name = imageName;
        std::ifstream image(imageName);
        std::stringstream ss;
        if (image.is_open())
        {
            std::string line;
            // read version line
            getline(image, line);
            std::string version = line;
            // read comment line
            std::string comment;
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

                // Convert substrings to integers
                TileManager::width = std::stoi(widthStr);
                TileManager::height = std::stoi(heightStr);
            }
            ss << image.rdbuf();
            // read max intensity value
            int maxIntensity;
            ss >> maxIntensity;

            // initialize array of unsigned character of pixels 
            TileManager::pixelData = new unsigned char *[TileManager::height];
            for (int i=0; i < height; ++i)
            {
                TileManager::pixelData[i] = new unsigned char [TileManager::width];
                for (int j=0; j < width; ++j)
                {
                    char pixel;
                    ss >> pixel;
                    TileManager::pixelData[i][j] = static_cast<unsigned char>(pixel); //copy the pixel unto pixelData array
                }
            }
            image.close();
            

        }
    }    
    void TileManager::createImage(unsigned char **inputPixels,int width, int height, std::string name)
    {
        std::string filename = name;
        std::ofstream outfile(filename);
        if (outfile.is_open()) 
        {
            // Write the PGM header
            outfile << "P2" << std::endl;
            outfile << "# Output PGM File" << std::endl;
            outfile << width << " " << height << std::endl;
            outfile << "255" << std::endl;

            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    unsigned char pixel = inputPixels[i][j];
                    outfile << std::setw(3) << static_cast<int>(pixel) << " ";
                }
            }
            outfile.close();

            std::cout << "Saved current state to: " << filename << std::endl;
        }
    }
    //make image board made of tiles
    void TileManager::initializeBoard(int width, int height) 
    {
        int tileHeight = height/gridSize; 
        int tileWidth = width/gridSize; 

        numRows = gridSize*tileHeight;  // Set the number of rows of the board
        numCols = gridSize*tileWidth;  // Set the number of cols of the board

        board = new Tile**[numRows];
        for (int i =0; i < numRows; i++)
        {
            board[i] = new Tile*[numCols];
        }
        int in = 1;
        for (int i = 0; i < numRows; i+=tileHeight) 
        {
            for (int j = 0; j < numCols; j+=tileWidth) 
            {
                 if (i < tileHeight*gridSize && j < tileWidth*gridSize)
                 {

                    Tile* tile = new Tile(i, j, tileWidth, tileHeight, pixelData); 
                    // Checks whether the Tile is not in the right bottom corner
                    // Changes it and make it blank
                    if (i == (gridSize-1)*tileHeight && j == (gridSize-1)*tileWidth)
                        tile->makeBlank(); 

                    board[i][j] = tile; // Create tiles and add them unto rows
                    xpos.push_back(i); // Stores the x positions of the Tile
                    ypos.push_back(j); // Stores the y positions of the Tile
                 }

            }
        }
    }

    // Changes the position of blank tile into other
    // Accept position of blank tile
    // Randomize next position for blank Tile
    std::pair<int, int> TileManager::performRandomMove(int blankXpos, int blankYpos)
    {
        // Get the random x and y position from the list of x positions and y positions available in a board
        int randomXpos = xpos[rand() % xpos.size()]; 
        int randomYpos = ypos[rand() % ypos.size()];
        bool bothChanged = (blankXpos != randomXpos) && (blankYpos != randomYpos); // if both changed , this means it has moved to an incorect direction
        bool repeat = (randomXpos == blankXpos) && (randomYpos == blankYpos);
        bool within = ((abs(randomXpos-blankXpos) > (numRows/gridSize)) || (abs(randomYpos-blankYpos) > (numCols/gridSize))); 
        while (bothChanged || repeat || within) 
        {
            randomXpos = xpos[rand() % xpos.size()]; 
            randomYpos = ypos[rand() % ypos.size()];

            bothChanged = (blankXpos != randomXpos) && (blankYpos != randomYpos);
            repeat = (randomXpos == blankXpos) && (randomYpos == blankYpos);
            within = ((abs(randomXpos-blankXpos) > (numRows/gridSize)) || (abs(randomYpos-blankYpos) > (numCols/gridSize)));
        }  
        // Swap the Tile in the random position with the blank Tile
        Tile* tile = board[blankXpos][blankYpos];
        Tile* temp = tile;
        tile->swapPixels(*board[randomXpos][randomYpos]);
        board[blankXpos][blankYpos] = board[randomXpos][randomYpos];
        board[randomXpos][randomYpos] = temp;

        return std::make_pair(randomXpos,randomYpos);
        
    }
        
        

    void TileManager::saveCurrentState(int move, std::string name) 
    {
            // Iterate over the tiles in the board
            int tileHeight = numRows/gridSize;
            int tileWidth = numCols/gridSize;
            int n=0;
            unsigned char** new_board = new unsigned char*[numRows];
            for (int i=0; i < numRows; i++)
            {
                new_board[i] = new unsigned char[numCols];
            }
            for (int i = 0; i < numRows; i+=tileHeight) 
            {
                
                for (int j = 0; j < numCols; j+=tileWidth) 
                {
                    if (i < numCols && j < numRows)
                    {
                        Tile* tile = board[i][j];
                        

                        if (tile != nullptr)
                        {
                            for (int row = 0; row < tileHeight; ++row) 
                            {
                                for (int col = 0; col < tileWidth; ++col)
                                {
                                    unsigned char pixel = tile->getPixels()[row][col];
                                    new_board[row+tile->getY()][col+tile->getX()] = pixel;
                                }
                                
                            }
                        }
                    }

                    
                }
                
            }
            createImage(new_board,numRows,numRows,name+"-"+std::to_string(move));
        } 

    }
}
