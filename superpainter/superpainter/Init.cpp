#include "stdafx.h"
#include "my_head.h"

int ww = 1000;
int wh = 600;

void init() {
	//回调函数
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myReashape);
	glutMouseFunc(myMouse);
	glutPassiveMotionFunc(myPassiveMotion);
	glutMotionFunc(myMotion);


	//弹出菜单
	glutCreateMenu(myMenu);
	glutAddMenuEntry("up", 1);
	glutAddMenuEntry("down", 2);
	glutAddMenuEntry("top", 3);
	glutAddMenuEntry("bottom", 4);
	//glutAttachMenu(GLUT_MIDDLE_BUTTON);

	//布局
	initFrame();

	//参数
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_STIPPLE);
	glEnable(GL_BLEND);     //启用混合状态  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	//设置背景颜色
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void myReashape(GLsizei w, GLsizei h) {

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
	//initFrame();
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


void myMouse(int button, int state, int x, int y) {
	my_Mouse(button, state, (double)x, (double)y);
}

void myPassiveMotion(int x, int y) {
	my_PassiveMotion((double)x, (double)y);
}

void myMotion(int x, int y) {
	my_Motion((double)x, (double)(y));
}

void myMenu(int id) {
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
