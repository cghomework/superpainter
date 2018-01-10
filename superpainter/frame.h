/*
#define toolNo  5
#define specialNo 3
#define sysNo 4
button leftTop,leftBottom,rightTop,rightMiddle,rightBottom;
button toolList[toolNo];
button specialList[specialNo];
button sysList[sysNo];
button line,curve,polygon,square,circle;

button colorFrame,colorSecond,colorCurrent,word;
*/

#ifndef FRAME_H
#define FRAME_H



#define MAINBLOCK 		5		// 主框架数目
#define LEFTTOP 		4		// 左上组按钮数
#define LEFTBOTTOM 		9		// 左下组按钮数
#define RIGHTTOP 		4		// 右上组按钮数
#define RIGHTMIDDLE 	12		// 右中组按钮数
#define RIGHTBOTTOM 	2		// 右下组按钮数
#define SLIP			4		// 滑动按钮组件
#define BUTTON_COUNT	LEFTTOP + LEFTBOTTOM + RIGHTTOP + RIGHTMIDDLE +RIGHTBOTTOM + SLIP
extern Button mainBlock[MAINBLOCK];
extern Button leftTop[LEFTTOP];
extern Button leftBottom[LEFTBOTTOM];
extern Button rightTop[RIGHTTOP];
extern Button rightMiddle[RIGHTMIDDLE];
extern Button rightBottom[RIGHTBOTTOM];
extern Button slip[SLIP];
extern Button * button_list[BUTTON_COUNT];

//板块背景颜色
extern double blockColor[4];
extern double blockColor2[4];

void initFrame();

void showColorBlock();

void showColorBlock2();

void showFrame();


#endif // !FRAME_H
