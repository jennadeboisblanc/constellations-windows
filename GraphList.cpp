//
//  GraphList.cpp
//  constellations
//
//  Created by Jenna deBoisblanc on 9/1/17.
//
//

#include "GraphList.h"

//
//  GraphList.cpp
//  constellations
//
//  Created by Jenna deBoisblanc on 8/29/17.
//
//

#include "GraphList.h"
#include <stdio.h>

GraphList::GraphList() {
    this->currentNodeIndex = NULL;
    this->numNodes = 0;
    nodeList = new AdjList [vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        nodeList[i].head = NULL;  		//linking head of all vertices (array) to NULL ,it doesn't store any number only stores HEAD
    }
    for (int i = 0; i < vertexCount; i++) {
        nodes.push_back(Node(std::to_string(i), -10, -10));
    }
//    nodes.at(0).set(150, 150);
//    nodes.at(1).set(250, 100);
//    nodes.at(2).set(100, 100);
    
    //addEdge(0,1);
    
    //addEdge(1,2);
    //addEdge(1,0);
    //addEdge(2, 0);
}


void GraphList::addEdge(int src, int dest) {
    /*
     * Adding Edge to Graph
     * https://github.com/JerryGoyal/data-structure/blob/master/graph%20implementation%20using%20adjacency%20list%20linked%20list%20array.cpp
     */

    
    AdjListNode* newNode = new AdjListNode;  //newNode stores both data(dest) and *next pointer
    //Node* newNode = &nodes.at(src);
    newNode->data = dest;					//consider src = 0 and dest = 1		0<----->1 for undirected graph
    newNode->next = NULL;		//  1----->NULL
    //adding nodes at beginning of each list just like in linked list//
    newNode->next = nodeList[src].head;		//*next(of dst) storing address of head->next node i.e.. 1--->2 (first node from head)
    nodeList[src].head = newNode;				//	0-->1-->2
    
    // Since graph is undirected, add an edge from dest to src also
    //Node* destNode = &nodes.at(dest); 				 //now newNode storing data(src)
    newNode = new AdjListNode;
    newNode->data = src;
    newNode->next = NULL;				// 0--->NULL
    
    newNode->next = nodeList[dest].head;	// 0---->NULL (bcuz.. 1-->NULL)
    nodeList[dest].head = newNode;			// 1---->0
    
    newNode = NULL;
    delete newNode;
}

// use this for loading graph to prevent duplicates
void GraphList::addDirectedEdge(int src, int dest) {
    AdjListNode* newNode = new AdjListNode;  //newNode stores both data(dest) and *next pointer
    //Node* newNode = &nodes.at(src);
    newNode->data = dest;					//consider src = 0 and dest = 1		0<----->1 for undirected graph
    newNode->next = NULL;		//  1----->NULL
    //adding nodes at beginning of each list just like in linked list//
    newNode->next = nodeList[src].head;		//*next(of dst) storing address of head->next node i.e.. 1--->2 (first node from head)
    nodeList[src].head = newNode;				//	0-->1-->2
}

void GraphList::display(){
    int v;
    for (v = 0; v < numNodes; ++v) {
        nodes.at(v).display();
        ofSetColor(255);
        
        // draw lines between nodes
        AdjListNode* tmp = nodeList[v].head;		//tmp has the address of (0,1..)vertex head

        int x1, y1;
        Node n = nodes.at(v); // could get to the point where this call isn't necessary- just tmp->x, tmp->y (that x, y is saved 2x)
        x1 = n.getX();
        y1 = n.getY();
        
        while (tmp) {
            n = nodes.at(tmp->data);
            int x2 = n.getX();
            int y2 = n.getY();
            ofDrawLine(x1, y1, x2, y2);
           tmp = tmp->next;
        }
    }
}

void GraphList::read() {
    resetList();
    ofBuffer buffer = ofBufferFromFile("nodesGrid.txt");
    int i = -1;
    for (auto line : buffer.getLines()){
        if (i == -1) numNodes = atoi(line.c_str());
        else {
            vector < string > result;
            
            cout << numNodes << endl;
            result = ofSplitString(line, " ");
            
            if (i >= 0 && i < nodes.size()) {
                nodes.at(i).set(result[0], atoi(result[1].c_str()), atoi(result[2].c_str()));
            }
        }
        i++;
    }
    
    ofBuffer buffer2 = ofBufferFromFile("adjacencyListGrid.txt");
    i = 0;
    for (auto line : buffer2.getLines()){
        vector < string > result;
        result = ofSplitString(line, " ");
        if (result.size() > 1) {
            for (int j = 1; j < result.size(); j++) {
                addDirectedEdge(atoi(result[0].c_str()), atoi(result[j].c_str()));
            }
        }
        i++;
    }
}

void GraphList::addNode(int mx, int my) {
    if (numNodes < nodes.size()) {
        nodes.at(numNodes).set(mx, my);
    }
    numNodes++;
}


bool GraphList::hasCurrentNode() {
    return (currentNodeIndex > -1);
}

void GraphList:: moveCurrentNode(int dx, int dy) {
    nodes.at(currentNodeIndex).move(dx, dy);
}

int GraphList::getClickedNode(int mx, int my) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes.at(i).mouseOver(mx, my)) {
            return i;
        }
    }
    return -1;
}

void GraphList::checkEdgeClick(int mx, int my) {
    int prevNodeIndex = currentNodeIndex;
    currentNodeIndex = getClickedNode(mx, my);
    //cout << currentNodeIndex << " " << prevNodeIndex << std::endl;
    // if we actually clicked on a star to create an edge
    if (currentNodeIndex >= 0) {
        // if we've already selected a star
        if (prevNodeIndex >= 0) {
            // oops, clicked on the same star
            if (prevNodeIndex == currentNodeIndex) {
                currentNodeIndex = -1;
            }
            // clicked a new star! let's add an edge
            else {
                // add link in adjacency matrix
                addEdge(prevNodeIndex, currentNodeIndex);
            }
        }
    }
}


void GraphList::checkNodeClick(int mx, int my) {
    currentNodeIndex = getClickedNode(mx, my);
}
//
//Node* GraphList::getClickedNode(int mx, int my) {
//    for (int i = 0; i < nodes.size(); i++) {
//        if (nodes.at(i).mouseOver(mx, my)) {
//            return &nodes.at(i);
//        }
//    }
//    return NULL;
//    
//}
//
//void GraphList::checkEdgeClick(int mx, int my) {
//    Node* prevNodeIndex = currentNodeIndex;
//    currentNodeIndex = getClickedNode(mx, my);
//    
//    if (currentNodeIndex != NULL) {
//        cout << currentNodeIndex->data << " " << prevNodeIndex << std::endl;
//    }
//    // if we actually clicked on a star to create an edge
//    if (currentNodeIndex) {
//        // if we've already selected a star
//        if (prevNodeIndex) {
//            // oops, clicked on the same star
//            if (prevNodeIndex == currentNodeIndex) {
//                currentNodeIndex = NULL;
//            }
//            // clicked a new star! let's add an edge
//            else {
//                // add link in list
//                addEdge(prevNodeIndex->data, currentNodeIndex->data);
//            }
//        }
//    }
//}
//bool GraphList::hasCurrentNode() {
//    return (currentNodeIndex);
//}
//
//void GraphList:: moveCurrentNode(int dx, int dy) {
//    currentNodeIndex->move(dx, dy);
//}

void GraphList::printGraph(){
    int v;
    for (v = 0; v < vertexCount; ++v){
        AdjListNode* tmp = nodeList[v].head;		//tmp has the address of (0,1..)vertex head
        cout<<"\n Adjacency list of vertex "<<v<<"\n head ";
        while (tmp)
        {
            cout<<"-> "<<tmp->data;
            tmp = tmp->next;
        }
        cout<<endl;
    }
}

void GraphList::save(){
    nodesFile.open("nodes.txt",ofFile::WriteOnly);
    nodesFile << numNodes << endl;
    for (int i = 0; i < nodes.size(); i++) {
        nodesFile << nodes.at(i).printData() << std::endl;
    }
    nodesFile.close();

    int v;
    adjacencyFile.open("adjacencyList.txt",ofFile::WriteOnly);
    for (v = 0; v < vertexCount; ++v){
        AdjListNode* tmp = nodeList[v].head;		//tmp has the address of (0,1..)vertex head
        adjacencyFile <<"\n" << v;
        while (tmp) {
            adjacencyFile <<" "<< tmp->data;
            tmp = tmp->next;
        }
    }
    adjacencyFile.close();
}


int GraphList::getCurrentNode() {
    //cout << currentNodeIndex << std::endl;
    return currentNodeIndex;
}

void GraphList::setCurrentNode(int num) {
    this->currentNodeIndex = num;
}

void GraphList::drawLineToCurrent(int x, int y) {
    ofSetColor(255);
    if (currentNodeIndex > -1 && currentNodeIndex < nodes.size()) {
        ofDrawLine(nodes.at(currentNodeIndex).getX(), nodes.at(currentNodeIndex).getY(), x, y);
    }
}

void GraphList::resetList() {
    nodeList = NULL;
    delete nodeList;
    nodeList = new AdjList [vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        nodeList[i].head = NULL;  		//linking head of all vertices (array) to NULL ,it doesn't store any number only stores HEAD
    }
    
}

GraphList::~GraphList() {
    nodeList = NULL;
    delete nodeList;
}


float GraphList::getAngle(int x0, int y0, int x1, int y1) {
	return atan2((y1 - y0)*1.0, (x1 - x0)*1.0);
}