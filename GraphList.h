//
//  GraphList.hpp
//  constellations
//
//  Created by Jenna deBoisblanc on 8/29/17.
//
//

#ifndef GraphList_h
#define GraphList_h

#include "ofMain.h"
#include "Node.h"
#include <stdio.h>
#include "ofMain.h"
#include "AdjStruct.h"

#define vertexCount 100




class GraphList {
    
private:
    vector<Node> nodes;
    int numNodes = 0;
    AdjList* nodeList;
    
public:
    int currentNodeIndex;
    // originals
    GraphList();
    ~GraphList();
    void addEdge(int i, int j);
    void addDirectedEdge(int i, int j);
    void resetList();
//    void removeEdge(int i, int j);
//    bool isEdge(int i, int j);
   
    
    // display
    void display();
    void drawLineToCurrent(int x, int y);
    
    // set
    int getCurrentNode();
    void setCurrentNode(int n);
    void addNode(int x, int y);
    
    // save
    ofFile nodesFile;
    ofFile adjacencyFile;
   void save();
    void read();
    
    void checkNodeClick(int x, int y);
    int getClickedNode(int x, int y);
    void checkEdgeClick(int x, int y);
    bool hasCurrentNode();
    void moveCurrentNode(int dx, int dy);
    
    void printGraph();

	float getAngle(int x0, int y0, int x1, int y1);
    
    
};
#endif /* GraphList_h */
