#include "stdafx.h"
#include "my_head.h"


Button mainBlock[MAINBLOCK];
Button leftTop[LEFTTOP];
Button leftBottom[LEFTBOTTOM];
Button rightTop[RIGHTTOP];
Button rightMiddle[RIGHTMIDDLE];
Button rightBottom[RIGHTBOTTOM];
Button slip[SLIP];
Button * button_list[BUTTON_COUNT];



double blockColor[4] = { 0.8, 0.8, 0.8, 1};
double blockColor2[4] = { 1, 1, 1, 0};


void initFrame() {


	int margin = 4;					// 板块内部距离和边界
	int border = 15;				// 整体边距
	int leftButtonw = 30;			// 左边按钮宽
	int leftButtonh = 30;			// 左边按钮高
	int rightButtonw = 130;			// 右边一般按钮宽
	int rightButtonh = 20;			// 右边一般按钮高
	int leftBottomy = wh - 510;		// 左边整体高度定位
	int rightBottomy = wh - 470;	// 右边整体高度定位

	/*
	框架
	*/

	//mainBlock[0].setSize(margin * 3 + leftButtonw * 2, margin * 3 + leftButtonh *2); // 左边按钮宽*2 + 组内边界*3；左边按钮高*2 + 组内边界*3；
	//mainBlock[0].setPosition(border,leftBottomy + leftButtonh*5 + 6 * margin + margin); // 整体边距；5行按钮，6个模块内边界，1个模块边界

	//mainBlock[1].setSize(margin * 3 + leftButtonw * 2, margin * 6 + leftButtonh *5); // 左边按钮宽*2 + 组内边界*3； 左边按钮高*5 + 组内边界 *6；
	//mainBlock[1].setPosition(border,leftBottomy); // 整体边距；左边定位
	
	mainBlock[2].setSize(margin * 2 + rightButtonw, margin * 5 + rightButtonw + rightButtonh * 3);
	mainBlock[2].setPosition(ww - border - margin * 2 - rightButtonw, rightBottomy + margin + margin + margin * 2 + rightButtonh + margin * 7 + rightButtonh * 6);

	mainBlock[3].setSize(margin * 2 + rightButtonw, margin * 7 + rightButtonh * 6);
	mainBlock[3].setPosition(ww - border - margin * 2 - rightButtonw, rightBottomy + margin + margin * 2 + rightButtonh);

	mainBlock[4].setSize(margin * 2 + rightButtonw, margin * 2 + rightButtonh);
	mainBlock[4].setPosition(ww - border - margin * 2 - rightButtonw, rightBottomy);

	for (int i = 2; i < 5; i++) {
		mainBlock[i].setColorInside(blockColor[0], blockColor[1], blockColor[2], blockColor[3]);
		mainBlock[i].setBorder(0);
	}


	/*
	按钮
	*/
	int button_list_index = 0;

	//左上组按钮
	for (int i = 0; i < LEFTTOP; i++) {
		leftTop[i].setSize(leftButtonw, leftButtonh);
		leftTop[i].setPosition(border, leftBottomy + LEFTBOTTOM * (margin + leftButtonh) + (LEFTTOP - 1 - i) * (margin + leftButtonh) + margin * 4);
		leftTop[i].setTex(1);
		leftTop[i].setBorder(0);
		button_list[button_list_index] = &leftTop[i];
		button_list_index++;
	}
	leftTop[0].setTexImage("img\\open.bmp");
	leftTop[1].setTexImage("img\\create.bmp");
	leftTop[2].setTexImage("img\\save.bmp");
	leftTop[3].setTexImage("img\\saveas.bmp");

	leftTop[0].setName("open");
	leftTop[1].setName("create");
	leftTop[2].setName("save");
	leftTop[3].setName("saveas");

	//左下组按钮
	for (int i = 0; i < LEFTBOTTOM; i++) {
		leftBottom[i].setSize(leftButtonw, leftButtonh);
		leftBottom[i].setPosition(border, leftBottomy + (LEFTBOTTOM - 1 - i) * (margin + leftButtonh));
		leftBottom[i].setTex(1);
		leftBottom[i].setBorder(0);
		button_list[button_list_index] = &leftBottom[i];
		button_list_index++;
	}
	leftBottom[0].setTexImage("img\\line.bmp");
	leftBottom[1].setTexImage("img\\curve.bmp");
	leftBottom[2].setTexImage("img\\polygon.bmp");
	leftBottom[3].setTexImage("img\\square.bmp");
	leftBottom[4].setTexImage("img\\circle.bmp");
	leftBottom[5].setTexImage("img\\cirsquare.bmp");
	leftBottom[6].setTexImage("img\\delete.bmp");
	leftBottom[7].setTexImage("img\\arrow1.bmp");
	leftBottom[8].setTexImage("img\\arrow2.bmp");

	leftBottom[0].setName("line");
	leftBottom[1].setName("curve");
	leftBottom[2].setName("polygon");
	leftBottom[3].setName("square");
	leftBottom[4].setName("circle");
	leftBottom[5].setName("cirsquare");
	leftBottom[6].setName("delete");
	leftBottom[7].setName("arrow1");
	leftBottom[8].setName("arrow2");

	//右上角组件
	for (int i = 0; i < RIGHTTOP; i++) {
		rightTop[i].setSize(rightButtonw, rightButtonh);
		rightTop[i].setPosition(ww - border - margin * 2 - rightButtonw + margin,
			rightBottomy + margin + margin + margin * 2 + rightButtonh + margin * 7 + rightButtonh * 6 + ((RIGHTTOP - 1 - i) + 1) * margin + ((RIGHTTOP - 1 - i)) * rightButtonh);
		rightTop[i].setColorInside(blockColor2[0], blockColor2[1], blockColor2[2], blockColor2[3]);
		rightTop[i].setBorder(0);
		button_list[button_list_index] = &rightTop[i];
		button_list_index++;
	}
	rightTop[0].setColorInside(blockColor2[0], blockColor2[1], blockColor2[2], 1);
	rightTop[0].setSize(rightButtonw, rightButtonw);
	rightTop[1].setColorInside(blockColor2[0], blockColor2[1], blockColor2[2], 1);
	rightTop[2].setText("current color:");
	rightTop[3].setColorInside(blockColor2[0], blockColor2[1], blockColor2[2], 1);

	//右中组件
	for (int i = 0; i < RIGHTMIDDLE; i++) {
		rightMiddle[i].setSize((rightButtonw - margin) / 2, rightButtonh);
		rightMiddle[i].setPosition(ww - border - margin * 2 - rightButtonw + margin * (i % 2 + 1) + (rightButtonw - margin) / 2 * (i % 2),
			rightBottomy + margin + margin * 2 + rightButtonh + ((RIGHTMIDDLE - 1 - i) / 2 + 1) * margin + ((RIGHTMIDDLE - 1 - i) / 2) * rightButtonh);
		rightMiddle[i].setColorInside(blockColor2[0], blockColor2[1], blockColor2[2], blockColor2[3]);
		rightMiddle[i].setBorder(0);
		button_list[button_list_index] = &rightMiddle[i];
		button_list_index++;
	}
	rightMiddle[0].setText("filled:");
	rightMiddle[2].setText("border:");
	rightMiddle[4].setText("texure:");
	rightMiddle[6].setText("trans:");

	rightMiddle[1].setColorInside(1, 1, 1, 1);
	rightMiddle[1].setColorBorder(0.2, 0.2, 0.2, 1);
	rightMiddle[1].setBorder(1);
	rightMiddle[3].setColorInside(0, 0, 0, 1);
	rightMiddle[3].setColorBorder(0.2, 0.2, 0.2, 1);
	rightMiddle[7].setSize((rightButtonw - margin) / 2, 6);
	rightMiddle[7].setPosition(ww - border - margin * 2 - rightButtonw + margin * 2 + (rightButtonw - margin) / 2,
		rightBottomy + margin + margin * 2 + rightButtonh + ((RIGHTMIDDLE - 8) / 2 + 1) * margin + ((RIGHTMIDDLE - 8) / 2) * rightButtonh + rightButtonh / 2 - 3);
	rightMiddle[7].setColorInside(0.6, 0.6, 0.6, 1);

	//右下组件
	button_list[button_list_index] = &rightBottom[0];
	button_list_index++;
	button_list[button_list_index] = &rightBottom[1];
	button_list_index++;

	rightBottom[0].setSize((rightButtonw - margin) / 2, rightButtonh);
	rightBottom[0].setPosition(ww - border - margin * 2 - rightButtonw + margin,
		rightBottomy + ((RIGHTBOTTOM - 2) / 2 + 1) * margin + ((RIGHTBOTTOM - 2) / 2) * rightButtonh);
	rightBottom[0].setColorInside(blockColor2[0], blockColor2[1], blockColor2[2], blockColor2[3]);
	rightBottom[0].setText("scale:");
	rightBottom[0].setBorder(0);

	rightBottom[1].setSize((rightButtonw - margin) / 2, 6);
	rightBottom[1].setPosition(ww - border - margin * 2 - rightButtonw + margin * 2 + (rightButtonw - margin) / 2,
		rightBottomy + ((RIGHTBOTTOM - 2) / 2 + 1) * margin + ((RIGHTBOTTOM - 2) / 2) * rightButtonh + rightButtonh / 2 - 3);
	rightBottom[1].setColorInside(0.6, 0.6, 0.6, 1);
	rightBottom[1].setBorder(0);


	//滑动按钮
	slip[0].setSize(7, 7);
	slip[0].setPosition(rightTop[0].x - 3, rightTop[0].y - 3);
	slip[0].setName("slip1"); 
	slip[1].setSize(5, rightButtonh);
	slip[1].setPosition(rightTop[1].x + rightTop[1].w / 2 - 2, rightTop[1].y);
	slip[1].setName("slip2");
	slip[2].setSize(5, rightButtonh);
	slip[2].setPosition(rightMiddle[7].x - 2, rightMiddle[7].y - rightButtonh / 2 + 2);
	slip[2].setName("slip3");
	slip[3].setSize(5, rightButtonh);
	slip[3].setPosition(rightBottom[1].x + rightButtonw / 4 - 2, rightBottom[1].y - rightButtonh / 2 + 2);
	slip[3].setName("slip4");
	for (int i = 0; i<SLIP; i++) {
		slip[i].setColorInside(1, 1, 1, 1);
		slip[i].setBorder(1);
		slip[i].setColorBorder(0, 0, 0, 1);
		button_list[button_list_index] = &slip[i];
		button_list_index++;
	}
}

void showColorBlock() {
	glBegin(GL_POLYGON);
	glColor4d(0, 0, 0, 1);
	glVertex2d(rightTop[0].x, rightTop[0].y + rightTop[0].h / 2);
	glVertex2d(rightTop[0].x, rightTop[0].y + rightTop[0].h);
	glVertex2d(rightTop[0].x + rightTop[0].w, rightTop[0].y + rightTop[0].h);
	glVertex2d(rightTop[0].x + rightTop[0].w, rightTop[0].y + rightTop[0].h / 2);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor4d(1, 0, 0, 0);
	glVertex2d(rightTop[0].x, rightTop[0].y);
	glColor4d(1, 0, 0, 1);
	glVertex2d(rightTop[0].x, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(1, 1, 0, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6, rightTop[0].y);
	glColor4d(1, 1, 0, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(0, 1, 0, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3, rightTop[0].y);
	glColor4d(0, 1, 0, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(0, 1, 1, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 2, rightTop[0].y);
	glColor4d(0, 1, 1, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 2, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(0, 0, 1, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3 * 2, rightTop[0].y);
	glColor4d(0, 0, 1, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3 * 2, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(1, 0, 1, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6 * 5, rightTop[0].y);
	glColor4d(1, 0, 1, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6 * 5, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(1, 0, 0, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w, rightTop[0].y);
	glColor4d(1, 0, 0, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w, rightTop[0].y + rightTop[0].h / 2);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glColor4d(1, 0, 0, 1);
	glVertex2d(rightTop[0].x, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(1, 0, 0, 0);
	glVertex2d(rightTop[0].x, rightTop[0].y + rightTop[0].h / 2 + rightTop[0].h / 2);

	glColor4d(1, 1, 0, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(1, 1, 0, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6, rightTop[0].y + rightTop[0].h / 2 + rightTop[0].h / 2);

	glColor4d(0, 1, 0, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(0, 1, 0, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3, rightTop[0].y + rightTop[0].h / 2 + rightTop[0].h / 2);

	glColor4d(0, 1, 1, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 2, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(0, 1, 1, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 2, rightTop[0].y + rightTop[0].h / 2 + rightTop[0].h / 2);

	glColor4d(0, 0, 1, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3 * 2, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(0, 0, 1, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3 * 2, rightTop[0].y + rightTop[0].h / 2 + rightTop[0].h / 2);

	glColor4d(1, 0, 1, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6 * 5, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(1, 0, 1, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6 * 5, rightTop[0].y + rightTop[0].h / 2 + rightTop[0].h / 2);

	glColor4d(1, 0, 0, 1);
	glVertex2d(rightTop[0].x + rightTop[0].w, rightTop[0].y + rightTop[0].h / 2);
	glColor4d(1, 0, 0, 0);
	glVertex2d(rightTop[0].x + rightTop[0].w, rightTop[0].y + rightTop[0].h / 2 + rightTop[0].h / 2);
	glEnd();
}

void showColorBlock2() {
	glBegin(GL_QUAD_STRIP);
	glColor4d(1, 1, 1, 1);
	glVertex2d(rightTop[1].x, rightTop[1].y);
	glColor4d(1, 1, 1, 1);
	glVertex2d(rightTop[1].x, rightTop[1].y + rightTop[1].h);
	glColor4dv(rightTop[1].colorInside);
	glVertex2d(rightTop[1].x + rightTop[1].w / 2, rightTop[1].y);
	glColor4dv(rightTop[1].colorInside);
	glVertex2d(rightTop[1].x + rightTop[1].w / 2, rightTop[1].y + rightTop[1].h);
	glColor4d(0, 0, 0, 1);
	glVertex2d(rightTop[1].x + rightTop[1].w, rightTop[1].y);
	glColor4d(0, 0, 0, 1);
	glVertex2d(rightTop[1].x + rightTop[1].w, rightTop[1].y + rightTop[1].h);
	glEnd();
}

void showFrame() {
	//	showChoosed();
	for (int i = 2; i< 5; i++) mainBlock[i].show();

	for (int i = 0; i < LEFTTOP; i++) leftTop[i].show();
	for (int i = 0; i < LEFTBOTTOM; i++) leftBottom[i].show();
	for (int i = 0; i < RIGHTTOP; i++) rightTop[i].show();
	for (int i = 0; i < RIGHTMIDDLE; i++) rightMiddle[i].show();
	for (int i = 0; i < RIGHTBOTTOM; i++) rightBottom[i].show();
	showColorBlock();
	showColorBlock2();
	for (int i = 0; i < SLIP; i++) slip[i].show();
}