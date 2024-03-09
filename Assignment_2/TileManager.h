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
            unsigned char ** pixelData;
            Tile*** board;
            int numRows, numCols;
            std::vector<int> xpos;
            std::vector<int> ypos;

        public:
            TileManager(int gridSize, const std::string& imageName, int numMoves);
            ~TileManager();



            void readPGM(const std::string& imageName);
            void createImage(unsigned char **inputPixels,int width, int height, std::string name);
            void initializeBoard(int width, int height);
            std::pair<int, int> performRandomMove(int blankXpos, int blankYpos);
            void saveCurrentState(int move);
            void playGame();


    };

} 

#endif // TILEMANAGER_H