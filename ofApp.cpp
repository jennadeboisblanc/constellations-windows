#include "ofApp.h"

int previewWidth = 640;
int previewHeight = 480;

//--------------------------------------------------------------
void ofApp::setup() {

	graphL = GraphList();

	initKinect();

	timesFile = 0;
	mode = VISUALIZE;

	// init bones
	auto boneAtlas = ofxKinectForWindows2::Data::Body::getBonesAtlas();
	int i = 0;
	for (auto bone : boneAtlas) {
		bones.push_back(Bone());
		bones[i].firstX = 0;
		bones[i].firstY = 0;
		bones[i].secondX = 0;
		bones[i].secondY = 0;
		i++;
	}

	ofSetWindowShape(previewWidth * 2, previewHeight * 2);
}

//--------------------------------------------------------------
void ofApp::update() {
	updateKinect();
	if (mode == KINECT_TIMESHOT) {
		time_t now = time(NULL);
		if (difftime(now, timeshot) > 1) {
			timeshot = now;
			saveKinect();
			timesFile++;
			if (timesFile > 20) {
				mode = VISUALIZE;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	//graphL.display();
	//drawKinect();

	if (mode == ADD_EDGES) {
		graphL.display();
		graphL.drawLineToCurrent(mouseX, mouseY);
	}
	else if (mode == ADD_NODES) {
		graphL.display();
		ofSetColor(255, 0, 0);
		ofFill();
		ofDrawCircle(mouseX, mouseY, 20);
	}
	else if (mode == KINECT_TIMESHOT) {
		time_t now = time(NULL);
		ofDrawBitmapString(std::to_string(10 - difftime(now,timeshot)), 100, 100);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 's') {
		graphL.save();
		graphL.printGraph();
	}
	else if (key == 'r') graphL.read();
	else if (key == 'a') mode = ADD_NODES;
	else if (key == 'e') mode = ADD_EDGES;
	else if (key == 'm') mode = MOVE_NODES;
	else if (key == 'v') {
		mode = VISUALIZE;
	}

	else if (key == 't') {
		mode = KINECT_TIMESHOT;
		timeshot = time(NULL);
		timesFile = 0;
	}

	else if (mode == MOVE_NODES) {
		if (graphL.hasCurrentNode()) {
			if (key == OF_KEY_UP) graphL.moveCurrentNode(0, -1);
			else if (key == OF_KEY_DOWN) graphL.moveCurrentNode(0, 1);
			else if (key == OF_KEY_RIGHT) graphL.moveCurrentNode(1, 0);
			else if (key == OF_KEY_LEFT) graphL.moveCurrentNode(-1, 0);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (mode == ADD_NODES) {
		graphL.addNode(mouseX, mouseY);
	}
	else if (mode == MOVE_NODES) {
		graphL.checkNodeClick(mouseX, mouseY);
	}
	else if (mode == ADD_EDGES) {
		graphL.checkEdgeClick(mouseX, mouseY);
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

//--------------------------------------------------------------
void ofApp::initKinect() {
	kinect.open();
	kinect.initDepthSource();
	kinect.initColorSource();
	kinect.initInfraredSource();
	kinect.initBodySource();
	kinect.initBodyIndexSource();
}

//--------------------------------------------------------------
void ofApp::updateKinect() {
	kinect.update();

	//--
	//Getting joint positions (skeleton tracking)
	//--
	//
	{
		auto bodies = kinect.getBodySource()->getBodies();
		for (auto body : bodies) {
			if (body.tracked) {
				for (auto joint : body.joints) {
					// now do something with the joints
					//ofDrawCircle(std::get<0>(joint).getPosition().x, std::get<0>(joint).getPosition().y, 30);
				}
			}
		}
	}
	//
	//--



	//--
	//Getting bones (connected joints)
	//--
	//
	/*{
		// Note that for this we need a reference of which joints are connected to each other.
		// We call this the 'boneAtlas', and you can ask for a reference to this atlas whenever you like
		auto bodies = kinect.getBodySource()->getBodies();
		auto boneAtlas = ofxKinectForWindows2::Data::Body::getBonesAtlas();

		for (auto body : bodies) {
			if (body.tracked) {
			int i = 0;
			for (auto bone : boneAtlas) {
				auto firstJointInBone = body.joints[bone.first];
				auto secondJointInBone = body.joints[bone.second];
				std::cout.precision(4);
				cout << body.joints[bone.first].getPosition().x << endl;
				bones[i].firstX = firstJointInBone.getPosition().x;
				bones[i].firstY = firstJointInBone.getPosition().y;
				bones[i].secondX = secondJointInBone.getPosition().x;
				bones[i].secondY = secondJointInBone.getPosition().y;
				//now do something with the joints
				i++;
			}
			}
		}
	}*/
	//
	//--
}

//--------------------------------------------------------------
void ofApp::drawKinect() {
	kinect.getDepthSource()->draw(0, 0, previewWidth, previewHeight);  // note that the depth texture is RAW so may appear dark

																	   // Color is at 1920x1080 instead of 512x424 so we should fix aspect ratio
	float colorHeight = previewWidth * (kinect.getColorSource()->getHeight() / kinect.getColorSource()->getWidth());
	float colorTop = (previewHeight - colorHeight) / 2.0;

	kinect.getBodySource()->drawProjected(0, 0, previewWidth*2, previewHeight*2);


	//kinect.getColorSource()->draw(previewWidth, 0 + colorTop, previewWidth, colorHeight);
	//kinect.getBodySource()->drawProjected(previewWidth, 0 + colorTop, previewWidth, colorHeight);

	//kinect.getInfraredSource()->draw(0, previewHeight, previewWidth, previewHeight);

	//kinect.getBodyIndexSource()->draw(previewWidth, previewHeight, previewWidth, previewHeight);
	//kinect.getBodySource()->drawProjected(previewWidth, previewHeight, previewWidth, previewHeight, ofxKFW2::ProjectionCoordinates::DepthCamera);
}

void ofApp::readKinect() {

	std::string n;
	ofBuffer buffer = ofBufferFromFile("bones" + std::to_string(timesFile) + ".txt");
	int i = 0;
	for (auto line : buffer.getLines()) {

		vector < string > result;

		result = ofSplitString(line, " ");

		if (i >= 0 && i < bones.size()) {
			bones[i].firstX = atoi(result[0].c_str());
			bones[i].firstY = atoi(result[1].c_str());
			bones[i].secondX = atoi(result[2].c_str());
			bones[i].secondY = atoi(result[3].c_str());
		}

		i++;
	}
}

void ofApp::saveKinect() {
	bonesFile.open("bones" + std::to_string(timesFile) + ".txt", ofFile::WriteOnly);
	
	for (int i = 0; i < bones.size(); i++) {
		//cout << bones[i].firstX << endl;
		bonesFile << bones[i].firstX << " " << bones[i].firstY << " " << bones[i].secondX << " " << bones[i].secondY << std::endl;
	}
	bonesFile.close();
}

