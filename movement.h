char * opened_file = NULL;

int leftMouse = 0;
int oldx,oldy;
int newx,newy;

int drawing = 0;
int choosedType = 0;
int slipType = 0;
int picking = 0;
int slipping = 0;
int changingpoints = 0;
int movingpoint = 0;

void saveEntry(int);
void loadEntry();
void newFile();
void newColor();
void clearPick();
void clearblick();
void refreshStatus();

//检查鼠标进入按钮
void checkInButton(int x, int y){
	for(int i = 0 ; i < LEFTTOP ;i++){
		if(x>leftTop[i].x && x<leftTop[i].x+leftTop[i].w && y>leftTop[i].y && y<leftTop[i].y+leftTop[i].h){
			leftTop[i].mouseHover();
			leftTop[i].mouseIn = 1;
			glFlush();
		}
		else{
			if(leftTop[i].mouseIn){
				glutPostRedisplay();
				leftTop[i].mouseIn = 0;
			}
		}
	}
	for(int i = 0 ; i < LEFTBOTTOM ;i++){
		if(x>leftBottom[i].x && x<leftBottom[i].x+leftBottom[i].w && y>leftBottom[i].y && y<leftBottom[i].y+leftBottom[i].h){
			leftBottom[i].mouseHover();
			leftBottom[i].mouseIn = 1;
			glFlush();
		}
		else{
			if(leftBottom[i].mouseIn){
				glutPostRedisplay();
				leftBottom[i].mouseIn = 0;
			}
		}
	}
	for(int i = 0 ; i < SLIP; i++){
		if(x>slip[i].x && x<slip[i].x+slip[i].w && y>slip[i].y && y<slip[i].y+slip[i].h){
			slip[i].mouseHover();
			slip[i].mouseIn = 1;
			glFlush();
		}
		else{
			if(slip[i].mouseIn){
				glutPostRedisplay();
				slip[i].mouseIn = 0;
			}
		}
	}

	if(x>rightTop[0].x && x<rightTop[0].x+rightTop[0].w && y>rightTop[0].y && y<rightTop[0].y+rightTop[0].h){
		rightTop[0].mouseHover();
		rightTop[0].mouseIn = 1;
		glFlush();
	}
	else{
		if(rightTop[0].mouseIn){
			glutPostRedisplay();
			rightTop[0].mouseIn = 0;
		}
	}
	if(x>rightTop[1].x && x<rightTop[1].x+rightTop[1].w && y>rightTop[1].y && y<rightTop[1].y+rightTop[1].h){
		rightTop[1].mouseHover();
		rightTop[1].mouseIn = 1;
		glFlush();
	}
	else{
		if(rightTop[1].mouseIn){
			glutPostRedisplay();
			rightTop[1].mouseIn = 0;
		}
	}
	if(x>rightMiddle[7].x && x<rightMiddle[7].x+rightMiddle[7].w && y>rightMiddle[7].y && y<rightMiddle[7].y+rightMiddle[7].h){
		rightMiddle[7].mouseHover();
		rightMiddle[7].mouseIn = 1;
		glFlush();
	}
	else{
		if(rightMiddle[7].mouseIn){
			glutPostRedisplay();
			rightMiddle[7].mouseIn = 0;
		}
	}
	if(x>rightBottom[1].x && x<rightBottom[1].x+rightBottom[1].w && y>rightBottom[1].y && y<rightBottom[1].y+rightBottom[1].h){
		rightBottom[1].mouseHover();
		rightBottom[1].mouseIn = 1;
		glFlush();
	}
	else{
		if(rightBottom[1].mouseIn){
			glutPostRedisplay();
			rightBottom[1].mouseIn = 0;
		}
	}
}

//检查鼠标按键
int checkPressButton(int x, int y){
	for(int i = 0 ;i < 5;i++){
		if(leftBottom[i].mouseIn){
			choosedType = i;
			slipping = 0;
			clearPick();
			clearblick();
			return 1;
		}
	}
	if(leftBottom[5].mouseIn){
		drawing = 0;
		
		entry_node * temp = entryList.phead->next;
		int i  = 0;
		while(temp!=NULL){
			if(temp->picked) break;
			temp = temp->next;
			i++;
		}
		if(picking) entryList.remove(i);
		glutPostRedisplay();
		return 1;
	}
	if(leftBottom[6].mouseIn){
		clearblick();
		picking = 1;
		drawing = 0;
		return 1;
	}
	if(leftBottom[7].mouseIn){
		clearPick();
		movingpoint = 1;
		drawing = 0;
		return 1;
	}
	if(rightTop[0].mouseIn){
		slipType = 0;
		slipping = 1;
		drawing = 0;
		return 1;
	}
	if(rightTop[1].mouseIn){
		slipType = 1;
		slipping = 1;
		drawing = 0;
		return 1;
	}
	if(rightMiddle[7].mouseIn){
		slipType = 2;
		slipping = 1;
		drawing = 0;
		return 1;
	}
	if(rightBottom[1].mouseIn){
		slipType = 3;
		slipping = 1;
		drawing = 0;
		return 1;
	}
	for(int i = 0 ; i < LEFTTOP;i++){
		if( leftTop[i].mouseIn){
			slipping = 0;
			drawing = 0;
			switch(i){
				case 0:	loadEntry();break;
				case 1:	newFile();break;
				case 2:	newColor();break;
				case 3:	saveEntry(1);break;
				case 4:	saveEntry(0);break;
			}
			return 1;
		}
	}
}

void clearPick(){
		picking = 0;
		entry_node * temp = entryList.phead->next;
		while(temp!=NULL){
			if(temp->picked == 1){
				temp->picked = 0;
				break;
			}
			temp = temp->next;
		}
		glutPostRedisplay();
}

void clearblick(){
		movingpoint = 0;
		entry_node * temp = entryList.phead->next;
		while(temp!=NULL){
			if(temp->blick == 1){
				temp->blick = 0;
				temp->refreshmaxmin();
				break;
			}
			temp = temp->next;
		}
		glutPostRedisplay();
}

void checkPressEntry(int x, int y){
	GLuint selectBuff[1000]={0};//创建一个保存选择结果的数组    
	GLint hits, viewport[4];      

	glGetIntegerv(GL_VIEWPORT, viewport); //获得viewport    
	glSelectBuffer(2000, selectBuff); //告诉OpenGL初始化  selectbuffer    
	glRenderMode(GL_SELECT);    //进入选择模式    

	glInitNames();  //初始化名字栈    
	glPushName(0);  //在名字栈中放入一个初始化名字，这里为‘0’    

	glMatrixMode(GL_PROJECTION);    //进入投影阶段准备拾取    
	glPushMatrix();     //保存以前的投影矩阵    
	glLoadIdentity();   //载入单位矩阵    


	gluPickMatrix( x,y,4,4,	viewport);
	gluOrtho2D(0.0,ww,0.0,wh);

	glInitNames();

	entryList.showAll();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
  

    hits = glRenderMode(GL_RENDER); // 从选择模式返回正常模式,该函数返回选择到对象的个数    
    GLuint names = 0;
    if(hits > 0){
		GLuint *ptr, minZ;
		ptr = (GLuint *) selectBuff;
		minZ = 0xffffffff;
		for (int i = 0; i < hits; i++) {
			if (*(ptr+1) <= minZ && *(ptr+3)!=0) {
				minZ = *(ptr+1);
				names = *(ptr+3);
			}
			ptr += 4;
		}
    }
    if(names == 1){
    	changingpoints = 1;
    	return;
    }
	entry_node * temp = entryList.phead->next;
	while(temp!=NULL){
		if(temp->insideNameId == names || temp->borderNameId == names){
			if(picking) temp->picked = 1;
			else if(movingpoint) temp->blick = 1;
			refreshStatus();
		}
		else{
			if(picking) temp->picked = 0;
			else if(movingpoint) temp->blick = 0;
		}
		temp = temp->next;
	}
	glutPostRedisplay();
}

void saveEntry(int s = 0){
	char *filename = NULL;
	if(s == 0 || opened_file == NULL){
		OPENFILENAME ofn;
		TCHAR szOpenFileNames[80*MAX_PATH];
		TCHAR szPath[MAX_PATH];
		ZeroMemory( &ofn, sizeof(ofn) );
		ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFile = szOpenFileNames;
		ofn.nMaxFile = sizeof(szOpenFileNames);
		//ofn.lpstrFile[0] = '/0';

		char Filter[] = "mytype Files(*.mytype)\0*.mytype\0All Files(*.*)\0*.*\0\0";
		ofn.lpstrFilter = TEXT(Filter);
		//if( GetOpenFileName( &ofn ) )
		if(GetSaveFileName( &ofn ))
		{ 
			lstrcpyn(szPath, szOpenFileNames, ofn.nFileOffset );
			filename = szOpenFileNames;
		}
	}
	else filename = opened_file;

	FILE *fp;
	fp =fopen(filename, "w");

  	fwrite(&(entryList.size), sizeof(int), 1, fp);

	int type;
	int no_of_vertices;
	int  status_int[12];
	double  status_double[20];
	double  *vertices_list;
	char *tex;
	char *text;
	entry_node * temp = entryList.phead->next;
	while(temp != NULL){
		vertices_list = new double[temp->nvertices*3 * 2];

		temp->save_status(type, no_of_vertices, vertices_list, status_int, status_double, tex, text);
  		fwrite(&type, sizeof(type), 1, fp);
  		fwrite(&no_of_vertices, sizeof(no_of_vertices), 1, fp);  
  		fwrite(vertices_list, sizeof(vertices_list[0]), temp->nvertices*3 * 2, fp);
  		fwrite(status_int, sizeof(status_int[0]), 12, fp);
  		fwrite(status_double, sizeof(status_double[0]), 20, fp);
  		if(tex == NULL){
  			fputs("n\n\0",fp);
  		}
  		else fputs( tex, fp );
  		if(text == NULL){
  			fputs("n\n\0",fp);
  		}
  		else fputs( text, fp );
  		temp = temp->next;
	}
	fclose(fp);
}

void loadEntry(){
	OPENFILENAME ofn;
	TCHAR szOpenFileNames[80*MAX_PATH];
	TCHAR szPath[MAX_PATH];
	ZeroMemory( &ofn, sizeof(ofn) );
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szOpenFileNames;
	ofn.nMaxFile = sizeof(szOpenFileNames);
	//ofn.lpstrFile[0] = '/0';

	char Filter[] = "mytype Files(*.mytype)\0*.mytype\0All Files(*.*)\0*.*\0\0";
	ofn.lpstrFilter = TEXT(Filter);
	if( GetOpenFileName( &ofn ) )
	{ 
		lstrcpyn(szPath, szOpenFileNames, ofn.nFileOffset );
		opened_file = new char[1000];
		strcpy(opened_file, szOpenFileNames);
	}

	newFile();

	FILE *fp;
	fp =fopen(szOpenFileNames, "r");

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
	while(index<n && !feof(fp)){
		entryList.newOne();
		entry_node * temp = entryList.ptail;
  		fread(&type, sizeof(type), 1, fp);
  		fread(&no_of_vertices, sizeof(no_of_vertices), 1, fp); 
		vertices_list = new double[no_of_vertices*3 * 2]; 
  		fread(vertices_list, sizeof(vertices_list[0]), no_of_vertices*3 * 2, fp);
  		fread(status_int, sizeof(status_int[0]), 12, fp);
  		fread(status_double, sizeof(status_double[0]), 20, fp);
  		fgets( tex, 1000,fp );
  		fgets( text, 1000,fp );

		temp->load_status(type, no_of_vertices, vertices_list, status_int, status_double, tex, text);

		index++;
		delete vertices_list;
	}
	delete tex;
	delete text;
	fclose(fp);
}

void newFile(){
	if(entryList.size != 0){
		int check = MessageBox(NULL, "save current file ?","warning", MB_YESNOCANCEL); 
		if(check == IDYES){
			if(opened_file == NULL) saveEntry(0);
			else saveEntry(1);
			entryList.clearAll();
		}
		else if(check == IDNO) entryList.clearAll();
		else if(check == IDCANCEL) return;
	}
	if(opened_file!=NULL)delete opened_file;
	glutPostRedisplay();
}

void newColor(){
	HWND hdlg;

	hdlg = GetActiveWindow();
	COLORREF rgbLineColor; 
	COLORREF retColor = RGB( 255,0,0);
 	COLORREF cusColor[16];
	CHOOSECOLOR stChooseColor=
	{
		sizeof(CHOOSECOLOR),
		hdlg,
		NULL,
        retColor,
        cusColor,
        CC_RGBINIT|CC_FULLOPEN | CC_ENABLEHOOK | CC_ANYCOLOR,
        0 ,
        NULL ,
        NULL
    };
    if (ChooseColor(&stChooseColor))
	{
	    rgbLineColor = stChooseColor.rgbResult;
	}
}


//鼠标按键事件
void myMouse(int button, int state, int x, int y){
	y = wh-y;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(checkPressButton(x,y) == 1){
			return;
		}
		if(drawing){
			entryList.ptail->addPoint(x,y);
			refreshStatus();
		}
		else if(picking){
			oldx = x;
			oldy = y;
			checkPressEntry(x,y);
		}
		else if(movingpoint){
			oldx = x;
			oldy = y;
			checkPressEntry(x,y);
		}
		else{
			drawing = 1;
			entryList.newOne();
			entryList.ptail->setType(choosedType);
			entryList.ptail->addPoint(x,y);
			entryList.ptail->setColorInside(rightTop[3].colorInside[0],rightTop[3].colorInside[1],rightTop[3].colorInside[2]);
			if(choosedType == 3) entryList.ptail->addPoint(x,y);
			refreshStatus();
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
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && slipping == 1){
		slipping = 0;
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && changingpoints == 1){
		changingpoints = 0;
	}
}

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
			refreshStatus();
			glutPostRedisplay();
		}
		else if(entryList.ptail->nvertices!=0){
			newx = x;
			newy = y;
			refreshStatus();
			glutPostRedisplay();
		}
	}
	else if(picking){
		entry_node * temp = entryList.phead->next;
		while(temp!=NULL){
			if(temp->picked == 1){
				if(changingpoints) temp->changePoints(oldx,oldy,x,y);
				else temp->movePoints(oldx,oldy,x,y);
				oldx = x;
				oldy = y;

				break;
			}
			temp = temp->next;
		}
		refreshStatus();
		glutPostRedisplay();
	}
	else if(movingpoint){
		entry_node * temp = entryList.phead->next;
		while(temp!=NULL){
			if(temp->blick == 1){
				temp->movePoint(oldx,oldy,x,y);
				oldx = x;
				oldy = y;

				break;
			}
			temp = temp->next;
		}
		refreshStatus();
		glutPostRedisplay();
	}
	else if(slipping){
		int i  = 0;
		if(rightTop[0].mouseIn) i = 0;
		if(rightTop[1].mouseIn) i = 1;
		if(rightMiddle[7].mouseIn) i = 2;
		if(rightBottom[1].mouseIn) i = 3;

		//更新位置
		if(i == 0) slip[i].setPosition((x>=rightTop[0].x && x <=rightTop[0].x+ rightTop[0].w?x-3:slip[i].x),(y>=rightTop[0].y && y <=rightTop[0].y+rightTop[0].h?y-3:slip[i].y));
		else if(i == 1 && x>=rightTop[1].x && x <=rightTop[1].x+ rightTop[1].w) slip[i].setPosition(x-2,slip[i].y);
		else if(i == 2 && x>=rightMiddle[3].x  && x <=rightMiddle[3].x+ rightMiddle[3].w) slip[i].setPosition(x-2,slip[i].y);
		else if(i == 3 && x>=rightBottom[1].x  && x <=rightBottom[1].x+ rightBottom[1].w) slip[i].setPosition(x-2,slip[i].y);

		//更新相联板块
		if(i == 0){
			double r = 0;
			double g = 0;
			double b = 0;
			double dx = (double)(x - rightTop[0].x)/(double)rightTop[0].w;
			double dy = -(double)(2*y - 2* rightTop[0].y - rightTop[0].h)/(double)rightTop[0].h;
			if(dx>1) dx = 1;
			else if(dx<0) dx = 0;
			if(dy>1) dy = 1;
			else if(dy<-1) dy = -1;
			if(dx < 1.0/6.0){
				r = 1;
				g = dx * 6;
			}
			else if (dx < 2.0/6.0){
				r = 1 - (dx-1.0/6.0) *6;
				g = 1;
			}
			else if (dx < 3.0/6.0){
				g = 1;
				b = (dx-2.0/6.0) *6;
			}
			else if (dx < 4.0/6.0){
				g = 1 - (dx-3.0/6.0) *6;
				b = 1;
			}
			else if (dx < 5.0/6.0){
				b = 1;
				r = (dx-4.0/6.0) *6;
			}
			else{
				b = 1 - (dx-5.0/6.0) *6;
				r = 1;
			}
			if(dy < 0){
				r += r * dy;
				g += g * dy;
				b += b * dy;
			}
			else{
				r += (1-r) * dy;
				g += (1-g) * dy;
				b += (1-b) * dy;
			}
			rightTop[1].setColorInside(r,g,b);
			rightTop[3].setColorInside(r,g,b);
			slip[1].setPosition(rightTop[1].x + rightTop[1].w/2 - 2, rightTop[1].y);
		}
		if(i == 1){
			double dx = -(double)(2* x - 2*rightTop[1].x - rightTop[1].w)/(double)rightTop[1].w;
			double r,g,b;
			r = rightTop[1].colorInside[0];
			g = rightTop[1].colorInside[1];
			b = rightTop[1].colorInside[2];
			if(dx < 0){
				r += r * dx;
				g += g * dx;
				b += b * dx;
			}
			else{
				r += (1-r) * dx;
				g += (1-g) * dx;
				b += (1-b) * dx;
			}
			rightTop[3].setColorInside(r,g,b);
		}

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


void refreshStatus(){
	entry_node * temp = entryList.ptail;

	if(temp == NULL || temp->vhead->next == NULL) return;
	if(drawing != 1){
		temp = entryList.phead->next;
		while(temp!=NULL){
			if(temp->picked || temp->blick) break;
			temp=temp->next;
		}
	}
	if(temp == NULL) return;
	char xstr[10] = {'x',':'};
	char ystr[10] = {'y',':'};
	char wstr[10] = {'w',':'};
	char hstr[10] = {'h',':'};
	itoa((int)temp->xmin,&xstr[2],10);
	itoa((int)temp->ymin,&ystr[2],10);
	itoa((int)temp->w,&wstr[2],10);
	itoa((int)temp->h,&hstr[2],10);

	rightMiddle[1].setColorInside(temp->colorInside[0],temp->colorInside[1],temp->colorInside[2]);
	rightMiddle[3].setColorInside(temp->colorBorder[0],temp->colorBorder[1],temp->colorBorder[2]);
	rightMiddle[8].setText(xstr);
	rightMiddle[9].setText(ystr);
	rightMiddle[10].setText(wstr);
	rightMiddle[11].setText(hstr);
}