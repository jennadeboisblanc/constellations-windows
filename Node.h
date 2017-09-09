//
//  Node.hpp
//  constellations
//
//  Created by Jenna deBoisblanc on 8/29/17.
//
//

#ifndef Node_h
#define Node_h

#include "ofMain.h"
#include <stdio.h>
#include <string>
#include <map>
#include <iterator>
#include <math.h>
#include <stdlib.h>
#include "ofMath.h"
#include "ofGraphics.h"
#include "AdjStruct.h"

class Node {

    private:
        int x;
        int y;
        int diam;
        std::string ID;
        //vector<Node*> adjacentNodes;
    
    public:
        // create
        Node();
        Node(std::string ID, int x, int y);
    
        Node* next;
        int data;
    
        //void addDestination(Node destination);
        void setAdjacentNodePointers(vector<Node*> adjNodePointers);
    
        // get
        Node getAdjNodeByAngle(float angle, float len);
        float getAngle(float x1, float y1, float x2, float y2);
        std::string getID();
        int getX();
        int getY();

        // display
        void display();
        void displayEdge(Node n);
        void showDestinationLines();
        bool mouseOver();
        bool mouseOver(int x, int y);
        //void displayNeighbors(AdjListNode* tmp);
    
        // update
        void set(std::string, int x, int y);
        void set(int x, int y);
        void move(int dx, int dy);
    
        // save
        std::string printData();
    
};

#endif /* Node_h */




