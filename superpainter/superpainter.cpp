// superpainter.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "my_head.h"


/*

#include "button.h"		//按钮类
#include "entry.h"		//图元类
#include "frame.h"		//界面框架
#include "movement.h"	//交互操作



//定义窗口大小改变的时候，内部元件的改变形式


*/
int main(int argc, char* argv[]) {
	//HWND hWnd = GetForegroundWindow();    //获取当前的前置窗口
	//ShowWindow(hWnd, SW_HIDE);        //隐藏了获取的窗口.

	glutInit(&argc, argv);

	glutInitWindowPosition(250, 100);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("superPainter");

	init();

	glutMainLoop();
}