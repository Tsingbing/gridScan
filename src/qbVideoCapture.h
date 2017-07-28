#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class qbVideoCapture {
public:
	ofPoint A;
	ofPoint B;
	ofPoint C;
	ofPoint D;

	ofxCvColorImage image;
	ofxCvColorImage image2;

	int cornerIndex = 1;

	ofVideoGrabber vidGrabber;
	ofImage imageVideo;
	int camWidth;
	int camHeight;

	void setup() {
		camWidth = 640;  // try to grab at this size.
		camHeight = 480;

		A = ofPoint(20, 20, 0);
		B = ofPoint(600, 20, 0);
		C = ofPoint(600, 400, 0);
		D = ofPoint(20, 400, 0);
		//we can now get back a list of devices.
		vector<ofVideoDevice> devices = vidGrabber.listDevices();

		for (int i = 0; i < devices.size(); i++) {

			if (devices[i].bAvailable) {
				ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
			}
			else {
				ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
			}
		}

		vidGrabber.setDeviceID(0);
		vidGrabber.setDesiredFrameRate(60);
		vidGrabber.initGrabber(camWidth, camHeight);

		ofSetVerticalSync(true);
	}

	void update() {
		ofBackground(100, 100, 100);
		vidGrabber.update();

		if (vidGrabber.isFrameNew())
		{
			imageVideo.setFromPixels(vidGrabber.getPixels());
		}
	}

	void draw() {
		//图像变形，代码执行顺序要注意，ABCD顶点要和image2匹配
		ofSetHexColor(0xffffff);
		image2 = imageVideo;
		image2.warpPerspective(A, B, C, D);
		image2.draw(20, 160,600,600);
		
		ofPushMatrix();
			ofTranslate(642, 162);
			vidGrabber.draw(0, 0);
			
			ofSetColor(255, 0, 0);
			ofFill();
			ofDrawCircle(A, 5.0);
			ofDrawCircle(B, 5.0);
			ofDrawCircle(C, 5.0);
			ofDrawCircle(D, 5.0);
		
			ofSetLineWidth(3.0);
			ofDrawLine(A, B);
			ofDrawLine(B, C);
			ofDrawLine(C, D);
			ofDrawLine(D, A);
		ofPopMatrix();
	}
};