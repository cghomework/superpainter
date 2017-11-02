#include <windows.h>
#include <commdlg.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL\glut.h>
#include <math.h>

int ww = 1000;		//窗口宽
int wh = 600;		//窗口高

#include "button.h"		//按钮类
#include "entry.h"		//图元类
#include "frame.h"		//界面框架
#include "movement.h"	//交互操作


//定义窗口大小改变的时候，内部元件的改变形式
void myReashape(GLsizei w, GLsizei h){
	//重置投影
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//重置视窗
	glViewport(0,0,w,h);

	//更新全局变量窗口大小
	ww = w;
	wh = h;
	initFrame();
	glFlush();
}

//主显示函数
void mydisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	entryList.showAll();
	
	showFrame();
	showMoving();
	
	glFlush();
}

int main(int argc, char* argv[]){

	HWND hWnd= GetForegroundWindow();    //获取当前的前置窗口
	ShowWindow(hWnd, SW_HIDE);        //隐藏了获取的窗口.

	glutInit(&argc, argv);
	glutInitWindowPosition(250,100);
	glutInitWindowSize(ww,wh);
	glutCreateWindow("superPainter");
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //指定混合函数  

	glutReshapeFunc(myReashape);
	glutMouseFunc(myMouse);
	glutPassiveMotionFunc(myPassiveMotion);
	glutMotionFunc(myMotion);
	

	initFrame();
	glutDisplayFunc(mydisplay);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LINE_STIPPLE);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);     //启用混合状态  
	glEnable(GL_TEXTURE_2D);
	glClearColor(1.0,1.0,1.0,1.0);
	glutMainLoop();
	if(opened_file!=NULL) delete opened_file;
}