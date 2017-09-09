//
//  Node.cpp
//  constellations
//
//  Created by Jenna deBoisblanc on 8/29/17.
//
//

#include "Node.h"


//--------------------------------------------------------------
Node::Node() {
    // default
}

Node::Node(std::string ID, int x, int y) {
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->diam = 15;
}

//void Node::addDestination(Node destination) {
//    adjacentNodes.push_back(destination);
//}

// problem??
//void Node::setAdjacentNodePointers(vector<Node*> adjNodePointers) {
//    adjacentNodes = adjNodePointers;
//}

//--------------------------------------------------------------
// get

float Node::getAngle(float x1, float x2, float y1, float y2) {
    // angle to actual point
    float dot = x1*x2 + y1*y2;      // dot product
    float det = x1*y2 - y1*x2;      // determinant
    float angle = atan2(det, dot);  // atan2(y, x) or atan2(sin, cos)
    return angle;
}

std::string Node::getID() {
    return this->ID;
}

int Node::getX() {
    return this->x;
}
int Node::getY() {
    return this->y;
}

//--------------------------------------------------------------
// display
void Node::display() {
    ofSetColor(255);
    if (mouseOver()) {
        ofSetColor(255, 0, 0);
    }
    ofFill();
    ofSetLineWidth(2);
    ofDrawCircle(x, y, 5);
    ofDrawBitmapString(ID, x, y-15);
    
//    if (mode != VISUALIZE) {
//        ofSetColor(0, 255, 0);
//        ofFill();
//        textSize(18);
//        ofDrawBitmapString(ID, x, y);dd
//    }
    
    //showDestinationLines();

}

//void Node::displayNeighbors(AdjListNode* tmp) {
//    int x1 = this->getX();
//    int y1 = this->getY();
//
//    while (tmp) {
//        tmp = tmp->next;
//        if (tmp) {
//            
//            // Not gonna work b/c can't get access to other nodes referenced
//                // so question is - add x, y to nodeList?
//            Node n = nodes.at(tmp->data);
//            int x2 = n.getX();
//            int y2 = n.getY();
//            ofDrawLine(x1, y1, x2, y2);
//        }
//    }
//
//}

void Node::displayEdge(Node n) {
    
}

//void Node::showDestinationLines() {
//    //cout << adjacentNodes.size() << std::endl;
//    for (int i = 0; i < adjacentNodes.size(); i ++) {
//        Node n = *adjacentNodes.at(i);
//        ofDrawLine(x, y, n.getX(), n.getY());
//    }
//}

bool Node::mouseOver() {
    int mx = ofGetAppPtr()->mouseX;
    int my = ofGetAppPtr()->mouseY;
    int x = mx - this->getX();
    int y = my - this->getY();
    float d = sqrt(x*x + y*y);
    return (d < diam);
}

bool Node::mouseOver(int mx, int my) {
    int x = mx - this->getX();
    int y = my - this->getY();
    float d = sqrt(x*x + y*y);
    return (d < diam);
}

//--------------------------------------------------------------
// update
void Node::move(int dx, int dy) {
    this->x +=dx;
    this->y += dy;
}

void Node::set(std::string s, int x, int y) {
    this->ID = s;
    this->x = x;
    this->y = y;
}

void Node::set(int x, int y) {
    this->x = x;
    this->y = y;
}

//--------------------------------------------------------------
// save
std::string Node::printData() {
    std::string s = ID + " " + std::to_string(getX()) + " " + std::to_string(getY());
    return s;
}


