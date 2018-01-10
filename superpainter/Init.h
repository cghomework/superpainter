#pragma once
#ifndef INIT_H
#define INIT_H

extern double ww;		//���ڿ�
extern double wh;		//���ڸ�
extern int coverageMenu;
extern int lineWidthMenu;
extern int menu_id;

void init();
void getReady();
void myReashape(GLsizei, GLsizei);
void mydisplay();//����ʾ����
void myMouse(int button, int state, int x, int y);
void myPassiveMotion(int x, int y);
void myMotion(int x, int y);
void coverageMenuEvent(int id);
void lineWidthMenuEvent(int id);
void myMenu(int id);

#endif // !INIT_H
