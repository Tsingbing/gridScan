#pragma once

#include "ofMain.h"

class qbGrid {
public:
	float gridWidth, gridHeight;
	float cellWidth, cellHeight;
	float quadWidth, quadHeight;
	float cellGap, quadGap;
	// 画 UxV 的网格
	int u;
	int v; 
	// 画 WxX 的细胞
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

	void setup() {
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
	}

	// 更新小方格的颜色，建立多维数组quadValue[i][j][k][l][r:g:b:h:s:v]
	void update() {

	}

	void draw(float px, float py) {
		// 画网格外框
		ofSetColor(0, 0, 255);
		ofNoFill();
		ofSetLineWidth(4);
		ofDrawRectangle(px, py, gridWidth, gridHeight);

		// 画细胞外框
		ofSetColor(255, 0, 0);
		ofNoFill();
		for (size_t i = 0; i < v; i++)
		{
			for (size_t j = 0; j < u; j++)
			{
				// 画细胞外框
				ofPushMatrix();        
					ofTranslate(j*cellWidth + (j + 1)*cellGap + px, i*cellHeight + (i + 1)*cellGap + py, 0);

					for (size_t k = 0; k < x; k++)
					{
						// 画小方块，有填充
						for (size_t l = 0; l < w; l++)
						{
							ofPushMatrix();  
								if (i == 5 && j == 5) {
									ofSetColor(0, 255, 0);
								} else {
									ofSetColor(255, 0, 0);
								}
						
								ofFill();
								ofTranslate(l*quadWidth + l*quadGap, k*quadHeight + k*quadGap, 0);
								ofDrawRectangle(0, 0, quadWidth, quadHeight);

								ofSetColor(0, 0, 0);
								ofNoFill();
								ofSetLineWidth(2);
								ofDrawRectangle(0, 0, quadWidth, quadHeight);
							ofPopMatrix();         // recall the pushed coordinate position
						}
					}

					ofSetColor(0, 0, 0);
					ofSetLineWidth(2);
					ofNoFill();
					ofDrawRectangle(0, 0, cellWidth, cellHeight);

				ofPopMatrix();         // recall the pushed coordinate position
			}
		}
	}
private:


};

