#include "stdafx.h"
#include "my_head.h"

void Graphic::_spin(double x, double y, double theta, double &_x, double &_y) {
	x -= xmin + w / 2;
	y -= ymin + h / 2;
	_x = x * cos(theta) - y * sin(theta) + xmin + w / 2;
	_y = x * sin(theta) + y * cos(theta) + ymin + h / 2;
}

Graphic::Graphic(double _x, double _y, double _w, double _h) :Entry(_x, _y, _w, _h), next(NULL) {}

//Ðý×ª
void Graphic::spin(double theta) {
	vertice_node * temp = vhead->next;
	double _x, _y;
	while (temp != NULL) {
		_x = temp->x;
		_y = temp->y;
		_spin(_x, _y, theta, _x, _y);
		temp->x = _x;
		temp->y = _y;
		_x = temp->left->x;
		_y = temp->left->y;
		_spin(_x, _y, theta, _x, _y);
		temp->left->x = _x;
		temp->left->y = _y;
		_x = temp->right->x;
		_y = temp->right->y;
		_spin(_x, _y, theta, _x, _y);
		temp->right->x = _x;
		temp->right->y = _y;

		temp = temp->next;
	}
	refreshmaxmin();
}
void Graphic::movePoint(double _x, double _y, double newx, double newy) {
	double dx = newx - _x;
	double dy = newy - _y;
	vertice_node * temp = vhead->next;
	int c = 0;
	while (temp != NULL) {
		if (temp->x < _x + 5 && temp->x > _x - 5 && temp->y < _y + 5 && temp->y > _y - 5) break;
		if (temp->left->x < _x + 5 && temp->left->x > _x - 5 && temp->left->y < _y + 5 && temp->left->y > _y - 5) {
			c = 1;
			temp = temp->left;
			break;
		}
		if (temp->right->x < _x + 5 && temp->right->x > _x - 5 && temp->right->y < _y + 5 && temp->right->y > _y - 5) {
			c = 1;
			temp = temp->right;
			break;
		}
		temp = temp->next;
	}
	if (temp == NULL) return;
	temp->x += dx;
	temp->y += dy;
	if (c != 1) {
		temp->left->x += dx;
		temp->left->y += dy;
		temp->right->x += dx;
		temp->right->y += dy;
	}
	refreshmaxmin();
}
void Graphic::changePoints(double _x, double _y, double newx, double newy) {

	double dx = newx - _x;
	double dy = newy - _y;
	double ratex = 1;
	double ratey = 1;
	int side = 0;
	double basex = xmax;
	double basey = ymax;
	if (xmax - 2 < _x && _x < xmax + 4) {
		ratex = (w + dx) / w;
		basex = xmin;
	}
	else if (xmin - 4 < _x && _x < xmin + 2) {
		ratex = (w - dx) / w;
		basex = xmax;
	}
	if (ymax - 2 < _y && _y < ymax + 4) {
		ratey = (h + dy) / h;
		basey = ymin;
	}
	else if (ymin - 4 < _y  && _y < ymin + 2) {
		ratey = (h - dy) / h;
		basey = ymax;
	}
	if (ratex == 0) ratex = 1;
	if (ratey == 0) ratey = 1;

	vertice_node * temp = vhead->next;
	while (temp != NULL) {
		temp->left->x = ratex * (temp->left->x - basex) + basex;
		temp->left->y = ratey * (temp->left->y - basey) + basey;
		temp->right->x = ratex * (temp->right->x - basex) + basex;
		temp->right->y = ratey * (temp->right->y - basey) + basey;
		temp->x = ratex * (temp->x - basex) + basex;
		temp->y = ratey * (temp->y - basey) + basey;
		temp = temp->next;
	}
	refreshmaxmin();
}
void Graphic::movePoints(double _x, double _y, double newx, double newy) {
	int dx = newx - _x;
	int dy = newy - _y;
	vertice_node * temp = vhead->next;
	while (temp != NULL) {
		temp->x += dx;
		temp->y += dy;
		temp->left->x += dx;
		temp->left->y += dy;
		temp->right->x += dx;
		temp->right->y += dy;
		temp = temp->next;
	}
	xmax += dx;
	xmin += dx;
	ymax += dy;
	ymin += dy;
}

void Graphic::save_status(int & type, int & no_of_vertices, double  vertices_list[], int  status_int[], double  status_double[], char * & tex_, char * & text) {
	status_int[0] = xmin;
	status_int[1] = xmax;
	status_int[2] = ymin;
	status_int[3] = ymax;
	status_int[4] = x;
	status_int[5] = y;
	status_int[6] = w;
	status_int[7] = h;
	status_int[8] = solid;
	status_int[9] = border;
	status_int[10] = width;
	status_int[11] = tex;

	status_double[0] = colorInside[0];
	status_double[1] = colorInside[1];
	status_double[2] = colorInside[2];
	status_double[3] = colorInside[3];

	status_double[4] = colorBorder[0];
	status_double[5] = colorBorder[1];
	status_double[6] = colorBorder[2];
	status_double[7] = colorBorder[3];

	status_double[8] = colorHoverInside[0];
	status_double[9] = colorHoverInside[1];
	status_double[10] = colorHoverInside[2];
	status_double[11] = colorHoverInside[3];

	status_double[12] = colorHoverBorder[0];
	status_double[13] = colorHoverBorder[1];
	status_double[14] = colorHoverBorder[2];
	status_double[15] = colorHoverBorder[3];

	status_double[16] = colorText[0];
	status_double[17] = colorText[1];
	status_double[18] = colorText[2];
	status_double[19] = colorText[3];

	tex_ = tex_dir;

	text = _text;

	no_of_vertices = nvertices;
	int index = 0;

	vertice_node * temp = vhead->next;

	while (temp != NULL) {

		vertices_list[index] = temp->x;
		index++;
		vertices_list[index] = temp->y;
		index++;
		vertice_node * temp_left = temp->left;
		vertice_node * temp_right = temp->right;

		vertices_list[index] = temp_left->x;
		index++;
		vertices_list[index] = temp_left->y;
		index++;

		vertices_list[index] = temp_right->x;
		index++;
		vertices_list[index] = temp_right->y;
		index++;

		temp = temp->next;
	}
	type = _type;
}
void Graphic::load_status(int  type_, int no_of_vertices, double  vertices_list[], int  status_int[], double  status_double[], char *tex_, char *text) {
	xmin = status_int[0];
	xmax = status_int[1];
	ymin = status_int[2];
	ymax = status_int[3];
	x = status_int[4];
	y = status_int[5];
	w = status_int[6];
	h = status_int[7];
	solid = status_int[8];
	border = status_int[9];
	width = status_int[10];
	tex = status_int[11];

	colorInside[0] = status_double[0];
	colorInside[1] = status_double[1];
	colorInside[2] = status_double[2];
	colorInside[3] = status_double[3];

	colorBorder[0] = status_double[4];
	colorBorder[1] = status_double[5];
	colorBorder[2] = status_double[6];
	colorBorder[3] = status_double[7];

	colorHoverInside[0] = status_double[8];
	colorHoverInside[1] = status_double[9];
	colorHoverInside[2] = status_double[10];
	colorHoverInside[3] = status_double[11];

	colorHoverBorder[0] = status_double[12];
	colorHoverBorder[1] = status_double[13];
	colorHoverBorder[2] = status_double[14];
	colorHoverBorder[3] = status_double[15];

	colorText[0] = status_double[16];
	colorText[1] = status_double[17];
	colorText[2] = status_double[18];
	colorText[3] = status_double[19];

	char temp[100];
	if (tex_[0] != 'n') {
		strcpy(temp, tex_);
		temp[strlen(temp) - 1] = '\0';
		setTexImage(temp);
	}
	if (text[0] != 'n') {
		strcpy(temp, text);
		temp[strlen(temp) - 1] = '\0';
		setText(temp);
	}
	//nvertices = no_of_vertices;
	int innerindex = 0;
	//vertice_node * temp = vhead->next;
	while (innerindex < no_of_vertices) {
		addPoint(vertices_list[innerindex * 6], vertices_list[innerindex * 6 + 1]);
		vtail->left->x = vertices_list[innerindex * 6 + 2];
		vtail->left->y = vertices_list[innerindex * 6 + 3];
		vtail->right->x = vertices_list[innerindex * 6 + 4];
		vtail->right->y = vertices_list[innerindex * 6 + 5];
		innerindex++;
	}

	_type = (type)type_;
}