#include "stdafx.h"
#include "my_head.h"

Button::Button(double _x, double _y, double _w, double _h) :Entry(_x, _y, _w, _h) {
	button_name = NULL;
	addPoint(_x, _y);
	addPoint(_x+_w, _y);
	addPoint(_x+_w, _y+_h);
	addPoint(_x, _y+_h);
}

void Button::show() {
	double save_xtrans = xtrans;
	double save_ytrans = ytrans;
	double save_standard = standard;
	xtrans = ytrans = 0;
	standard = 1;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	if (nvertices == 1 && _type != CIRCLE) showPoint();
	else if (border) {
		switch (_type) {
		case LINE:		showLine(0); break;
		case CURVE:		showCurve(0); break;
		case POLYGON:	showLine(0); break;
		case CIRCLE:	showCurve(0); break;
		default:		break;
		}
	}
	if (tex) {
		showTex();
	}
	else if (solid) {
		switch (_type) {
		case LINE:		break;
		case CURVE:		break;
		case POLYGON:	showLine(1); break;
		case CIRCLE:	showCurve(1); break;
		default:		break;
		}
	}
	if (_text != NULL) showText();
	if (picked) showPick();
	if (blick) showPoints();
	glPopMatrix();
	glPopAttrib();
	xtrans = save_xtrans;
	ytrans = save_ytrans;
	standard = save_standard;
}


void Button::setPosition(double _x, double _y) {
	double dx = _x - x;
	double dy = _y - y;
	vertice_node * temp = vhead->next;
	while (temp != NULL) {
		temp->x += dx;
		temp->y += dy;
		temp = temp->next;
	}
	x = _x;
	y = _y;
	refreshmaxmin();
}
void Button::setSize(double _w, double _h) {
	double dw = (_w - w) / w;
	double dh = (_h - h) / h;
	vertice_node * temp = vhead->next;
	while (temp != NULL) {
		temp->x += (temp->x - xmin) * dw;
		temp->y += (temp->y - ymin) * dh;
		temp = temp->next;
	}
	w = _w;
	h = _h;
	refreshmaxmin();
}
void Button::mouseHover() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	/*
	setColor(colorHoverInside);
	glBegin(GL_POLYGON);
	glVertex2f(x,y);
	glVertex2f(x+w,y);
	glVertex2f(x+w,y+h);
	glVertex2f(x,y+h);
	glEnd();
	*/
	setColor(colorHoverBorder);
	glBegin(GL_LINE_STRIP & GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmin + w, ymin);
	glVertex2f(xmin + w, ymin + h);
	glVertex2f(xmin, ymin + h);
	glEnd();
	glFlush();
	glPopMatrix();
	glPopAttrib();
}
void Button::mouseUnhover() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	setColor(colorInside);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
	setColor(colorBorder);
	glBegin(GL_LINE_STRIP & GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
	//		glFlush();
	glPopMatrix();
	glPopAttrib();
}
void Button::setName(char * _name) {
	button_name = new char[strlen(_name)];
	strcpy(button_name, _name);
}