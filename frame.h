/*
#define toolNo  5
#define specialNo 3
#define sysNo 4
button leftTop,leftBottom,rightTop,rightMiddle,rightBottom;
button toolList[toolNo];
button specialList[specialNo];
button sysList[sysNo];
button line,curve,polygon,square,circle;

button colorFrame,colorSecond,colorCurrent,word;
*/

#define MAINBLOCK 		5		// 主框架数目
#define LEFTTOP 		5		// 左上组按钮数
#define LEFTBOTTOM 		8		// 左下组按钮数
#define RIGHTTOP 		4		// 右上组按钮数
#define RIGHTMIDDLE 	12		// 右中组按钮数
#define RIGHTBOTTOM 	2		// 右下组按钮数
#define SLIP			4		// 滑动按钮组件
button mainBlock[MAINBLOCK];
button leftTop[LEFTTOP];
button leftBottom[LEFTBOTTOM];
button rightTop[RIGHTTOP];
button rightMiddle[RIGHTMIDDLE];
button rightBottom[RIGHTBOTTOM];
button slip[SLIP];

	//板块背景颜色
	double blockColor[4] = {0.8,0.8,0.8,1};
	double blockColor2[4] = {1,1,1,0};

void initFrame(){


	int margin = 4;					// 板块内部距离和边界
	int border = 15;				// 整体边距
	int leftButtonw = 30;			// 左边按钮宽
	int leftButtonh = 30;			// 左边按钮高
	int rightButtonw = 130;			// 右边一般按钮宽
	int rightButtonh = 20;			// 右边一般按钮高
	int leftBottomy = wh - 480;	// 左边整体高度定位
	int rightBottomy = wh - 420;// 右边整体高度定位

/*
	//主板块
	mainBlock[0].setSize(margin * 3 + leftButtonw * 2, margin * 3 + leftButtonh *2); // 左边按钮宽*2 + 组内边界*3；左边按钮高*2 + 组内边界*3；
	mainBlock[0].setPosition(border,leftBottomy + leftButtonh*5 + 6 * margin + margin); // 整体边距；5行按钮，6个模块内边界，1个模块边界

	mainBlock[1].setSize(margin * 3 + leftButtonw * 2, margin * 6 + leftButtonh *5); // 左边按钮宽*2 + 组内边界*3； 左边按钮高*5 + 组内边界 *6；
	mainBlock[1].setPosition(border,leftBottomy); // 整体边距；左边定位
*/
	mainBlock[2].setSize(margin * 2 + rightButtonw, margin * 5 + rightButtonw + rightButtonh * 3);
	mainBlock[2].setPosition(ww - border - margin * 2 - rightButtonw, rightBottomy + margin + margin + margin * 2 + rightButtonh + margin * 7 + rightButtonh *6);

	mainBlock[3].setSize(margin * 2 + rightButtonw, margin * 7 + rightButtonh *6);
	mainBlock[3].setPosition(ww - border - margin * 2 - rightButtonw, rightBottomy + margin + margin * 2 + rightButtonh);

	mainBlock[4].setSize(margin * 2 + rightButtonw, margin * 2 + rightButtonh);
	mainBlock[4].setPosition(ww - border - margin * 2 - rightButtonw, rightBottomy);

	for(int i = 2 ; i< 5;i++) mainBlock[i].setColorInside(blockColor[0],blockColor[1],blockColor[2],blockColor[3]);


	//左上组按钮
	for(int i = 0 ; i < LEFTTOP ; i++){
		leftTop[i].setSize(leftButtonw,leftButtonh);
		leftTop[i].setPosition(border, leftBottomy + LEFTBOTTOM * (margin + leftButtonh) + (LEFTTOP - 1 - i) * (margin + leftButtonh) + margin * 4);
		leftTop[i].setTex(1);
	}
	leftTop[0].setTexImage("img\\open.bmp");
	leftTop[1].setTexImage("img\\create.bmp");
	leftTop[2].setTexImage("img\\set.bmp");
	leftTop[3].setTexImage("img\\save.bmp");
	leftTop[4].setTexImage("img\\saveas.bmp");
		
	//左下组按钮
	for(int i = 0 ; i < LEFTBOTTOM ; i++){
		leftBottom[i].setSize(leftButtonw,leftButtonh);
		leftBottom[i].setPosition(border, leftBottomy + (LEFTBOTTOM - 1 - i) * (margin + leftButtonh));
		leftBottom[i].setTex(1);
	}
	leftBottom[0].setTexImage("img\\line.bmp");
	leftBottom[1].setTexImage("img\\curve.bmp");
	leftBottom[2].setTexImage("img\\polygon.bmp");
	leftBottom[3].setTexImage("img\\square.bmp");
	leftBottom[4].setTexImage("img\\circle.bmp");
	leftBottom[5].setTexImage("img\\delete.bmp");
	leftBottom[6].setTexImage("img\\arrow1.bmp");
	leftBottom[7].setTexImage("img\\arrow2.bmp");

	//右上角组件
	for(int i = 0; i < RIGHTTOP;i++){
		rightTop[i].setSize(rightButtonw, rightButtonh);
		rightTop[i].setPosition(ww - border - margin * 2 - rightButtonw + margin, 
				rightBottomy + margin + margin + margin * 2 + rightButtonh + margin * 7 + rightButtonh *6 + ((RIGHTTOP - 1 - i) + 1) * margin + ((RIGHTTOP - 1 - i)) * rightButtonh);
		rightTop[i].setColorInside(blockColor2[0], blockColor2[1], blockColor2[2], blockColor2[3]);
	}
	rightTop[0].setColorInside(blockColor2[0], blockColor2[1], blockColor2[2], 1);
	rightTop[0].setSize(rightButtonw, rightButtonw);
	rightTop[2].setText("current color:");

	//右中组件
	for(int i = 0; i < RIGHTMIDDLE;i++){
		rightMiddle[i].setSize((rightButtonw - margin) / 2, rightButtonh);
		rightMiddle[i].setPosition(ww - border - margin * 2 - rightButtonw + margin * (i % 2 + 1) + (rightButtonw - margin)/ 2 * (i % 2), 
				rightBottomy + margin + margin * 2 + rightButtonh + ((RIGHTMIDDLE - 1 - i) / 2  + 1) * margin + ((RIGHTMIDDLE - 1 - i) / 2) * rightButtonh);
		
		rightMiddle[i].setColorInside(blockColor2[0], blockColor2[1], blockColor2[2], blockColor2[3]);
	}
	rightMiddle[0].setText("filled:");
	rightMiddle[2].setText("border:");
	rightMiddle[4].setText("texure:");
	rightMiddle[6].setText("trans:");
	rightMiddle[7].setSize((rightButtonw - margin) / 2, 6);
	rightMiddle[7].setPosition(ww - border - margin * 2 - rightButtonw + margin * 2 + (rightButtonw - margin)/ 2, 
			rightBottomy + margin + margin * 2 + rightButtonh + ((RIGHTMIDDLE - 8) / 2  + 1) * margin + ((RIGHTMIDDLE - 8) / 2) * rightButtonh + rightButtonh/2 - 3);
	rightMiddle[7].setColorInside(0.6, 0.6, 0.6, 1);

	//右下组件
	rightBottom[0].setSize((rightButtonw - margin) / 2, rightButtonh);
	rightBottom[0].setPosition(ww - border - margin * 2 - rightButtonw + margin, 
			rightBottomy + ((RIGHTBOTTOM - 2) / 2  + 1) * margin + ((RIGHTBOTTOM - 2) / 2) * rightButtonh);
	rightBottom[0].setColorInside(blockColor2[0], blockColor2[1], blockColor2[2], blockColor2[3]);
	
	rightBottom[1].setSize((rightButtonw - margin) / 2, 6);
	rightBottom[1].setPosition(ww - border - margin * 2 - rightButtonw + margin * 2 + (rightButtonw - margin)/ 2, 
			rightBottomy + ((RIGHTBOTTOM - 2) / 2  + 1) * margin + ((RIGHTBOTTOM - 2) / 2) * rightButtonh + rightButtonh/2 - 3);
	rightBottom[1].setColorInside(0.6, 0.6, 0.6, 1);

	//滑动按钮
	slip[0].setSize(7,7);
	slip[0].setPosition(rightTop[0].x - 3, rightTop[0].y-3);
	slip[1].setSize(5,rightButtonh);
	slip[1].setPosition(rightTop[1].x - 2, rightTop[1].y);
	slip[2].setSize(5,rightButtonh);
	slip[2].setPosition(rightMiddle[7].x - 2, rightMiddle[7].y - rightButtonh / 2 + 2);
	slip[3].setSize(5,rightButtonh);
	slip[3].setPosition(rightBottom[1].x - 2, rightBottom[1].y - rightButtonh / 2 + 2);
	for(int i = 0;i<SLIP;i++){
		slip[i].setColorInside(1, 1, 1, 1);
		slip[i].setBorder(1);
		slip[i].setColorBorder(0,0,0,1);
	}
}


void showColorBlock(){
	glBegin(GL_QUAD_STRIP);
	glColor4d(1,0,0,0);
	glVertex2d(rightTop[0].x, rightTop[0].y);
	glColor4d(1,0,0,1);
	glVertex2d(rightTop[0].x, rightTop[0].y + rightTop[0].h);
	glColor4d(1,1,0,0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6, rightTop[0].y);
	glColor4d(1,1,0,1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6, rightTop[0].y + rightTop[0].h);
	glColor4d(0,1,0,0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3, rightTop[0].y);
	glColor4d(0,1,0,1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3 , rightTop[0].y + rightTop[0].h);
	glColor4d(0,1,1,0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 2, rightTop[0].y);
	glColor4d(0,1,1,1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 2, rightTop[0].y + rightTop[0].h);
	glColor4d(0,0,1,0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3 * 2, rightTop[0].y);
	glColor4d(0,0,1,1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 3 * 2, rightTop[0].y + rightTop[0].h);
	glColor4d(1,0,1,0);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6 * 5, rightTop[0].y);
	glColor4d(1,0,1,1);
	glVertex2d(rightTop[0].x + rightTop[0].w / 6 * 5, rightTop[0].y + rightTop[0].h);
	glColor4d(1,0,0,0);
	glVertex2d(rightTop[0].x + rightTop[0].w, rightTop[0].y);
	glColor4d(1,0,0,1);
	glVertex2d(rightTop[0].x + rightTop[0].w, rightTop[0].y + rightTop[0].h);
	glEnd();
}

void showColorBlock2(){
	glBegin(GL_QUAD_STRIP);
	glColor4d(1,1,1,1);
	glVertex2d(rightTop[1].x, rightTop[1].y);
	glColor4d(1,1,1,1);
	glVertex2d(rightTop[1].x, rightTop[1].y + rightTop[1].h);
	glColor4dv(rightTop[1].colorInside);
	glVertex2d(rightTop[1].x + rightTop[1].w / 2, rightTop[1].y);
	glColor4dv(rightTop[1].colorInside);
	glVertex2d(rightTop[1].x + rightTop[1].w / 2, rightTop[1].y + rightTop[1].h);
	glColor4d(0,0,0,1);
	glVertex2d(rightTop[1].x + rightTop[1].w, rightTop[1].y);
	glColor4d(0,0,0,1);
	glVertex2d(rightTop[1].x + rightTop[1].w, rightTop[1].y + rightTop[1].h);
	glEnd();
}


void showFrame(){
//	showChoosed();
	for(int i = 2 ; i< 5;i++) mainBlock[i].show();

	for(int i  = 0 ; i < LEFTTOP; i++) leftTop[i].show();
	for(int i  = 0 ; i < LEFTBOTTOM; i++) leftBottom[i].show();
	for(int i  = 0 ; i < RIGHTTOP; i++) rightTop[i].show();
	for(int i  = 0 ; i < RIGHTMIDDLE; i++) rightMiddle[i].show();
	for(int i  = 0 ; i < RIGHTBOTTOM; i++) rightBottom[i].show();
	showColorBlock();
	showColorBlock2();
	for(int i  = 0 ; i < SLIP; i++) slip[i].show();
}

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
}

int drawing = 0;
int choosedType = 0;
int slipType = 0;
int picking = 0;
int slipping = 0;
//检查鼠标按键
int checkPressButton(int x, int y){
	for(int i = 0 ;i < 5;i++){
		if(leftBottom[i].mouseIn){
			choosedType = i;
			picking = 0;
			slipping = 0;
			return 1;
		}
	}
	if(leftBottom[6].mouseIn){
		picking = 1;
		drawing = 0;
		return 1;
	}
	for(int i = 0 ; i < SLIP; i++){
		if(slip[i].mouseIn){
			slipType = i;
			slipping = 1;
			picking = 0;
			drawing = 0;
			return 1;
		}
	}
}

int checkPressEntry(int x, int y){
	printf("checking picking\n");
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
		printf ("hits = %d\n", hits);
		ptr = (GLuint *) selectBuff;
		minZ = 0xffffffff;
		for (int i = 0; i < hits; i++) {
			printf("%d %d %d %d\n",*(ptr),*(ptr+1),*(ptr+2),*(ptr+3));
			if (*(ptr+1) < minZ) {
				minZ = *(ptr+1);
				names = *(ptr+3);
			}
			ptr += 4;
		}
    }
	entry_node * temp = entryList.phead->next;
	while(temp!=NULL){
		if(temp->insideNameId == names || temp->borderNameId == names){
			printf("polygon %d picked\n", names);
			temp->picked = 1;
		}
		else temp->picked = 0;
		temp = temp->next;
	}
}