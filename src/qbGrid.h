#pragma once

#include "ofMain.h"
#include "qbVideoCapture.h"
class qbGrid {
public:
	float gridWidth, gridHeight;
	float cellWidth, cellHeight;
	float quadWidth, quadHeight;
	float cellGap, quadGap;

	qbVideoCapture videoCapture;
	unsigned char quadValue[100][100][10][10][6]; // Hue, Sat, Bri, Red, Green, Blue of each quadrant

	// �� UxV ������
	int u;
	int v; 
	// �� WxX ��ϸ��
	int w;
	int x; 

	qbGrid()
		: u(18)
		, v(18)
		, w(2)
		, x(2)
		, gridWidth(596)
		, gridHeight(596)
	{}

	virtual ~qbGrid() {}


	//--------------------------------------------------------------
	void setup(qbVideoCapture videoCapture_) {
		cellGap = 9.0 / 596.0 * gridWidth;
		cellWidth = (gridWidth - (u + 1) * cellGap) / u;

		cellHeight = (gridHeight - (v + 1) * cellGap) / v;


		quadGap = cellWidth / (2 * w - 1);
		quadWidth = (cellWidth - (w - 1) * quadGap) / w;
		quadHeight = (cellHeight - (x - 1) * quadGap) / x;

		cout << cellHeight << "\n";
		cout << cellWidth << "\n";
		cout << quadWidth << "\n";
		cout << quadHeight << "\n";

		videoCapture = videoCapture_;
	}


	//--------------------------------------------------------------
	void update() {
		// ����С�������ɫ��������ά����quadValue[i][j][k][l][r:g:b:h:s:v]
	}


	//--------------------------------------------------------------
	void draw(float px, float py) {
		// ���������
		ofSetColor(0, 0, 255);
		ofNoFill();
		ofSetLineWidth(4);
		ofDrawRectangle(px, py, gridWidth, gridHeight);
		
		// ��ϸ�����
		ofSetColor(255, 0, 0);
		ofNoFill();
		for (size_t i = 0; i < u; i++)
		{
			for (size_t j = 0; j < v; j++)
			{
				// ��ϸ�����
				ofPushMatrix();        
					ofTranslate(j*cellWidth + (j + 1)*cellGap + px, i*cellHeight + (i + 1)*cellGap + py, 0);
					
					for (size_t k = 0; k < w; k++)
					{
						// ��С���飬�����
						for (size_t l = 0; l < x; l++)
						{
							// ==============�ɼ�������ɫֵ,�������������ɫ
							for (size_t m = 0; m < quadWidth; m++)
							{
								for (size_t n = 0; n < quadHeight; n++)
								{
									float local =       //Skips to column column in Row
										m + //Skips pixels within quad
										k * (quadGap + quadWidth) + //Skips quads
										i * (cellGap + cellWidth) + //Skips cells
										(cellGap)+ //Skips left margin

												   //Skips to row
										n * gridWidth + //Skips pixels within quad
										l * gridWidth * (quadGap + quadHeight) +  //Skips quads
										j * gridWidth * (cellGap + cellHeight) + //Skips cells
										gridWidth * (cellGap); //Skips Top Margin;

									/*quadValue[i][j][k][l][0] += videoCapture.image.getPixels().getColor(local_x, local_y).getHue();
									quadValue[i][j][k][l][1] += videoCapture.image.getPixels().getColor(local_x, local_y).getSaturation();
									quadValue[i][j][k][l][2] += videoCapture.image.getPixels().getColor(local_x, local_y).getBrightness();*/
									quadValue[i][j][k][l][0] += videoCapture.image.getPixels().getColor(local).r;
									quadValue[i][j][k][l][1] += videoCapture.image.getPixels().getColor(local).g;
									quadValue[i][j][k][l][2] += videoCapture.image.getPixels().getColor(local).b;
								}
							}// ================�ɼ�������ɫֵ����

							ofPushMatrix();  
								if (i == 5 && j == 5) {
									//ofSetColor(quadValue[i][j][k][l][0], quadValue[i][j][k][l][1], quadValue[i][j][k][l][2]);
									ofSetColor(0, 255, 0);
								} else {
									ofSetColor(255, 0, 0);
								}
								
								ofFill();
								ofTranslate(l*quadWidth + l*quadGap, k*quadHeight + k*quadGap, 0);
								ofDrawRectangle(0, 0, quadWidth, quadHeight);

								/*ofSetColor(0, 0, 0);
								ofNoFill();
								ofSetLineWidth(1);
								ofDrawRectangle(0, 0, quadWidth, quadHeight);*/
							ofPopMatrix();         // recall the pushed coordinate position
						}
					}

					//ofSetColor(0, 0, 0);
					//ofSetLineWidth(1);  //�Ժ��滭�����εĿ����Ӱ�죬���Խ���ʱ����������Ϊ1��Ҳ���У���bug
					//ofNoFill();
					//ofDrawRectangle(0, 0, cellWidth, cellHeight);

				ofPopMatrix();         // recall the pushed coordinate position
			}
		}

	}
	
private:

};

