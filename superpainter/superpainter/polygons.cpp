#include "stdafx.h"
#include "my_head.h"

polygons graphList;

polygons::polygons() :size(0) {
	phead = new Graphic;
	ptail = phead;
}
void polygons::newOne(double _x, double _y, double _w, double _h) {
	Graphic * temp = new Graphic(_x, _y, _w, _h);
	ptail->next = temp;
	ptail = temp;
	size++;
	ptail->insideNameId = size * 2;
	ptail->borderNameId = size * 2 + 1;
}
int polygons::remove(int i) {
	if (size == 0 || size <= i) return 0;
	Graphic * temp = phead;
	int j = 0;
	while (temp != NULL) {
		if (j == i) {
			Graphic * temp2 = temp->next;
			if (ptail == temp2) ptail = temp;
			temp->next = temp->next->next;
			delete temp2;
			size--;
		}
		if (j >= i && temp->next != NULL) {
			temp->next->insideNameId = (j + 1) * 2;
			temp->next->borderNameId = (j + 1) * 2 + 1;
		}
		j++;
		temp = temp->next;
	}
}
void polygons::showAll() {
	Graphic * temp = phead;
	while (temp->next != NULL) {
		temp->next->show();
		temp = temp->next;
	}
}
void polygons::clearAll() {
	while (size>0) remove(0);
}