#include "ofApp.h"
#include "qbGrid.h"
#include "qbVideoCapture.h"

qbGrid grid;
qbVideoCapture videoCapture;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(100, 100, 100);	

	// ���������������С�Ȳ���
	grid.setup(); 
	videoCapture.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	videoCapture.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// �ڣ�22��162����λ�û滭����
	videoCapture.draw();
	grid.draw(22,162);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
