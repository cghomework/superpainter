
int leftMouse = 0;
int oldx,oldy;
//鼠标按键事件
void myMouse(int button, int state, int x, int y){
	y = wh-y;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(checkPressButton(x,y) == 1) return;
		if(drawing){
			entryList.ptail->addPoint(x,y);
		}
		else if(picking){
			oldx = x;
			oldy = y;
			checkPressEntry(x,y);
		}
		else{
			drawing = 1;
			entryList.newOne();
			entryList.ptail->setType(choosedType);
			entryList.ptail->addPoint(x,y);
			if(choosedType == 3) entryList.ptail->addPoint(x,y);
		}
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && drawing){
		drawing = 0;
		glutPostRedisplay();
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && drawing && choosedType == 4){
		entryList.ptail->addPoint(x,y);
		entryList.ptail->addPoint(x,y);
		entryList.ptail->addPoint(x,y);
		vertice_node * temp1 = entryList.ptail->vhead->next;
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

		temp3->x = temp1->x = entryList.ptail->xmin + entryList.ptail->w/2;
		temp2l->x = temp2r->x = temp2->x = entryList.ptail->xmax;
		temp4l->x = temp4r->x = temp4->x = entryList.ptail->xmin;
		temp3l->x = temp1r->x = temp1->x + entryList.ptail->w/2 * c;
		temp3r->x = temp1l->x = temp1->x - entryList.ptail->w/2 * c;

		temp2->y = temp4->y = entryList.ptail->ymin + entryList.ptail->h/2;
		temp1l->y = temp1r->y = temp1->y = entryList.ptail->ymax;
		temp3l->y = temp3r->y = temp3->y = entryList.ptail->ymin;
		temp2l->y = temp4r->y = temp2->y + entryList.ptail->h/2 * c;
		temp2r->y = temp4l->y = temp2->y - entryList.ptail->h/2 * c;

		drawing = 0;
		if(entryList.ptail->w == 0 ||entryList.ptail->h == 0) entryList.remove(entryList.size - 1);
		glutPostRedisplay();
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && drawing && choosedType == 3){
		entryList.ptail->addPoint(entryList.ptail->vhead->next->x,y);
		entryList.ptail->addPoint(x,y);
		entryList.ptail->addPoint(x,entryList.ptail->vhead->next->y);
		drawing = 0;
		glutPostRedisplay();
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && choosedType == 1){
		leftMouse = 0;
		glutPostRedisplay();
	}
}

int newx,newy;
//鼠标一般移动事件
void myPassiveMotion(int x, int y){
	y = wh -y;
	checkInButton(x,y);
	if(drawing){
		if(entryList.ptail->nvertices!=0){
			newx = x;
			newy = y;
			glutPostRedisplay();
		}
	}
}

//鼠标按键移动事件
void myMotion(int x,int y){
	leftMouse =1;
	y = wh -y;
	if(drawing){
		if(choosedType == 1 && entryList.ptail->nvertices>1){
			entryList.ptail->vtail->left->x = 2 * entryList.ptail->vtail->x - x;
			entryList.ptail->vtail->left->y = 2 * entryList.ptail->vtail->y - y;
			entryList.ptail->vtail->right->x = x;
			entryList.ptail->vtail->right->y = y;
			newx = x;
			newy = y;
			glutPostRedisplay();
		}
		else if(entryList.ptail->nvertices!=0){
			newx = x;
			newy = y;
			glutPostRedisplay();
		}
	}
	else if(picking){
		entry_node * temp = entryList.phead->next;
		while(temp!=NULL){
			if(temp->picked == 1){
				temp->movePoints(oldx,oldy,x,y);
				oldx = x;
				oldy = y;
				break;
			}
			temp = temp->next;
		}
		glutPostRedisplay();
	}
	else if(slipping){
		int i  = 0;
		for(i = 0; i < SLIP;i++){
			if(slip[i].mouseIn) break;
		}

		//更新位置
		if(i == 0) slip[i].setPosition((x>=rightTop[0].x && x <=rightTop[0].x+ rightTop[0].w?x-3:slip[i].x),(y>=rightTop[0].y && y <=rightTop[0].y+rightTop[0].h?y-3:slip[i].y));
		else if(i == 1 && x>=rightTop[1].x && x <=rightTop[1].x+ rightTop[1].w) slip[i].setPosition(x-2,slip[i].y);
		else if(i == 2 && x>=rightMiddle[3].x  && x <=rightMiddle[3].x+ rightMiddle[3].w) slip[i].setPosition(x-2,slip[i].y);
		else if(i == 3 && x>=rightBottom[1].x  && x <=rightBottom[1].x+ rightBottom[1].w) slip[i].setPosition(x-2,slip[i].y);

		//更新相联板块
		//if(i == 0){
		//	if(slip[i].x + 3 <)
		//}

		glutPostRedisplay();
	}
}

void showMoving(){
	if(drawing){
		if(choosedType == 4){
			int n = 3600;
			int xmin = min(newx,entryList.ptail->vtail->x);
			int ymin = min(newy,entryList.ptail->vtail->y);
		    if(entryList.ptail->solid){
		    	glColor4dv(entryList.ptail->colorInside);  
			    glBegin(GL_POLYGON);  
			    for(int i=0;i<n;i++)  
			    {  
			        glVertex2d(abs(newx - entryList.ptail->vtail->x)/2*cos(2*3.1415926*i/n) + xmin + abs(newx - entryList.ptail->vtail->x)/2,abs(newy - entryList.ptail->vtail->y)/2*sin(2*3.1415926*i/n) + ymin + abs(newy - entryList.ptail->vtail->y)/2);
			    }  
			    glEnd(); 
			}
		    glColor4dv(entryList.ptail->colorBorder);  
		    glBegin(GL_LINE_STRIP & GL_LINE_LOOP);  
		    for(int i=0;i<n;i++)  
		    {  
		        glVertex2d(abs(newx - entryList.ptail->vtail->x)/2*cos(2*3.1415926*i/n) + xmin + abs(newx - entryList.ptail->vtail->x)/2,abs(newy - entryList.ptail->vtail->y)/2*sin(2*3.1415926*i/n) + ymin + abs(newy - entryList.ptail->vtail->y)/2);
		    }  
		    glEnd(); 
			glFlush();
		}
		else if(choosedType == 3){
		    if(entryList.ptail->solid){
		    	glColor4dv(entryList.ptail->colorInside);  
			    glBegin(GL_POLYGON);
			        glVertex2d(entryList.ptail->vtail->x, entryList.ptail->vtail->y);
			        glVertex2d(entryList.ptail->vtail->x, newy);
			        glVertex2d(newx, newy);
			        glVertex2d(newx, entryList.ptail->vtail->y);
			    glEnd(); 
			}
		    glColor4dv(entryList.ptail->colorBorder);  
		    glBegin(GL_LINE_STRIP & GL_LINE_LOOP);  
		        glVertex2d(entryList.ptail->vtail->x, entryList.ptail->vtail->y);
		        glVertex2d(entryList.ptail->vtail->x, newy);
		        glVertex2d(newx, newy);
		        glVertex2d(newx, entryList.ptail->vtail->y);
		    glEnd(); 
			glFlush();
		}
		else if(choosedType == 1){
			if(leftMouse){
				glColor4d(0,0,0,1);
				glBegin(GL_LINE_STRIP);
					glVertex2d(entryList.ptail->vtail->left->x,entryList.ptail->vtail->left->y);
					glVertex2d(entryList.ptail->vtail->x,entryList.ptail->vtail->y);
					glVertex2d(newx,newy);
				glEnd();
				glFlush();
			}
			else{
				glColor4dv(entryList.ptail->colorBorder);
				glBegin(GL_LINES);
					if(entryList.ptail->nvertices!=0){
						glVertex2d(entryList.ptail->vtail->x,entryList.ptail->vtail->y);
						glVertex2d(newx,newy);
					}
				glEnd();
				glFlush();
			}
		}
		else{
			glColor4dv(entryList.ptail->colorBorder);
			glBegin(GL_LINES);
				if(entryList.ptail->nvertices!=0){
					glVertex2d(entryList.ptail->vtail->x,entryList.ptail->vtail->y);
					glVertex2d(newx,newy);
				}
			glEnd();
			glFlush();
		}
	}
}