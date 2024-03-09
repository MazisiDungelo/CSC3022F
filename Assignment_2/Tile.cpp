#include "Tile.h"

namespace DNGMAZ001 {
    Tile::Tile() : x(0), y(0), width(0), height(0), pixels(nullptr){}
    Tile::Tile(int x,int y,int width,int height, unsigned char** inputPixels) : 
                        x(x),y(y),width(width),height(height)
                        
    {
        this->pixels = new unsigned char*[height];
        for (int i = y; i < y + height; ++i) 
        {
            this->pixels[i - y] = new unsigned char[width];
            for (int j = x; j < x + width; ++j)
            {
                this->pixels[i - y][j - x] = inputPixels[i][j];
            }
        }

    }

    Tile::~Tile() {
        for(int i = 0; i < this->getHeight(); i++)
        {
            delete[] pixels[i];
        }
        delete[] pixels;
        pixels = nullptr;
    }
    // Copy constructor
    // Deep copy elements of other Tile into this Tile
    Tile::Tile(const Tile& other) : x(other.x), y(other.y), width(other.width), height(other.height) {
        pixels = new unsigned char*[height];
        for (int i = 0; i < height; ++i) {
            pixels[i] = new unsigned char[width];
            for (int j = 0; j < width; ++j) {
                pixels[i][j] = other.pixels[i][j];
            }
        }
    }
    // Copy operator
    // Deep copy elements of Tile object into other Tile
    Tile& Tile::operator=(const Tile& other)
    {
        if (this != &other) // Check for self-assignment
        { 
            // Deallocate existing memory
            for (int i = 0; i < height; ++i) {
                delete[] pixels[i];
            }
            delete[] pixels;

            // Copy values from other
            x = other.x;
            y = other.y;
            width = other.width;
            height = other.height;

            // Allocate memory for pixels and copy pixel data
            pixels = new unsigned char*[height];
            for (int i = 0; i < height; ++i) {
                pixels[i] = new unsigned char[width];
                for (int j = 0; j < width; ++j) {
                    pixels[i][j] = other.pixels[i][j];
                }
            }
         }
        return *this;
    }
    // Move Constructor
    // Move contents of other Tile into this Tile
    Tile::Tile(Tile&& other) noexcept : x(other.x), y(other.y), width(other.width), height(other.height), pixels(other.pixels) {
        other.x = 0;
        other.y = 0;
        other.width = 0;
        other.height = 0;
        other.pixels = nullptr;
    }

    // Move Assignment Operator
    // Move contents of other Tile into this Tile
    Tile& Tile::operator=(Tile&& other) noexcept {
        if (this != &other) {
            // Deallocate existing memory
            for (int i = 0; i < height; ++i) {
                delete[] pixels[i];
            }
            delete[] pixels;

            // Move values from other
            x = other.x;
            y = other.y;
            width = other.width;
            height = other.height;
            pixels = other.pixels;

            // Reset other object
            other.x = 0;
            other.y = 0;
            other.width = 0;
            other.height = 0;
            other.pixels = nullptr;
        }
        return *this;
    }

    unsigned char Tile::getPixel(int row, int col) const 
    {
        return this->pixels[row][col];
    }
    unsigned char** Tile::getPixels() const 
    {
        return pixels;
    }
    int Tile::getWidth()const 
    {
        return this->width;
    }
    int Tile::getHeight()const 
    {
        return this->height;
    }
    void Tile::makeBlank() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            pixels[i][j] = 0; // Set to blank value
        }
    }
    }

}