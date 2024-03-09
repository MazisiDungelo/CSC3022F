#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <string>

namespace DNGMAZ001{

        // Create Tile object
        // Tile has position that it has in a board
        class Tile{
            private:
                // Declare positions of Tile on a board
                int x;
                int y;
                int width;
                int height;
                unsigned char** pixels;
            
            public:
                // Default constructor 
                Tile();
                // Custom constructor
                Tile(int x, int y,int width, int height, unsigned char** inputPixels);
                // Destructor
                ~Tile();
                // Copy Constructor
                Tile(const Tile& other);

                // Copy Assignment Operator
                Tile& operator=(const Tile& other);

                // Move Constructor
                Tile(Tile&& other) noexcept;

                // Move Assignment Operator
                Tile& operator=(Tile&& other) noexcept;

        
                unsigned char getPixel(int row, int col) const;
                unsigned char** getPixels() const;
                int getWidth() const;
                int getHeight() const;
                int getX() const;
                int getY() const;
                void swapPixels(Tile& other);
                // changes the Tile to blank
                void makeBlank();

    };
}

#endif