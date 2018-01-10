#include "stdafx.h"
#include "my_head.h"

double ww = 1000;
double wh = 600;
int menu_id = -1;
int coverageMenu = -1;
int lineWidthMenu = -1;

int ready = 0;

void init() {
	//回调函数
	glutReshapeFunc(myReashape);
	glutDisplayFunc(mydisplay);
	glutMouseFunc(myMouse);
	glutPassiveMotionFunc(myPassiveMotion);
	glutMotionFunc(myMotion);

	//布局
	initFrame();

	//参数
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xFFFF);
	glEnable(GL_BLEND);     //启用混合状态  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_TEXTURE_2D);
	glRenderMode(GL_RENDER);
	//设置背景颜色
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void myReashape(GLsizei w, GLsizei h) {

	if (!ready) {
		getReady();
	}
	//HWND hWnd = GetForegroundWindow();    //获取当前的前置窗口
	//HANDLE hIcon = LoadImage(NULL, "icon.ico", IMAGE_ICON, NULL, NULL, LR_LOADFROMFILE);
	//SendMessage(hWnd, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIcon);

	//重置投影
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//重置视窗
	glViewport(0, 0, w, h);

	//更新全局变量窗口大小
	ww = w;
	wh = h;
	initFrame();
	glFlush();
}

//主显示函数
void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	graphList.showAll();
	glRectf(-0.1f, -0.1f, 0.5f, 0.5f);
	showFrame();
	showMoving();
	glFlush();
}


void getReady() {
	graphList.newOne(0, 0, 0, 0);
	graphList.ptail->setType(3);
	graphList.ptail->addPoint(0, 0);
	graphList.ptail->addPoint(0, 100);
	graphList.ptail->addPoint(100, 100);
	graphList.ptail->addPoint(100, 0);
	glutPostRedisplay();
	now_op = picking;
	checkPressEntry(50, 50);
	graphList.remove(0);
	now_op = sys;
	ready = 1;
}

void myMouse(int button, int state, int x, int y) {
	my_Mouse(button, state, (double)x, (double)y);
}

void myPassiveMotion(int x, int y) {
	my_PassiveMotion((double)x, (double)y);
}

void myMotion(int x, int y) {
	my_Motion((double)x, (double)(y));
}

void coverageMenuEvent(int id) {
	if (graphList.size <= 1) return;
	Graphic * temp = graphList.phead;
	while (temp->next != NULL) {
		if (temp->next->picked == 1) {
			switch (id) {
			case 1: {
				Graphic * temp2 = temp->next;
				if (temp2 == graphList.ptail) return;
				temp->next = temp2->next;
				temp2->next = temp->next->next;
				temp->next->next = temp2;
				if (temp->next == graphList.ptail) graphList.ptail = graphList.ptail->next;
				break;
			}
			case 2: {
				if (temp == graphList.phead) return;
				Graphic * temp1 = graphList.phead;
				while (temp1->next != temp) {
					temp1 = temp1->next;
				}
				Graphic * temp2 = temp->next;
				Graphic * temp3 = temp2->next;

				temp1->next = temp2;
				temp2->next = temp;
				temp->next = temp3;
				if (temp2 == graphList.ptail) graphList.ptail = graphList.ptail->next;
				break;
			}
			case 3: {
				Graphic * temp2 = temp->next;
				if (temp2 == graphList.ptail) return;
				temp->next = temp2->next;
				temp2->next = NULL;
				graphList.ptail->next = temp2;
				graphList.ptail = graphList.ptail->next;
				break;
			}
			case 4: {
				if (temp == graphList.phead) return;
				Graphic * temp3 = temp->next;
				temp->next = temp3->next;
				temp3->next = graphList.phead->next;
				graphList.phead->next = temp3;
				if (temp3 == graphList.ptail) graphList.ptail = graphList.ptail->next;
				break;
			}
			default:break;
			}
			glutPostRedisplay();
			break;
		}
		temp = temp->next;
	}
}

void lineWidthMenuEvent(int id) {
	if (graphList.size <= 0) return;
	Graphic * temp = graphList.phead;
	while (temp->next != NULL) {
		if (temp->next->picked == 1) {
			switch (id) {
			case 5: {
				temp->next->width = 2;
				break;
			}
			case 6: {
				temp->next->width = 4;
				break;
			}
			case 7: {
				temp->next->width = 6;
				break;
			}
			case 8: {
				temp->next->width = 8;
				break;
			}
			default:break;
			}
			glutPostRedisplay();
			break;
		}
		temp = temp->next;
	}
}

void myMenu(int id) {
	if (id == 0 && graphList.size > 0) {
		Graphic * temp = graphList.phead;
		while (temp->next != NULL) {
			if (temp->next->picked == 1) {
				graphList.newOne(temp->next);
				break;
			}
			temp = temp->next;
		}
	}
}