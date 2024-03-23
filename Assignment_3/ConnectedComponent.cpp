#include "ConnectedComponent.h"

namespace DNGMAZ001
{
    // Default constructor
    ConnectedComponent::ConnectedComponent() : numOfPixels(0), pixelID(0), coordinates(), allPairs()
    {}
    // Custom constructor
    ConnectedComponent::ConnectedComponent(int noOfPixels, int id,std::vector< std::pair<int,int> > coordinates):
                                            numOfPixels(noOfPixels), pixelID(id), coordinates(coordinates)
    {}
    ConnectedComponent::~ConnectedComponent(){}
    // Copy Constructor
    ConnectedComponent::ConnectedComponent(const ConnectedComponent& other) {
        numOfPixels = other.numOfPixels;
        pixelID = other.pixelID;
        coordinates = other.coordinates;
        allPairs = other.allPairs;
    }
    // Move Constructor
    ConnectedComponent::ConnectedComponent(ConnectedComponent&& other) noexcept :
                                            numOfPixels(other.numOfPixels), pixelID(other.pixelID),
                                            coordinates(std::move(other.coordinates)), allPairs(std::move(other.allPairs)) 
    {
        other.numOfPixels = 0;
        other.pixelID = 0;
    }
    // Copy Assignment Operator
    ConnectedComponent& ConnectedComponent::operator=(const ConnectedComponent& other) {
        if (this != &other) {
            numOfPixels = other.numOfPixels;
            pixelID = other.pixelID;
            coordinates = other.coordinates;
            allPairs = other.allPairs;
        }
        return *this;
    }
    // Move Assignment Operator
    ConnectedComponent& ConnectedComponent::operator=(ConnectedComponent&& other) noexcept {
        if (this != &other) {
            numOfPixels = other.numOfPixels;
            pixelID = other.pixelID;
            coordinates = std::move(other.coordinates);
            allPairs = std::move(other.allPairs);
            other.numOfPixels = 0;
            other.pixelID = 0;
        }
        return *this;
    }    
}