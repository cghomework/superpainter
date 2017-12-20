#pragma once
#ifndef INIT_H
#define INIT_H

extern int ww;		//窗口宽
extern int wh;		//窗口高

void init();
void myReashape(GLsizei, GLsizei);
void mydisplay();//主显示函数
void myMouse(int button, int state, int x, int y);
void myPassiveMotion(int x, int y);
void myMotion(int x, int y);
void myMenu(int id);

#endif // !INIT_H
