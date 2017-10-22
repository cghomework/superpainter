//#define BMP_Header_Length 54  //图像数据在内存块中的偏移量  

struct vertice_node{
	double x,y;
	vertice_node * next;
	vertice_node * left;
	vertice_node * right;
	vertice_node(){
		right = left = next = NULL;
	}
};
class entry_node{
		enum type{
			LINE,
			CURVE,
			POLYGON,
			SQUARE,
			CIRCLE
		}_type;
		void showTex(){
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			glPushMatrix();
			glPushName(insideNameId);
			glBindTexture(GL_TEXTURE_2D, _tex);  
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f);
				glVertex2f(x,y);
				glTexCoord2f(1.0f, 0.0f);
				glVertex2f(x+w,y);
				glTexCoord2f(1.0f, 1.0f);
				glVertex2f(x+w,y+h);
				glTexCoord2f(0.0f, 1.0f);
				glVertex2f(x,y+h);
			glEnd();
			glPopName();
			glPopMatrix();
			glPopAttrib();
		}
		void showText(){
			setColor(colorText);
			glRasterPos2d(x+5, y+h-18); 
			for(char *c=_text; *c != '\0'; c++) {  
			    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);  
			}  
		}
		void showBorder(){
			glPushName(borderNameId);
			setColor(colorBorder);
			glLineWidth(width);
			glBegin(GL_LINE_STRIP & GL_LINE_LOOP);
				vertice_node *temp2 = vhead;
				while(temp2->next!=NULL){
					glVertex2d(temp2->next->x,temp2->next->y);
					temp2 = temp2->next;
				}
				if(_type == POLYGON) glVertex2d(vhead->next->x,vhead->next->y);
			glEnd();
			glPopName();
		}
		void showLine(){
			glPushName(borderNameId);
			setColor(colorBorder);
			glLineWidth(width);
			glBegin(GL_LINE_STRIP);
				vertice_node *temp2 = vhead;
				while(temp2->next!=NULL){
					glVertex2d(temp2->next->x,temp2->next->y);
					temp2 = temp2->next;
				}
				if(_type == POLYGON) glVertex2d(vhead->next->x,vhead->next->y);
			glEnd();
			glPopName();
		}
		void showPoint(){
			glPushName(borderNameId);
			setColor(colorBorder);
			glBegin(GL_POINTS);
				glVertex2d(vhead->next->x,vhead->next->y);
			glEnd();
			glPopName();
		}
		void showInside(){
			glPushName(insideNameId);
			setColor(colorInside);
			glBegin(GL_POLYGON);
				vertice_node *temp2 = vhead;
				while(temp2->next!=NULL){
					glVertex2d(temp2->next->x,temp2->next->y);
					temp2 = temp2->next;
				}
			glEnd();
			glPopName();
		}
		void showCircle(){
			if(solid){
				glPushName(insideNameId);
			    setColor(colorInside); 
			    glBegin(GL_POLYGON);
			    	vertice_node * temp = vhead->next;
			    	while(temp->next != NULL){
			    		double p1x = temp->x;
			    		double p1y = temp->y;
			    		double p2x = temp->right->x;
			    		double p2y = temp->right->y;
			    		double p3x = temp->next->left->x;
			    		double p3y = temp->next->left->y;
			    		double p4x = temp->next->x;
			    		double p4y = temp->next->y;
				    	for(double t = 0.0; t <= 1.01; t += 0.01){
						    double a1 = pow((1-t),3);  
						    double a2 = pow((1-t),2)*3*t;  
						    double a3 = 3*t*t*(1-t);  
						    double a4 = t*t*t;
						    glVertex2d(p1x*a1 + p2x*a2 + p3x*a3 + p4x*a4, p1y*a1 + p2y*a2 + p3y*a3 + p4y*a4);
				    	}
				    	temp = temp->next;
			    	}
		    		double p1x = temp->x;
		    		double p1y = temp->y;
		    		double p2x = temp->right->x;
		    		double p2y = temp->right->y;
		    		double p3x = vhead->next->left->x;
		    		double p3y = vhead->next->left->y;
		    		double p4x = vhead->next->x;
		    		double p4y = vhead->next->y;
			    	for(double t = 0.0; t <= 1.01; t += 0.01){
					    double a1 = pow((1-t),3);  
					    double a2 = pow((1-t),2)*3*t;  
					    double a3 = 3*t*t*(1-t);  
					    double a4 = t*t*t;
					    glVertex2d(p1x*a1 + p2x*a2 + p3x*a3 + p4x*a4, p1y*a1 + p2y*a2 + p3y*a3 + p4y*a4);
			    	}
			    glEnd();
				glPopName();
			}
			if(border){
				glPushName(borderNameId);
			    setColor(colorBorder);  
				glLineWidth(width);
			    glBegin(GL_LINE_STRIP);
			    	vertice_node * temp = vhead->next;
			    	while(temp->next != NULL){
			    		double p1x = temp->x;
			    		double p1y = temp->y;
			    		double p2x = temp->right->x;
			    		double p2y = temp->right->y;
			    		double p3x = temp->next->left->x;
			    		double p3y = temp->next->left->y;
			    		double p4x = temp->next->x;
			    		double p4y = temp->next->y;
				    	for(double t = 0.0; t <= 1.01; t += 0.01){
						    double a1 = pow((1-t),3);  
						    double a2 = pow((1-t),2)*3*t;  
						    double a3 = 3*t*t*(1-t);  
						    double a4 = t*t*t;
						    glVertex2d(p1x*a1 + p2x*a2 + p3x*a3 + p4x*a4, p1y*a1 + p2y*a2 + p3y*a3 + p4y*a4);
				    	}
				    	temp = temp->next;
			    	}
		    		double p1x = temp->x;
		    		double p1y = temp->y;
		    		double p2x = temp->right->x;
		    		double p2y = temp->right->y;
		    		double p3x = vhead->next->left->x;
		    		double p3y = vhead->next->left->y;
		    		double p4x = vhead->next->x;
		    		double p4y = vhead->next->y;
			    	for(double t = 0.0; t <= 1.01; t += 0.01){
					    double a1 = pow((1-t),3);  
					    double a2 = pow((1-t),2)*3*t;  
					    double a3 = 3*t*t*(1-t);  
					    double a4 = t*t*t;
					    glVertex2d(p1x*a1 + p2x*a2 + p3x*a3 + p4x*a4, p1y*a1 + p2y*a2 + p3y*a3 + p4y*a4);
			    	}
			    glEnd();
				glPopName();
			}
		}
		void showCurve(){
		    if(border){
				glPushName(borderNameId);
			    setColor(colorBorder);  
				glLineWidth(width);
			    glBegin(GL_LINE_STRIP);
			    	vertice_node * temp = vhead->next;
			    	while(temp->next != NULL){
			    		double p1x = temp->x;
			    		double p1y = temp->y;
			    		double p2x = temp->right->x;
			    		double p2y = temp->right->y;
			    		double p3x = temp->next->left->x;
			    		double p3y = temp->next->left->y;
			    		double p4x = temp->next->x;
			    		double p4y = temp->next->y;
				    	for(double t = 0.0; t <= 1.01; t += 0.01){
						    double a1 = pow((1-t),3);  
						    double a2 = pow((1-t),2)*3*t;  
						    double a3 = 3*t*t*(1-t);  
						    double a4 = t*t*t;
						    glVertex2d(p1x*a1 + p2x*a2 + p3x*a3 + p4x*a4, p1y*a1 + p2y*a2 + p3y*a3 + p4y*a4);
				    	}
				    	temp = temp->next;
			    	}
			    glEnd();
				glPopName();
			}
		}
		// 函数power_of_two用于判断一个整数是不是2的整数次幂    
		int power_of_two(int n){    
		    if( n <= 0 )    
		        return 0;    
		    return (n & (n-1)) == 0;    
		}
		void setColor(double *color){
			glColor4dv(color);
		}	
	public:
		int xmin,xmax,ymin,ymax;
		int x,y;
		int w,h;
		int insideNameId;
		int borderNameId;
		double colorInside[4];
		double colorBorder[4];
		double colorHoverInside[4];
		double colorHoverBorder[4];
		double colorText[4];
		int solid;
		int border;
		int width;
		int mouseIn; 
		int picked;
		GLuint _tex;
		int tex;
		char *_text;
		int nvertices;
		entry_node * next;
		vertice_node * vhead;
		vertice_node * vtail;
		entry_node(int _x = 0, int _y = 0, int _w = 125, int _h = 25):
			_type(POLYGON),nvertices(0),next(NULL),x(_x),y(_y),w(_w),h(_h),solid(1),border(1),mouseIn(0),picked(0),tex(0),_text(NULL),width(2),insideNameId(0),borderNameId(0){
			for(int i = 0 ; i < 3;i++){
				colorInside[i] = 1.0;
				colorBorder[i] = 0.0;
				colorHoverBorder[i] = 0.5;
				colorHoverInside[i] = 1.0;
				colorText[i] = 0.0;
			}
			colorBorder[3] = 1.0;
			colorInside[3] = 1.0;
			colorHoverBorder[3] = 1.0;
			colorHoverInside[3] = 1.0;
			colorText[3] = 1.0;
			vhead = new vertice_node;
			vtail = vhead;
			xmin = ww;
			xmax = 0;
			ymin = wh;
			ymax = 0;
		}
		void setPosition(int _x, int _y){
			x = _x;
			y = _y;
		}
		void setSize(int _w, int _h){
			w = _w;
			h = _h;
		}
		void setType(int x){
			switch(x){
				case 0:_type = LINE;break;
				case 1:_type = CURVE;break;
				case 2:_type = POLYGON;break;
				case 3:_type = SQUARE;break;
				case 4:_type = CIRCLE;break;
			}
		}
		void setColorInside(double c1, double c2, double c3, double c4 = 1.0){
			colorInside[0] = c1;
			colorInside[1] = c2;
			colorInside[2] = c3;
			colorInside[3] = c4;
		}
		void setColorBorder(double c1, double c2, double c3, double c4 = 1.0){
			colorBorder[0] = c1;
			colorBorder[1] = c2;
			colorBorder[2] = c3;
			colorBorder[3] = c4;
		}
		void setText(const char *text){
			if(text == NULL){
				_text = NULL;
		    	return;
		    }
		    _text = new char[strlen(text)];
		    strcpy(_text,text);
		}
		void setBorder(int x = 1){
			border = x;
		}
		void setSolid(int x = 1){
			solid = x;
		}
		void setTex(int x = 0){
			tex = x;
		}
		void show(){
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			glPushMatrix();
			if(nvertices == 1 && _type != CIRCLE) showPoint();
			else if(_type == CIRCLE) showCircle();
			else if(_type == CURVE) showCurve();
			else{
				if(solid && (_type == POLYGON ||  _type == SQUARE)){
					if(tex) showTex();
					else showInside();
					if(border){
						showBorder();
					}
				}
				else showLine();
			}
			if(_text != NULL) showText();
			glPopMatrix();
			glPopAttrib();
		}
		void mouseHover(){
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			setColor(colorHoverInside);
			glBegin(GL_POLYGON);
				glVertex2f(x,y);
				glVertex2f(x+w,y);
				glVertex2f(x+w,y+h);
				glVertex2f(x,y+h);
			glEnd();

			setColor(colorHoverBorder);
			glBegin(GL_LINE_STRIP & GL_LINE_LOOP);
				glVertex2f(x,y);
				glVertex2f(x+w,y);
				glVertex2f(x+w,y+h);
				glVertex2f(x,y+h);
			glEnd();
			glPopAttrib();
		}
		void mouseUnhover(){
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			setColor(colorInside);
			glBegin(GL_POLYGON);
				glVertex2f(x,y);
				glVertex2f(x+w,y);
				glVertex2f(x+w,y+h);
				glVertex2f(x,y+h);
			glEnd();
			setColor(colorBorder);
			glBegin(GL_LINE_STRIP & GL_LINE_LOOP);
				glVertex2f(x,y);
				glVertex2f(x+w,y);
				glVertex2f(x+w,y+h);
				glVertex2f(x,y+h);
			glEnd();
			glPopAttrib();
		}
		int setTexImage(const char* file_name){
			GLint width, height, total_bytes;    
		    GLubyte* pixels = 0;    
		    GLuint last_texture_ID=0, texture_ID = 0;    
		  
		    // 打开文件，如果失败，返回    
		    FILE* pFile = fopen(file_name, "rb");    
		    if( pFile == 0 )    
		        return 2;    
		  
		    // 读取文件中图象的宽度和高度    
		    fseek(pFile, 0x0012, SEEK_SET);    
		    fread(&width, 4, 1, pFile);    
		    fread(&height, 4, 1, pFile);    
		    fseek(pFile, BMP_Header_Length, SEEK_SET);    
		  
		    // 计算每行像素所占字节数，并根据此数据计算总像素字节数    
		    {    
		        GLint line_bytes = width * 3;    
		        while( line_bytes % 4 != 0 )    
		            ++line_bytes;    
		        total_bytes = line_bytes * height;    
		    }    
		  
		    // 根据总像素字节数分配内存    
		    pixels = (GLubyte*)malloc(total_bytes);    
		    if( pixels == 0 )    
		    {    
		        fclose(pFile);    
		        return 3;    
		    }    
		  
		    // 读取像素数据    
		    if( fread(pixels, total_bytes, 1, pFile) <= 0 )    
		    {    
		        free(pixels);    
		        fclose(pFile);    
		        return 4;    
		    }    
		  
		    // 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放    
		    // 若图像宽高超过了OpenGL规定的最大值，也缩放    
		    {    
		        GLint max;    
		        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);    
		        if( !power_of_two(width)    
		            || !power_of_two(height)    
		            || width > max    
		            || height > max )    
		        {    
		            const GLint new_width = 256;    
		            const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形    
		            GLint new_line_bytes, new_total_bytes;    
		            GLubyte* new_pixels = 0;    
		  
		            // 计算每行需要的字节数和总字节数    
		            new_line_bytes = new_width * 3;    
		            while( new_line_bytes % 4 != 0 )    
		                ++new_line_bytes;    
		            new_total_bytes = new_line_bytes * new_height;    
		  
		            // 分配内存    
		            new_pixels = (GLubyte*)malloc(new_total_bytes);    
		            if( new_pixels == 0 )    
		            {    
		                free(pixels);    
		                fclose(pFile);    
		                return 5;    
		            }    
		  
		            // 进行像素缩放    
		            gluScaleImage(GL_RGB,    
		                width, height, GL_UNSIGNED_BYTE, pixels,    
		                new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);    
		  
		            // 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height    
		            free(pixels);    
		            pixels = new_pixels;    
		            width = new_width;    
		            height = new_height;    
		        }    
		    }    
		  
		    // 分配一个新的纹理编号    
		    glGenTextures(1, &texture_ID);    
		    if( texture_ID == 0 )    
		    {    
		        free(pixels);    
		        fclose(pFile);    
		        return 6;    
		    }    
		  
		    // 绑定新的纹理，载入纹理并设置纹理参数    
		    // 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复    
		    GLint lastTextureID=last_texture_ID;    
		    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);    
		    glBindTexture(GL_TEXTURE_2D, texture_ID);    
		    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); */   
		  
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);    
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);   
		  
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    
		    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);    
		  
		    /* glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,   
		    GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels); */   
		  
		    gluBuild2DMipmaps(GL_TEXTURE_2D,3,width,height,0x80E0,GL_UNSIGNED_BYTE,pixels);  
		  
		    glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定    
		    free(pixels);    
		    _tex = texture_ID;
		    return 1;
		}
		void addPoint(double _x, double _y){
			vertice_node * temp = new vertice_node;
			vertice_node * tempLeft = new vertice_node;
			vertice_node * tempRight = new vertice_node;
			temp->x = _x;
			temp->y = _y;
			tempLeft->x = _x;
			tempLeft->y = _y;
			tempRight->x = _x;
			tempRight->y = _y;
			temp->left = tempLeft;
			temp->right = tempRight;
			vtail->next = temp;
			vtail = vtail->next;
			nvertices++;
			if(_x<xmin) xmin = _x;
			if(_x>xmax) xmax = _x;
			if(_y<ymin) ymin = _y;
			if(_y>ymax) ymax = _y;
			w = abs(xmax - xmin);
			h = abs(ymax - ymin);
		}
		void movePoint(double _x, double _y,double newx, double newy){
			vertice_node * temp = vhead->next;
			while(temp!=NULL){
				if(temp->x == _x || temp->y == _y ) break;
				temp = temp->next;
			}
			int tempx = temp->x;
			int tempy = temp->y;
			temp->left->x += newx - tempx;
			temp->left->y += newy - tempy;
			temp->right->x += newx - tempx;
			temp->right->y += newy - tempy;
			temp->x = newx;
			temp->y = newy;
		}
		void changePoints(double _x,double _y,double newx,double newy){
			double neww = w;
			double newh = h;
			double ratex = 1;
			double ratey = 1;
			if(_x == xmax) neww += newx - _x;
			if(_x == xmin) neww -= newx - _x;
			if(_y == ymax) newh += newy - _y;
			if(_y == ymin) newh -= newy - _y;
			ratex = neww / w;
			ratey = newh / h;

			vertice_node * temp = vhead->next;
			while(temp!=NULL){
				temp->left->x *= ratex;
				temp->left->y *= ratey;
				temp->right->x *= ratex;
				temp->right->y *= ratey;
				temp->x *= newx;
				temp->y *= newy;
				temp = temp->next;
			}
		}
		void rotatePoints(double _x,double _y,double newx,double newy){}
		void movePoints(double _x,double _y,double newx,double newy){
			printf("bug1\n");
			int dx = newx - _x;
			int dy = newy - _y;
			vertice_node * temp = vhead->next;
			while(temp!=NULL){
				temp->x +=dx;
				temp->y +=dy;
				temp->left->x += dx;
				temp->left->y += dy;
				temp->right->x += dx;
				temp->right->y += dy;
				temp = temp->next;
			}
		}
		int deletePoint(double _x, double _y){
			if(nvertices == 0) return 0;
			vertice_node * temp = vhead;
			temp->x = _x;
			temp->y = _y;
			vtail->next = temp;
			vtail = vtail->next;
			nvertices++;
			if(_x<xmin) xmin = _x;
			if(_x>xmax) xmax = _x;
			if(_y<ymin) ymin = _y;
			if(_y>ymax) ymax = _y;
			w = abs(xmax - xmin);
			h = abs(ymax - ymin);
		}
};

class polygons{
	public:
		int size;
		entry_node * phead;
		entry_node * ptail;
		polygons():size(0){
			phead = new entry_node;
			ptail = phead;
		}

		void newOne(){
			entry_node * temp = new entry_node;
			ptail->next = temp;
			ptail = temp;
			size++;
			ptail->insideNameId = size*2;
			ptail->borderNameId = size*2-1;
		}

		int remove(int i){

			if(size == 0 || size<= i) return 0;
			entry_node * temp = phead;
			for(int j = 0 ; j<i;j++){
				temp = temp->next;
			}
			entry_node * temp2 = temp->next;
			if(ptail == temp2) ptail = temp;
			temp->next = temp->next->next;
			delete temp2;
			size--;
		}

		void showAll(){
			entry_node * temp = phead;
			while(temp->next!=NULL){
				temp->next->show();
				temp = temp->next;
			}
		}
//};
}entryList;