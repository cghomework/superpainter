#pragma once
#ifndef INIT_H
#define INIT_H

extern int ww;		//���ڿ�
extern int wh;		//���ڸ�

void init();
void myReashape(GLsizei, GLsizei);
void mydisplay();//����ʾ����
void myMouse(int button, int state, int x, int y);
void myPassiveMotion(int x, int y);
void myMotion(int x, int y);
void myMenu(int id);

#endif // !INIT_H
