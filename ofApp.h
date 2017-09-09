#pragma once

#include "ofMain.h"
#include "GraphList.h"
#include "ofxKinectForWindows2.h"
#include <time.h>
#include <utility>

#define VISUALIZE   0
#define ADD_NODES   1
#define ADD_EDGES   2
#define MOVE_NODES  3
#define KINECT_TIMESHOT 4

struct Bone {
	float firstX;
	float firstY;
	float secondX;
	float secondY;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        int mode;
    
        //GRAPH
        GraphList graphL;
    
    
		// KINECT
		ofxKFW2::Device kinect;
		void initKinect();
		void updateKinect();
		void drawKinect();
		ofFile bonesFile;
		ofFile jointsFile;
		void saveKinect();
		void readKinect();
		vector<Bone> bones;
		int timesFile;
		time_t timeshot;
    
		
};
