#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCsv.h"

class qbVideoCapture {
public:
	ofPoint A;
	ofPoint B;
	ofPoint C;
	ofPoint D;
	//qbFile file;

	ofxCvColorImage image;
	ofxCvColorImage image2;
	ofxCsv csv;
	ofxCsv csvRecorder;

	int cornerIndex = 1;
	bool SaveWarpPoints = false;

	ofVideoGrabber vidGrabber;
	ofImage imageVideo;
	int camWidth;
	int camHeight;

	ofTrueTypeFont font;

	//--------------------------------------------------------------
	void setup() {
		camWidth = 640;  // try to grab at this size.
		camHeight = 480;

		//file.setup();
		if (csv.load("morse.csv")) {
			A = ofPoint(ofToFloat(csv[0][1]), ofToFloat(csv[0][2]), ofToFloat(csv[0][3]));
			B = ofPoint(ofToFloat(csv[1][1]), ofToFloat(csv[1][2]), ofToFloat(csv[1][3]));
			C = ofPoint(ofToFloat(csv[2][1]), ofToFloat(csv[2][2]), ofToFloat(csv[2][3]));
			D = ofPoint(ofToFloat(csv[3][1]), ofToFloat(csv[3][2]), ofToFloat(csv[3][3]));
		}

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

		// 分配空间 ，需要free 记住
		image2.allocate(600,600);
		// 分配空间 ，需要free
		imageVideo.allocate(640, 480, OF_IMAGE_COLOR);
	}


	//--------------------------------------------------------------
	void update() {
		ofBackground(100, 100, 100);
		vidGrabber.update();
		
		if (vidGrabber.isFrameNew()) {  
			imageVideo.setFromPixels(vidGrabber.getPixels());

		}
		// 保存鼠标选取ABCD四个点位置。按S键，将ABCD的鼠标位置保存到文件。
		if (SaveWarpPoints == true) {
			// 保存到文件
			cout << "SaveWarpPoints" << "\n";

			csv[0].setInt(1, A.x);
			csv[0].setInt(2, A.y); 
			csv[0].setInt(3, A.z);

			csv[1].setInt(1, B.x);
			csv[1].setInt(2, B.y);
			csv[1].setInt(3, B.z);

			csv[2].setInt(1, C.x);
			csv[2].setInt(2, C.y);
			csv[2].setInt(3, C.z);

			csv[3].setInt(1, D.x);
			csv[3].setInt(2, D.y);
			csv[3].setInt(3, D.z);
			
			csv.save("morse.csv");
			SaveWarpPoints = false;
		}

	}


	//--------------------------------------------------------------
	void draw() {
		ofSetHexColor(0xffffff);
		// 图像变形，代码执行顺序要注意，ABCD顶点要和image2匹配
		image2 = imageVideo;  // 这句代码也有问题
		//image2.setFromPixels(imageVideo.getPixels());

		ofPoint A_ = ofPoint(A.x - 642, A.y - 162, 0);
		ofPoint B_ = ofPoint(B.x - 642, B.y - 162, 0);
		ofPoint C_ = ofPoint(C.x - 642, C.y - 162, 0);
		ofPoint D_ = ofPoint(D.x - 642, D.y - 162, 0);
		image2.warpPerspective(A_, B_, C_, D_);
		image2.draw(20, 160,600,600);
		
		// 画摄像头图像
		vidGrabber.draw(642, 162);

		// 画四个点，选取位置
		ofSetColor(255, 0, 0);
		ofFill();
		ofDrawCircle(A, 5.0);
		ofDrawCircle(B, 5.0);
		ofDrawCircle(C, 5.0);
		ofDrawCircle(D, 5.0);

		// 做连线，选取围绕区域
		ofSetLineWidth(3.0);
		ofDrawLine(A, B);
		ofDrawLine(B, C);
		ofDrawLine(C, D);
		ofDrawLine(D, A);
	}


	//--------------------------------------------------------------
	void keyPressed(int key) {
		switch (key)
		{
		case '1':
			cornerIndex = 1;
			break;
		case '2':
			cornerIndex = 2;
			break;
		case '3':
			cornerIndex = 3;
			break;
		case '4':
			cornerIndex = 4;
			break;
		case 's':
			SaveWarpPoints = true;
			break;
		default:
			break;
		}
	}


	//--------------------------------------------------------------
	void mousePressed(int x, int y, int button) {
		switch (cornerIndex)
		{
		case 1:
			A = ofPoint(x, y, 0);
			break;
		case 2:
			B = ofPoint(x, y, 0);
			break;
		case 3:
			C = ofPoint(x, y, 0);
			break;
		case 4:
			D = ofPoint(x, y, 0);
			break;
		default:
			break;
		}
	}

};
