#ifndef ConnComp_H
#define ConnComp_H

#include <iostream>
#include <vector>
#include <utility>
#include <set>

namespace DNGMAZ001
{
     class ConnectedComponent
    {

        public:
            // ConnectCompoments variables;
            int numOfPixels;
            int pixelID;
            std::vector< std::pair<int,int> > coordinates;
            std::multiset< std::pair<int,int> > allPairs;

            ConnectedComponent();
            ConnectedComponent(int noOfPixels, int id,std::vector< std::pair<int,int> > coordinates);
            ~ConnectedComponent();
            // Copy constructor
            ConnectedComponent(const ConnectedComponent& other);
            // Move constructor 
            ConnectedComponent(ConnectedComponent&& other);
            // Copy assignment operator
            ConnectedComponent& ConnectedComponent::operator=(const ConnectedComponent& other);
            // Move assigment operator
            ConnectedComponent& ConnectedComponent::operator=(const ConnectedComponent&& other);

            
            bool compareComponents (const std::pair<int,int> & lhs,const std::pair<int,int> & rhs);
        
    };
 }
 #endif