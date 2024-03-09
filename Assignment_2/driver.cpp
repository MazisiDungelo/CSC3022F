#include "TileManager.h"
#include "Tile.h"

int main(int argc, char* argv[]) {
    // Set the grid size, image name, and number of moves
    int gridSize = 3; 
    std::string imageName = "mona512.pgm"; 
    int numMoves = 2; 

    // Parse command line arguments
    if (argc == 4) {
        gridSize = std::atoi(argv[1]);
        numMoves = std::atoi(argv[2]);
        imageName = argv[3];
    } else {
        std::cerr << "Usage: " << argv[0] << " <gridSize> <numMoves> <inputImageName>\n";
        return 1;  // Return error code
    }
    // Create a TileManager object
    DNGMAZ001::TileManager tileManager(gridSize, imageName, numMoves);

    // Play the game
    tileManager.playGame();

    return 0;
}