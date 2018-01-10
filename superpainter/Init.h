#pragma once
#ifndef INIT_H
#define INIT_H

extern double ww;		//窗口宽
extern double wh;		//窗口高
extern int coverageMenu;
extern int lineWidthMenu;
extern int menu_id;

void init();
void getReady();
void myReashape(GLsizei, GLsizei);
void mydisplay();//主显示函数
void myMouse(int button, int state, int x, int y);
void myPassiveMotion(int x, int y);
void myMotion(int x, int y);
void coverageMenuEvent(int id);
void lineWidthMenuEvent(int id);
void myMenu(int id);

#endif // !INIT_H
