#include "stdafx.h"
#include "my_head.h"

char * opened_file = NULL;

double colorInside_buff[4] = { 1,1,1,trans };
double colorBorder_buff[4] = { 0,0,0,trans };

int leftMouse = 0;
int choosedType = 0;
int choosingColor = 0;
int slipType = 0;
int buttonin = 0;

double trans = 1;
double standard = 1;
double xtrans = 0;
double ytrans = 0;
double oldx, oldy;
double newx, newy;

user_op now_op = sys;
user_op last_op = sys;
int movingcanvas = 0;
int spinning = 0;
int changingpoints = 0;


void my_Mouse(int button, int state, double x, double y) {
	//视觉放大缩小的回调
	y = wh - y;
	x = x / standard + ((standard - 1) / standard) * ww / 2;
	y = y / standard + ((standard - 1) / standard) * wh / 2;

	//拓展的辅助键检测
	int mod = glutGetModifiers();

	//中键
	if (button == GLUT_WHEEL_UP) {
		standard *= 1.1;
		if (standard >= 0 && standard <= 2)
			slip[3].setPosition(rightBottom[1].x + (rightBottom[1].w / 2) * standard - 2, slip[3].y);
		glutPostRedisplay();
	}
	if (button == GLUT_WHEEL_DOWN) {
		standard *= 0.9;
		if (standard >= 0 && standard <= 2)
			slip[3].setPosition(rightBottom[1].x + (rightBottom[1].w / 2) * standard - 2, slip[3].y);
		glutPostRedisplay();
	}

	//左键
	if (button == GLUT_LEFT_BUTTON) {
		//按下
		if (state == GLUT_DOWN) {
			if (mod & GLUT_ACTIVE_ALT) {
				oldx = x;
				oldy = y;
				movingcanvas = 1;
			}
			else if (checkPressButton(x, y)) {}
			else {
				switch (now_op) {
				case sys: {
					now_op = drawing;
					graphList.newOne(x, y, 0, 0);
					graphList.ptail->setType(choosedType);
					graphList.ptail->addPoint(x + xtrans, y + ytrans);
					graphList.ptail->setColorInside(colorInside_buff[0], colorInside_buff[1], colorInside_buff[2]);
					graphList.ptail->setColorBorder(colorBorder_buff[0], colorBorder_buff[1], colorBorder_buff[2]);
					refreshStatus();
					break;
				}
				case drawing: {
					graphList.ptail->addPoint(x, y);
					refreshStatus();
					break;
				}
				case picking: {
					oldx = x;
					oldy = y;
					if (mod & GLUT_ACTIVE_CTRL)	spinning = 1;
					else checkPressEntry(x, y);
					break;
				}
				case movingpoint: {
					oldx = x;
					oldy = y;
					checkPressEntry(x, y);
					break;
				}
				default: printf("left button down no suit type\n");
				}
			}
		}
		//释放
		else {
			if (now_op == drawing) {
				switch (choosedType) {
					case 0: break;
					case 1: {
						leftMouse = 0;
						glutPostRedisplay();
						break;
					}
					case 2: break;
					case 3: {
						graphList.ptail->addPoint(graphList.ptail->vhead->next->x, y);
						graphList.ptail->addPoint(x, y);
						graphList.ptail->addPoint(x, graphList.ptail->vhead->next->y);
						now_op = sys;
						glutPostRedisplay();
						break;
					}
					case 4: {
						graphList.ptail->addPoint(x, y);
						graphList.ptail->addPoint(x, y);
						graphList.ptail->addPoint(x, y);

						vertice_node * temp1 = graphList.ptail->vhead->next;
						vertice_node * temp1l = temp1->left;
						vertice_node * temp1r = temp1->right;

						vertice_node * temp2 = temp1->next;
						vertice_node * temp2l = temp2->left;
						vertice_node * temp2r = temp2->right;

						vertice_node * temp3 = temp2->next;
						vertice_node * temp3l = temp3->left;
						vertice_node * temp3r = temp3->right;

						vertice_node * temp4 = temp3->next;
						vertice_node * temp4l = temp4->left;
						vertice_node * temp4r = temp4->right;

						double c = 0.551915024494;


						temp3->x = temp1->x = graphList.ptail->xmin + graphList.ptail->w / 2;
						temp2l->x = temp2r->x = temp2->x = graphList.ptail->xmax;
						temp4l->x = temp4r->x = temp4->x = graphList.ptail->xmin;
						temp3l->x = temp1r->x = temp1->x + graphList.ptail->w / 2 * c;
						temp3r->x = temp1l->x = temp1->x - graphList.ptail->w / 2 * c;

						temp2->y = temp4->y = graphList.ptail->ymin + graphList.ptail->h / 2;
						temp1l->y = temp1r->y = temp1->y = graphList.ptail->ymax;
						temp3l->y = temp3r->y = temp3->y = graphList.ptail->ymin;
						temp2l->y = temp4r->y = temp2->y + graphList.ptail->h / 2 * c;
						temp2r->y = temp4l->y = temp2->y - graphList.ptail->h / 2 * c;

						now_op = sys;
						if (graphList.ptail->w == 0 || graphList.ptail->h == 0) graphList.remove(graphList.size - 1);
						glutPostRedisplay();
						break;
					}
					default: printf("left button up drawing no suit type\n");
				}
			}
			if (now_op == slipping) {
				now_op = last_op;
			}
			else if(changingpoints) changingpoints = 0;
			else if (spinning) spinning = 0;
			else if (movingcanvas) movingcanvas = 0;
		}
	}

	//右键
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN && now_op == drawing) {
			now_op = sys;
			glutPostRedisplay();
		}
	}
}

void my_PassiveMotion(double x, double y) {
	y = wh - y;
	x = x / standard + ((standard - 1) / standard) * ww / 2;
	y = y / standard + ((standard - 1) / standard) * wh / 2;

	Button *target = checkInButton(x, y);
	if (target != NULL) {
		buttonin = 1;
		target->mouseHover();
		target->mouseIn = 1;
	}
	else {
		buttonin = 0;
		glutPostRedisplay();
	}

	newx = x;
	newy = y;
	if (now_op == drawing) {
		if (graphList.ptail->nvertices != 0) {
			glutPostRedisplay();
		}
	}
	else if (now_op == picking) {
		Graphic * temp = graphList.phead->next;
		while (temp != NULL) {
			if (temp->picked == 1) break;
			temp = temp->next;
		}
		if(temp != NULL && x < temp->xmax && x > temp->xmin && y < temp->ymax && y > temp->ymin) glutAttachMenu(GLUT_RIGHT_BUTTON);
		else glutDetachMenu(GLUT_RIGHT_BUTTON);
	}
}

void my_Motion(double x, double y) {
	leftMouse = 1;
	y = wh - y;
	x = x / standard + ((standard - 1) / standard) * ww / 2;
	y = y / standard + ((standard - 1) / standard) * wh / 2;
	if (movingcanvas) {
		Graphic * temp = graphList.phead->next;
		while (temp != NULL) {
			temp->movePoints(oldx, oldy, x, y);
			temp = temp->next;
		}
		//xtrans += x - oldx;
		//ytrans += y - oldy;
		oldy = y;
		oldx = x;
		glutPostRedisplay();
	}
	else if (now_op == drawing) {
		if (choosedType == 1 && graphList.ptail->nvertices>1) {
			graphList.ptail->vtail->left->x = 2 * graphList.ptail->vtail->x - x;
			graphList.ptail->vtail->left->y = 2 * graphList.ptail->vtail->y - y;
			graphList.ptail->vtail->right->x = x;
			graphList.ptail->vtail->right->y = y;
			newx = x;
			newy = y;
			refreshStatus();
			glutPostRedisplay();
		}
		else if (graphList.ptail->nvertices != 0) {
			newx = x;
			newy = y;
			refreshStatus();
			glutPostRedisplay();
		}
	}
	else if (now_op == slipping) {
		x = x*standard - (standard - 1) * ww / 2;
		y = y*standard - (standard - 1) * wh / 2;
		int i = slipType;

		//更新位置
		if (i == 0) slip[i].setPosition((x >= rightTop[0].x && x <= rightTop[0].x + rightTop[0].w ? x - 3 : slip[i].x), (y >= rightTop[0].y && y <= rightTop[0].y + rightTop[0].h ? y - 3 : slip[i].y));
		else if (i == 1 && x >= rightTop[1].x && x <= rightTop[1].x + rightTop[1].w) slip[i].setPosition(x - 2, slip[i].y);
		else if (i == 2 && x >= rightMiddle[3].x  && x <= rightMiddle[3].x + rightMiddle[3].w) slip[i].setPosition(x - 2, slip[i].y);
		else if (i == 3 && x >= rightBottom[1].x  && x <= rightBottom[1].x + rightBottom[1].w) slip[i].setPosition(x - 2, slip[i].y);

		double r = 0;
		double g = 0;
		double b = 0;

		//更新相联板块
		if (i == 0) {
			double dx = (double)(x - rightTop[0].x) / (double)rightTop[0].w;
			double dy = -(double)(2 * y - 2 * rightTop[0].y - rightTop[0].h) / (double)rightTop[0].h;

			if (dx>1) dx = 1;
			else if (dx<0) dx = 0;
			if (dy>1) dy = 1;
			else if (dy<-1) dy = -1;

			if (dx < 1.0 / 6.0) {
				r = 1;
				g = dx * 6;
			}
			else if (dx < 2.0 / 6.0) {
				r = 1 - (dx - 1.0 / 6.0) * 6;
				g = 1;
			}
			else if (dx < 3.0 / 6.0) {
				g = 1;
				b = (dx - 2.0 / 6.0) * 6;
			}
			else if (dx < 4.0 / 6.0) {
				g = 1 - (dx - 3.0 / 6.0) * 6;
				b = 1;
			}
			else if (dx < 5.0 / 6.0) {
				b = 1;
				r = (dx - 4.0 / 6.0) * 6;
			}
			else {
				b = 1 - (dx - 5.0 / 6.0) * 6;
				r = 1;
			}

			if (dy < 0) {
				r += r * dy;
				g += g * dy;
				b += b * dy;
			}
			else {
				r += (1 - r) * dy;
				g += (1 - g) * dy;
				b += (1 - b) * dy;
			}


			rightTop[1].setColorInside(r, g, b);
			rightTop[3].setColorInside(r, g, b);
			slip[1].setPosition(rightTop[1].x + rightTop[1].w / 2 - 2, rightTop[1].y);
		}
		if (i == 1) {
			double dx = -(double)(2 * x - 2 * rightTop[1].x - rightTop[1].w) / (double)rightTop[1].w;
			r = rightTop[1].colorInside[0];
			g = rightTop[1].colorInside[1];
			b = rightTop[1].colorInside[2];
			if (dx < 0) {
				r += r * dx;
				g += g * dx;
				b += b * dx;
			}
			else {
				r += (1 - r) * dx;
				g += (1 - g) * dx;
				b += (1 - b) * dx;
			}
			rightTop[3].setColorInside(r, g, b);
		}
		if (i == 2) {
			if (choosingColor == 0) {
				r = rightMiddle[1].colorInside[0];
				g = rightMiddle[1].colorInside[1];
				b = rightMiddle[1].colorInside[2];
			}
			else {
				r = rightMiddle[3].colorInside[0];
				g = rightMiddle[3].colorInside[1];
				b = rightMiddle[3].colorInside[2];
			}
			trans = 1 - (double)(x - rightMiddle[3].x) / (double)rightMiddle[3].w;
		}
		if (i == 3) {
			if (choosingColor == 0) {
				r = rightMiddle[1].colorInside[0];
				g = rightMiddle[1].colorInside[1];
				b = rightMiddle[1].colorInside[2];
			}
			else {
				r = rightMiddle[3].colorInside[0];
				g = rightMiddle[3].colorInside[1];
				b = rightMiddle[3].colorInside[2];
			}
			double _standard = (slip[3].x - rightBottom[1].x + 2) / ((double)rightBottom[1].w / 2);
			if (_standard < 2 && _standard > 0)
				standard = _standard;
		}
		if (choosingColor == 0) {
			colorInside_buff[0] = r;
			colorInside_buff[1] = g;
			colorInside_buff[2] = b;
			rightMiddle[1].setColorInside(r, g, b);
		}
		else {
			colorBorder_buff[0] = r;
			colorBorder_buff[1] = g;
			colorBorder_buff[2] = b;
			rightMiddle[3].setColorInside(r, g, b);
		}
		
		Graphic * temp = graphList.phead->next;
		while (temp != NULL) {
			if (temp->picked == 1) {
				if (choosingColor == 0) temp->setColorInside(r, g, b, trans);
				else temp->setColorBorder(r, g, b, trans);
				break;
			}
			temp = temp->next;
		}
		refreshStatus();
		glutPostRedisplay();
		
	}
	else if (now_op == picking) {
		if (buttonin) {
			return;
		}
		Graphic * temp = graphList.phead->next;
		while (temp != NULL) {
			if (temp->picked == 1) {
				if (spinning) {
					double theta;
					double cx = temp->xmin + temp->w / 2;
					double cy = temp->ymin + temp->h / 2;
					theta = (acos((x - cx) / sqrt((x - cx)*(x - cx) + (y - cy)*(y - cy))) - acos((oldx - cx) / sqrt((oldx - cx)*(oldx - cx) + (oldy - cy)*(oldy - cy))));
					if (y - cy < 0) theta = -theta;
					temp->spin(theta);
				}
				else if (changingpoints) temp->changePoints(oldx, oldy, x, y);
				else temp->movePoints(oldx, oldy, x, y);
				oldy = y;
				oldx = x;

				break;
			}
			temp = temp->next;
		}
		refreshStatus();
		glutPostRedisplay();
	}
	else if (now_op == movingpoint) {
		Graphic * temp = graphList.phead->next;
		while (temp != NULL) {
			if (temp->blick == 1) {
				temp->movePoint(oldx, oldy, x, y);
				oldx = x;
				oldy = y;

				break;
			}
			temp = temp->next;
		}
		refreshStatus();
		glutPostRedisplay();
	}
}

Button * checkInButton(double x, double y) {
	x = x*standard - (standard - 1) * ww / 2;
	y = y*standard - (standard - 1) * wh / 2;

	for (int i = 0; i < BUTTON_COUNT; i++) {
		if (button_list[i]->checkIn(x, y)) return button_list[i];
	}
	return NULL;
}

int checkPressButton(double x, double y) {
	Button * target = checkInButton(x, y);

	x = x*standard - (standard - 1) * ww / 2;
	y = y*standard - (standard - 1) * wh / 2;

	if (target == NULL) return 0;

	char * temp = target->button_name;

	if (target >= &leftTop[0] && target <= &leftTop[LEFTTOP - 1]) {
		if (strcmp(temp, "open") == 0) loadEntry();
		else if (strcmp(temp, "create") == 0) newFile();
		else if (strcmp(temp, "save") == 0) saveEntry(1);
		else if (strcmp(temp, "saveas") == 0) saveEntry(0);
	}
	else if (target >= &leftBottom[0] && target <= &leftBottom[LEFTBOTTOM - 4]) {
		if (now_op == picking || now_op == movingpoint) {
			Graphic *temp = graphList.phead->next;
			while (temp != NULL) {
				if (temp->picked) {
					temp->picked = 0;
					break;
				}
				else if (temp->blick) {
					temp->blick = 0;
					break;
				}
				temp = temp->next;
			}
			glutPostRedisplay();
		}
		now_op = sys;
		if (strcmp(temp, "line") == 0) choosedType = 0;
		else if (strcmp(temp, "curve") == 0) choosedType = 1;
		else if (strcmp(temp, "polygon") == 0) choosedType = 2;
		else if (strcmp(temp, "square") == 0) choosedType = 3;
		else if (strcmp(temp, "circle") == 0) choosedType = 4;
	}
	else if ((target >= &slip[0] && target <= &slip[SLIP - 1]) || (target == &rightTop[0]) || (target == &rightTop[1]) || (target == &rightMiddle[7]) || (target == &rightBottom[1])) {
		last_op = now_op;
		now_op = slipping;
		if (temp == NULL) {
			if (target == &rightTop[0]) slipType = 0;
			else if (target == &rightTop[1]) slipType = 1;
			else if (target == &rightMiddle[7]) slipType = 2;
			else if (target == &rightBottom[1]) slipType = 3;
		}
		else {
			if (strcmp(temp, "slip1") == 0) slipType = 0;
			else if (strcmp(temp, "slip2") == 0) slipType = 1;
			else if (strcmp(temp, "slip3") == 0) slipType = 2;
			else if (strcmp(temp, "slip4") == 0) slipType = 3;
		}
	}
	else if (target == &rightMiddle[1]) {
		choosingColor = 0;
		rightMiddle[1].setBorder();
		rightMiddle[3].setBorder(0);
	}
	else if (target == &rightMiddle[3]) {
		choosingColor = 1;
		rightMiddle[1].setBorder(0);
		rightMiddle[3].setBorder();
	}
	else if (target == &rightMiddle[5]) {
		chooseTex();
	}
	else if (temp == NULL) {}
	else if (strcmp(temp, "delete") == 0 && now_op == picking) {
		Graphic * temp = graphList.phead->next;
		int i = 0;
		while (temp != NULL) {
			if (temp->picked) break;
			temp = temp->next;
			i++;
		}
		graphList.remove(i);
		glutPostRedisplay();
	}
	else if (strcmp(temp, "arrow1") == 0) {
		if (now_op == movingpoint) {
			Graphic *temp = graphList.phead->next;
			while (temp != NULL) {
				if (temp->blick) {
					temp->blick = 0;
					break;
				}
				temp = temp->next;
			}
			glutPostRedisplay();
		}
		now_op = picking;
	}
	else if (strcmp(temp, "arrow2") == 0) {
		if (now_op == picking) {
			Graphic *temp = graphList.phead->next;
			while (temp != NULL) {
				if (temp->picked) {
					temp->picked = 0;
					break;
				}
				temp = temp->next;
			}
			glutPostRedisplay();
		}
		now_op = movingpoint;
	}

	return 1;
}

void checkPressEntry(double x, double y) {
	x = x*standard - (standard - 1) * ww / 2;
	y = y*standard - (standard - 1) * wh / 2;
	GLuint selectBuff[1000] = { 0 };//创建一个保存选择结果的数组    
	GLint hits, viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport); //获得viewport    
	glSelectBuffer(2000, selectBuff); //告诉OpenGL初始化  selectbuffer    
	glRenderMode(GL_SELECT);    //进入选择模式    

	glInitNames();  //初始化名字栈    
	glPushName(0);  //在名字栈中放入一个初始化名字，这里为‘0’    

	glMatrixMode(GL_PROJECTION);    //进入投影阶段准备拾取    
	glPushMatrix();     //保存以前的投影矩阵    
	glLoadIdentity();   //载入单位矩阵    


	gluPickMatrix(x, y, 4, 4, viewport);
	gluOrtho2D(0.0, ww, 0.0, wh);

	glInitNames();

	graphList.showAll();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);


	hits = glRenderMode(GL_RENDER); // 从选择模式返回正常模式,该函数返回选择到对象的个数    
	GLuint names = 0;
	if (hits > 0) {
		GLuint *ptr, minZ;
		ptr = (GLuint *)selectBuff;
		minZ = 0xffffffff;
		for (int i = 0; i < hits; i++) {
			if (*(ptr + 1) <= minZ && *(ptr + 3) != 0) {
				minZ = *(ptr + 1);
				names = *(ptr + 3);
			}
			ptr += 4;
		}
	}
	if (names == 1) {
		changingpoints = 1;
		return;
	}
	Graphic * temp = graphList.phead->next;
	while (temp != NULL) {
		if (temp->insideNameId == names || temp->borderNameId == names) {
			if (now_op == picking) temp->picked = 1;
			else if (now_op == movingpoint) temp->blick = 1;
			refreshStatus();
		}
		else {
			if (now_op == picking) temp->picked = 0;
			else if (now_op == movingpoint) temp->blick = 0;
		}
		temp = temp->next;
	}
	glutPostRedisplay();
}

void chooseTex() {
	if (now_op != picking) {
		char *message = "choose a graph first";
		char *title = "warning";
		WCHAR *message_w = charToWchar(message);
		WCHAR *title_w = charToWchar(title);
		int check = MessageBox(NULL, message_w, title_w, MB_OK);
		free(message_w);
		free(title_w);
		return;
	}

	char *message = "switch tex?";
	char *title = "tex choice";
	WCHAR *message_w = charToWchar(message);
	WCHAR *title_w = charToWchar(title);
	int check = MessageBox(NULL, message_w, title_w, MB_YESNOCANCEL);
	free(message_w);
	free(title_w);

	if (check == IDCANCEL) return;
	else if (check == IDYES) {
		OPENFILENAME ofn = { 0 };
		TCHAR szOpenFileNames[MAX_PATH] = { 0 };	//用于接收文件名  
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(OPENFILENAME);		//结构体大小  
		ofn.hwndOwner = NULL;						//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄  
		ofn.lpstrFilter = TEXT("BMP Files(*.bmp)\0*.bmp\0All Files(*.*)\0*.*\0\0");//设置过滤  
		ofn.nFilterIndex = 1;						//过滤器索引  
		ofn.lpstrFile = szOpenFileNames;			//接收返回的文件名，注意第一个字符需要为NULL  
		ofn.nMaxFile = sizeof(szOpenFileNames);		//缓冲区长度  
		ofn.lpstrInitialDir = NULL;					//初始目录为默认  
		ofn.lpstrTitle = TEXT("请选择一个文件");	//使用系统默认标题留空即可  

		char * tex_buff = NULL;
		if (GetOpenFileName(&ofn)) tex_buff = wcharToChar(szOpenFileNames);
		else {
			char *message = "set tex failed";
			char *title = "warning";
			WCHAR *message_w = charToWchar(message);
			WCHAR *title_w = charToWchar(title);
			int check = MessageBox(NULL, message_w, title_w, MB_OK);
			free(message_w);
			free(title_w);
			return;
		}
		
		Graphic * temp = graphList.phead->next;
		while (temp != NULL) {
			if (temp->picked == 1) {
				temp->setTexImage(tex_buff);
				temp->setTex(1);
				break;
			}
			temp = temp->next;
		}
	}
	else {
		Graphic * temp = graphList.phead->next;
		while (temp != NULL) {
			if (temp->picked == 1) {
				temp->setTexImage(NULL);
				temp->setTex(0);
				break;
			}
			temp = temp->next;
		}
	}
}

void saveEntry(int s) {
	if (s == 0 || opened_file == NULL) {
		OPENFILENAME ofn = { 0 };
		TCHAR szOpenFileNames[MAX_PATH] = { 0 };		//用于接收文件名  
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(OPENFILENAME);		//结构体大小  
		ofn.hwndOwner = NULL;						//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄  
		ofn.lpstrFilter = TEXT("mytype Files(*.mytype)\0*.mytype\0All Files(*.*)\0*.*\0\0");//设置过滤  
		ofn.nFilterIndex = 1;						//过滤器索引  
		ofn.lpstrFile = szOpenFileNames;			//接收返回的文件名，注意第一个字符需要为NULL  
		ofn.nMaxFile = sizeof(szOpenFileNames);		//缓冲区长度  
		ofn.lpstrInitialDir = NULL;					//初始目录为默认  
		ofn.lpstrTitle = TEXT("请选择一个文件");	//使用系统默认标题留空即可  

		if (GetSaveFileName(&ofn))
		{
			if(opened_file != NULL) delete opened_file;
			opened_file = wcharToChar(szOpenFileNames);
		}
		else {
			char *message = "save failed";
			char *title = "warning";
			WCHAR *message_w = charToWchar(message);
			WCHAR *title_w = charToWchar(title);
			int check = MessageBox(NULL, message_w, title_w, MB_OK);
			free(message_w);
			free(title_w);
			return;
		}
	}

	FILE *fp;
	fp = fopen(opened_file, "wb");

	fwrite(&(graphList.size), sizeof(int), 1, fp);
	int type;
	int no_of_vertices;
	int  status_int[12];
	double  status_double[20];
	double  *vertices_list;
	char *tex;
	char *text;
	Graphic * temp = graphList.phead->next;
	while (temp != NULL) {
		vertices_list = new double[temp->nvertices * 3 * 2];

		temp->save_status(type, no_of_vertices, vertices_list, status_int, status_double, tex, text);
		/*
		printf("%d\n", type);
		printf("%d\n", no_of_vertices);
		for (int i = 0; i < no_of_vertices*3 * 2; ++i)
		{
		printf("%lf ", vertices_list[i]);
		}
		printf("\n");
		for (int i = 0; i < 12; ++i)
		{
		printf("%d ", status_int[i]);
		}
		printf("\n");
		for (int i = 0; i < 20; ++i)
		{
		printf("%d ", status_double[i]);
		}
		printf("\n");
		if(tex == NULL) printf("n\n");
		else printf("%s\n", tex);
		if(text == NULL) printf("n\n");
		else printf("%s\n", text);
		printf("==================================================================================\n");
		//*/

		fwrite(&type, sizeof(type), 1, fp);
		fwrite(&no_of_vertices, sizeof(no_of_vertices), 1, fp);
		fwrite(vertices_list, sizeof(vertices_list[0]), temp->nvertices * 3 * 2, fp);
		fwrite(status_int, sizeof(status_int[0]), 12, fp);
		fwrite(status_double, sizeof(status_double[0]), 20, fp);
		if (tex == NULL) {
			fputs("n\n", fp);
		}
		else {
			fputs(tex, fp);
			fputs("\n", fp);
		}
		if (text == NULL) {
			fputs("n\n", fp);
		}
		else {
			fputs(text, fp);
			fputs("\n", fp);
		}
		temp = temp->next;
	}
	fclose(fp);
}

void loadEntry() {
	OPENFILENAME ofn = { 0 };
	TCHAR szOpenFileNames[MAX_PATH] = { 0 };		//用于接收文件名  
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);		//结构体大小  
	ofn.hwndOwner = NULL;						//拥有着窗口句柄，为NULL表示对话框是非模态的，实际应用中一般都要有这个句柄  
	ofn.lpstrFilter = TEXT("mytype Files(*.mytype)\0*.mytype\0All Files(*.*)\0*.*\0\0");//设置过滤  
	ofn.nFilterIndex = 1;						//过滤器索引  
	ofn.lpstrFile = szOpenFileNames;			//接收返回的文件名，注意第一个字符需要为NULL  
	ofn.nMaxFile = sizeof(szOpenFileNames);		//缓冲区长度  
	ofn.lpstrInitialDir = NULL;					//初始目录为默认  
	ofn.lpstrTitle = TEXT("请选择一个文件");	//使用系统默认标题留空即可  

	if (GetOpenFileName(&ofn)){
		if (opened_file != NULL) delete opened_file;
		opened_file = wcharToChar(szOpenFileNames);
	}
	else{
		char *message = "save failed";
		char *title = "warning";
		WCHAR *message_w = charToWchar(message);
		WCHAR *title_w = charToWchar(title);
		int check = MessageBox(NULL, message_w, title_w, MB_OK);
		free(message_w);
		free(title_w);
		return;
	}

	newFile();

	FILE *fp;
	fp = fopen(opened_file, "rb");

	if (fp == 0) return;

	int n;
	fread(&n, sizeof(int), 1, fp);
	int type;
	int no_of_vertices;
	int  status_int[12];
	double  status_double[20];
	double  *vertices_list;
	char *tex = new char[1000];
	char *text = new char[1000];

	int index = 0;
	while (index<n && !feof(fp)) {
		graphList.newOne(0,0,0,0);
		Graphic * temp = graphList.ptail;
		fread(&type, sizeof(type), 1, fp);
		fread(&no_of_vertices, sizeof(no_of_vertices), 1, fp);
		vertices_list = new double[no_of_vertices * 3 * 3];
		fread(vertices_list, sizeof(vertices_list[0]), no_of_vertices * 3 * 2, fp);
		fread(status_int, sizeof(status_int[0]), 12, fp);
		fread(status_double, sizeof(status_double[0]), 20, fp);
		fgets(tex, 1000, fp);
		fgets(text, 1000, fp);
		/*
		printf("%d\n", type);
		printf("%d\n", no_of_vertices);
		for (int i = 0; i < no_of_vertices*3 * 2; ++i)
		{
		printf("%lf ", vertices_list[i]);
		}
		printf("\n");
		for (int i = 0; i < 12; ++i)
		{
		printf("%d ", status_int[i]);
		}
		printf("\n");
		for (int i = 0; i < 20; ++i)
		{
		printf("%d ", status_double[i]);
		}
		printf("\n");

		printf("%s", tex);
		printf("%s", text);
		printf("==========================================================================\n");
		//*/
		temp->load_status(type, no_of_vertices, vertices_list, status_int, status_double, tex, text);

		index++;
		delete vertices_list;
	}
	delete tex;
	delete text;
	fclose(fp);
}

void newFile() {
	if (graphList.size != 0) {
		char *message = "save current file ?";
		char *title = "warning";
		WCHAR *message_w = charToWchar(message);
		WCHAR *title_w = charToWchar(title);
		int check = MessageBox(NULL, message_w, title_w, MB_YESNOCANCEL);
		free(message_w);
		free(title_w);
		if (check == IDCANCEL) {}
		else{
			if (check == IDYES) {
				if (opened_file == NULL) saveEntry(0);
				else saveEntry(1);
			}
			graphList.clearAll();
			glutPostRedisplay();
		}
	}
}

void newColor() {
	static CHOOSECOLOR stChooseColor;
	static COLORREF rgbLineColor;
	HWND aaaaa = GetForegroundWindow();
	COLORREF retColor = RGB(255, 0, 0);
	COLORREF cusColor[16];
	stChooseColor.lStructSize = sizeof(CHOOSECOLOR);
	stChooseColor.hwndOwner = aaaaa;
	stChooseColor.rgbResult = rgbLineColor;
	stChooseColor.lpCustColors = (LPDWORD)cusColor;
	stChooseColor.Flags = CC_RGBINIT;
	stChooseColor.lCustData = 0;
	stChooseColor.lpfnHook = NULL;
	stChooseColor.lpTemplateName = NULL;
	if (ChooseColor(&stChooseColor))
	{
		rgbLineColor = stChooseColor.rgbResult;
	}
}

void showMoving() {
	if (now_op == drawing) {
		if (choosedType == 4) {
			int n = 3600;
			int xmin = min(newx, graphList.ptail->vtail->x);
			int ymin = min(newy, graphList.ptail->vtail->y);
			if (graphList.ptail->solid) {
				glColor4dv(graphList.ptail->colorInside);
				glBegin(GL_POLYGON);
				for (int i = 0; i<n; i++)
				{
					glVertex2d((fabs(newx - graphList.ptail->vtail->x) / 2 * cos(2 * 3.1415926*i / n) + xmin + fabs(newx - graphList.ptail->vtail->x) / 2)*standard - (standard - 1) * ww / 2, (fabs(newy - graphList.ptail->vtail->y) / 2 * sin(2 * 3.1415926*i / n) + ymin + fabs(newy - graphList.ptail->vtail->y) / 2)*standard - (standard - 1) * wh / 2);
				}
				glEnd();
			}
			glColor4dv(graphList.ptail->colorBorder);
			glBegin(GL_LINE_STRIP & GL_LINE_LOOP);
			for (int i = 0; i<n; i++)
			{
				glVertex2d((fabs(newx - graphList.ptail->vtail->x) / 2 * cos(2 * 3.1415926*i / n) + xmin + fabs(newx - graphList.ptail->vtail->x) / 2)*standard - (standard - 1) * ww / 2, (fabs(newy - graphList.ptail->vtail->y) / 2 * sin(2 * 3.1415926*i / n) + ymin + fabs(newy - graphList.ptail->vtail->y) / 2)*standard - (standard - 1) * wh / 2);
			}
			glEnd();
			glFlush();
		}
		else if (choosedType == 3) {
			if (graphList.ptail->solid) {
				glColor4dv(graphList.ptail->colorInside);
				glBegin(GL_POLYGON);
				glVertex2d(graphList.ptail->vtail->x*standard - (standard - 1) * ww / 2, graphList.ptail->vtail->y*standard - (standard - 1) * wh / 2);
				glVertex2d(graphList.ptail->vtail->x*standard - (standard - 1) * ww / 2, newy*standard - (standard - 1) * wh / 2);
				glVertex2d(newx*standard - (standard - 1) * ww / 2, newy*standard - (standard - 1) * wh / 2);
				glVertex2d(newx*standard - (standard - 1) * ww / 2, graphList.ptail->vtail->y*standard - (standard - 1) * wh / 2);
				glEnd();
			}
			glColor4dv(graphList.ptail->colorBorder);
			glBegin(GL_LINE_STRIP & GL_LINE_LOOP);
			glVertex2d(graphList.ptail->vtail->x*standard - (standard - 1) * ww / 2, graphList.ptail->vtail->y*standard - (standard - 1) * wh / 2);
			glVertex2d(graphList.ptail->vtail->x*standard - (standard - 1) * ww / 2, newy*standard - (standard - 1) * wh / 2);
			glVertex2d(newx*standard - (standard - 1) * ww / 2, newy*standard - (standard - 1) * wh / 2);
			glVertex2d(newx*standard - (standard - 1) * ww / 2, graphList.ptail->vtail->y*standard - (standard - 1) * wh / 2);
			glEnd();
			glFlush();
		}
		else if (choosedType == 1) {
			if (leftMouse) {
				glColor4d(0, 0, 0, 1);
				glBegin(GL_LINE_STRIP);
				glVertex2d(graphList.ptail->vtail->left->x*standard - (standard - 1) * ww / 2, graphList.ptail->vtail->left->y*standard - (standard - 1) * wh / 2);
				glVertex2d(graphList.ptail->vtail->x*standard - (standard - 1) * ww / 2, graphList.ptail->vtail->y*standard - (standard - 1) * wh / 2);
				glVertex2d(newx*standard - (standard - 1) * ww / 2, newy*standard - (standard - 1) * wh / 2);
				glEnd();
				glFlush();
			}
			else {
				glColor4dv(graphList.ptail->colorBorder);
				glBegin(GL_LINES);
				if (graphList.ptail->nvertices != 0) {
					glVertex2d(graphList.ptail->vtail->x*standard - (standard - 1) * ww / 2, graphList.ptail->vtail->y*standard - (standard - 1) * wh / 2);
					glVertex2d(newx*standard - (standard - 1) * ww / 2, newy*standard - (standard - 1) * wh / 2);
				}
				glEnd();
				glFlush();
			}
		}
		else {
			glColor4dv(graphList.ptail->colorBorder);
			glBegin(GL_LINES);
			if (graphList.ptail->nvertices != 0) {
				glVertex2d(graphList.ptail->vtail->x*standard - (standard - 1) * ww / 2, graphList.ptail->vtail->y*standard - (standard - 1) * wh / 2);
				glVertex2d(newx*standard - (standard - 1) * ww / 2, newy*standard - (standard - 1) * wh / 2);
			}
			glEnd();
			glFlush();
		}
	}
}

void refreshStatus() {
	Graphic * temp = graphList.ptail;

	if (temp == NULL || temp->vhead->next == NULL) return;
	if (now_op != drawing) {
		temp = graphList.phead->next;
		while (temp != NULL) {
			if (temp->picked || temp->blick) break;
			temp = temp->next;
		}

		if (temp == NULL) return;
		char xstr[10] = { 'x',':' };
		char ystr[10] = { 'y',':' };
		char wstr[10] = { 'w',':' };
		char hstr[10] = { 'h',':' };
		_itoa((int)temp->xmin, &xstr[2], 10);
		_itoa((int)temp->ymin, &ystr[2], 10);
		_itoa((int)temp->w, &wstr[2], 10);
		_itoa((int)temp->h, &hstr[2], 10);

		rightMiddle[1].setColorInside(temp->colorInside[0], temp->colorInside[1], temp->colorInside[2]);
		rightMiddle[3].setColorInside(temp->colorBorder[0], temp->colorBorder[1], temp->colorBorder[2]);
		rightMiddle[8].setText(xstr);
		rightMiddle[9].setText(ystr);
		rightMiddle[10].setText(wstr);
		rightMiddle[11].setText(hstr);
		if (temp->tex) {
			rightMiddle[5].setTexImage(temp->tex_dir);
			rightMiddle[5].setTex(1);
		}
		else rightMiddle[5].setTex(0);
	}
}

WCHAR * charToWchar(char *s) {
	int w_nlen = MultiByteToWideChar(CP_ACP, 0, s, -1, NULL, 0);
	WCHAR *ret;
	ret = (WCHAR*)malloc(sizeof(WCHAR)*w_nlen);
	memset(ret, 0, sizeof(ret));
	MultiByteToWideChar(CP_ACP, 0, s, -1, ret, w_nlen);
	return ret;
}

char* wcharToChar(LPWSTR lpwszStrIn){
	LPSTR pszOut = NULL;
	if (lpwszStrIn != NULL)
	{
		int nInputStrLen = wcslen(lpwszStrIn);

		// Double NULL Termination  
		int nOutputStrLen = WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, NULL, 0, 0, 0) + 2;
		pszOut = new char[nOutputStrLen];

		if (pszOut)
		{
			memset(pszOut, 0x00, nOutputStrLen);
			WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, pszOut, nOutputStrLen, 0, 0);
		}
	}
	return pszOut;
}