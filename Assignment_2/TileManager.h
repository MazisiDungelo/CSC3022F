#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <string>
#include <vector>
#include <utility>

namespace DNGMAZ001 {

    class Tile;

    class TileManager {

        private:
            int gridSize;
            int numMoves;
            int width, height;
            unsigned char ** pixelData; // Stores pixels read from input image
            Tile*** board;
            int numRows, numCols; // Stores number of rows and columns for board

            // Stores the index of Tiles in a board
            std::vector<int> xpos; 
            std::vector<int> ypos;

        public:
            // Custom constructor
            TileManager(int gridSize, const std::string& imageName, int numMoves);
            // Destructor
            ~TileManager();



            void readPGM(const std::string& imageName);
            void createImage(unsigned char **inputPixels,int width, int height, std::string name);
            void initializeBoard(int width, int height);
            // Changes the position of blank tile into other
            // Accept position of blank tile
            // Randomize next position for blank Tile
            std::pair<int, int> performRandomMove(int blankXpos, int blankYpos);
            void saveCurrentState(int move);
            void playGame();


    };

} 

#endif // TILEMANAGER_H