#include "stdafx.h"
#include "my_head.h"


	Entry::Entry(double _x, double _y, double _w, double _h) :
	_type(POLYGON), nvertices(0), x(_x), y(_y), w(_w), h(_h), solid(1), border(1), mouseIn(0), picked(0), blick(0), tex(0), _text(NULL), tex_dir(NULL), width(2), insideNameId(0), borderNameId(0) {
	for (int i = 0; i < 3; i++) {
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
	xmin = _x;
	xmax = _x + _w;
	ymin = _y;
	ymax = _y + _h;
}

	void Entry::showTex() {
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushMatrix();
		glPushName(insideNameId);
		glBindTexture(GL_TEXTURE_2D, _tex);

		if (_type == POLYGON) {
			glBegin(GL_POLYGON);
			vertice_node *temp2 = vhead;
			while (temp2->next != NULL) {
				//printf("%lf %lf \n", temp2->next->x, temp2->next->y);
				glTexCoord2d((temp2->next->x - xmin) / w, (temp2->next->y - ymin) / h);
				glVertex2d(standard*(temp2->next->x + xtrans) - (standard - 1) * ww / 2, standard*(temp2->next->y + ytrans) - (standard - 1) * wh / 2);
				temp2 = temp2->next;
			}
			glEnd();
		}
		else {
			glBegin(GL_POLYGON);
			vertice_node * temp = vhead->next;
			while (temp->next != NULL) {
				double p1x = temp->x;
				double p1y = temp->y;
				double p2x = temp->right->x;
				double p2y = temp->right->y;
				double p3x = temp->next->left->x;
				double p3y = temp->next->left->y;
				double p4x = temp->next->x;
				double p4y = temp->next->y;
				for (double t = 0.0; t <= 1.01; t += 0.01) {
					double a1 = pow((1 - t), 3);
					double a2 = pow((1 - t), 2) * 3 * t;
					double a3 = 3 * t*t*(1 - t);
					double a4 = t*t*t;
					double x_temp = p1x*a1 + p2x*a2 + p3x*a3 + p4x*a4;
					double y_temp = p1y*a1 + p2y*a2 + p3y*a3 + p4y*a4;
					if (x_temp<xmin) xmin = x_temp;
					if (x_temp>xmax) xmax = x_temp;
					if (y_temp<ymin) ymin = y_temp;
					if (y_temp>ymax) ymax = y_temp;
					w = fabs(xmax - xmin);
					h = fabs(ymax - ymin);
					glTexCoord2d((x_temp - xmin) / w, (y_temp - ymin) / h);
					glVertex2d((x_temp + xtrans)*standard - (standard - 1) * ww / 2, (y_temp + ytrans)*standard - (standard - 1) * wh / 2);
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
			for (double t = 0.0; t <= 1.01; t += 0.01) {
				double a1 = pow((1 - t), 3);
				double a2 = pow((1 - t), 2) * 3 * t;
				double a3 = 3 * t*t*(1 - t);
				double a4 = t*t*t;
				double x_temp = p1x*a1 + p2x*a2 + p3x*a3 + p4x*a4;
				double y_temp = p1y*a1 + p2y*a2 + p3y*a3 + p4y*a4;
				if (x_temp < xmin) xmin = x_temp;
				if (x_temp > xmax) xmax = x_temp;
				if (y_temp < ymin) ymin = y_temp;
				if (y_temp > ymax) ymax = y_temp;
				w = fabs(xmax - xmin);
				h = fabs(ymax - ymin);
				glTexCoord2d((x_temp - xmin) / w, (y_temp - ymin) / h);
				glVertex2d((x_temp + xtrans)*standard - (standard - 1) * ww / 2, (y_temp + ytrans)*standard - (standard - 1) * wh / 2);
			}
			glEnd();
		}
		/*
		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex2d(standard*(xmin + xtrans) - (standard - 1) * ww / 2, standard*(ymin + ytrans) - (standard - 1) * wh / 2);
		glTexCoord2d(1.0f, 0.0f);
		glVertex2d(standard*((xmin + xtrans) + w) - (standard - 1) * ww / 2, standard*(ymin + ytrans) - (standard - 1) * wh / 2);
		glTexCoord2d(1.0f, 1.0f);
		glVertex2d(standard*((xmin + xtrans) + w) - (standard - 1) * ww / 2, standard*((ymin + ytrans) + h) - (standard - 1) * wh / 2);
		glTexCoord2d(0.0f, 1.0f);
		glVertex2d(standard*(xmin + xtrans) - (standard - 1) * ww / 2, standard*((ymin + ytrans) + h) - (standard - 1) * wh / 2);
		glEnd();
		*/
		glPopName();
		glPopMatrix();
		glPopAttrib();
	}
	void Entry::showText() {
		setColor(colorText);
		glRasterPos2d(standard*(x + xtrans + 5) - (standard - 1) * ww / 2, standard*((y + ytrans) + h - 18) - (standard - 1) * wh / 2);
		for (char *c = _text; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
		}
	}
	void Entry::showPoint() {
		glPushName(borderNameId);
		setColor(colorBorder);
		glLineWidth(standard*width);
		glBegin(GL_POINTS);
		glVertex2d(standard*(vhead->next->x + xtrans) - (standard - 1) * ww / 2, standard*(vhead->next->y + ytrans) - (standard - 1) * wh / 2);
		glEnd();
		glPopName();
	}
	void Entry::showLine(int flag) {
		if (flag == 0) {
			//printf("%lf %lf %lf %lf \n", colorBorder[0], colorBorder[1], colorBorder[2], colorBorder[3]);
			glPushName(borderNameId);
			setColor(colorBorder);
			glLineWidth(standard*width);
			if (_type == LINE) glBegin(GL_LINE_STRIP);
			else glBegin(GL_LINE_LOOP);
			vertice_node *temp2 = vhead;
			while (temp2->next != NULL) {
				//printf("%lf %lf \n", temp2->next->x, temp2->next->y);
				glVertex2d(standard*(temp2->next->x + xtrans) - (standard - 1) * ww / 2, standard*(temp2->next->y + ytrans) - (standard - 1) * wh / 2);
				temp2 = temp2->next;
			}
			glEnd();
			glPopName();
		}
		else {
			glPushName(insideNameId);
			GLUtesselator* m_pTess;
			m_pTess = gluNewTess();
			gluTessCallback(m_pTess, GLU_TESS_BEGIN, (void (CALLBACK *)())glBegin);
			gluTessCallback(m_pTess, GLU_TESS_VERTEX, (void (CALLBACK *)())glVertex3dv);
			gluTessCallback(m_pTess, GLU_END, (void (CALLBACK *)())glEnd);
			gluTessBeginPolygon(m_pTess, NULL);
			gluTessBeginContour(m_pTess);
			setColor(colorInside);

			GLdouble (*quad)[3] = (GLdouble(*)[3])malloc(sizeof(GLdouble) * nvertices * 3);
			//GLdouble quad[nvertices][3];
			vertice_node *temp2 = vhead;
			int i = 0;
			while (temp2->next != NULL) {
				quad[i][0] = standard*(temp2->next->x + xtrans) - (standard - 1) * ww / 2;
				quad[i][1] = standard*(temp2->next->y + ytrans) - (standard - 1) * wh / 2;
				quad[i][2] = 0;
				gluTessVertex(m_pTess, quad[i], quad[i]);
				temp2 = temp2->next;
				i++;
			}
			gluTessEndContour(m_pTess);
			gluTessEndPolygon(m_pTess);
			gluDeleteTess(m_pTess);
			glPopName();
		}
	}
	void Entry::showCurve(int flag) {
		refreshmaxmin();
		if (flag == 0) {
			glLineWidth(standard*width);
			setColor(colorBorder);
			glPushName(borderNameId);
			glBegin(GL_LINE_STRIP);
		}
		else {
			setColor(colorInside);
			glPushName(insideNameId);
			glBegin(GL_POLYGON);
		}
		vertice_node * temp = vhead->next;
		while (temp->next != NULL) {
			double p1x = temp->x;
			double p1y = temp->y;
			double p2x = temp->right->x;
			double p2y = temp->right->y;
			double p3x = temp->next->left->x;
			double p3y = temp->next->left->y;
			double p4x = temp->next->x;
			double p4y = temp->next->y;
			for (double t = 0.0; t <= 1.01; t += 0.05) {
				double a1 = pow((1 - t), 3);
				double a2 = pow((1 - t), 2) * 3 * t;
				double a3 = 3 * t*t*(1 - t);
				double a4 = t*t*t;
				double x_temp = p1x*a1 + p2x*a2 + p3x*a3 + p4x*a4;
				double y_temp = p1y*a1 + p2y*a2 + p3y*a3 + p4y*a4;
				if (x_temp<xmin) xmin = x_temp;
				if (x_temp>xmax) xmax = x_temp;
				if (y_temp<ymin) ymin = y_temp;
				if (y_temp>ymax) ymax = y_temp;
				w = fabs(xmax - xmin);
				h = fabs(ymax - ymin);
				glVertex2d((x_temp + xtrans)*standard - (standard - 1) * ww / 2, (y_temp + ytrans)*standard - (standard - 1) * wh / 2);
			}
			temp = temp->next;
		}
		if (_type == CIRCLE) {
			double p1x = temp->x;
			double p1y = temp->y;
			double p2x = temp->right->x;
			double p2y = temp->right->y;
			double p3x = vhead->next->left->x;
			double p3y = vhead->next->left->y;
			double p4x = vhead->next->x;
			double p4y = vhead->next->y;
			for (double t = 0.0; t <= 1.01; t += 0.05) {
				double a1 = pow((1 - t), 3);
				double a2 = pow((1 - t), 2) * 3 * t;
				double a3 = 3 * t*t*(1 - t);
				double a4 = t*t*t;
				double x_temp = p1x*a1 + p2x*a2 + p3x*a3 + p4x*a4;
				double y_temp = p1y*a1 + p2y*a2 + p3y*a3 + p4y*a4;
				if (x_temp<xmin) xmin = x_temp;
				if (x_temp>xmax) xmax = x_temp;
				if (y_temp<ymin) ymin = y_temp;
				if (y_temp>ymax) ymax = y_temp;
				w = fabs(xmax - xmin);
				h = fabs(ymax - ymin);
				glVertex2d((x_temp + xtrans)*standard - (standard - 1) * ww / 2, (y_temp + ytrans)*standard - (standard - 1) * wh / 2);
			}
		}
		glEnd();
		glPopName();
	}
	void Entry::showPick() {
		glPushName(1);
		// 1000100010001000
		glLineWidth(3);
		glLineStipple(1, 0x8888);
		glColor4d(0, 0, 0, 1);
		glBegin(GL_LINE_STRIP & GL_LINE_LOOP);
		glVertex2d(standard*(xmin - width / 2 + xtrans) - (standard - 1) * ww / 2, standard*(ymin + ytrans - width / 2) - (standard - 1) * wh / 2);
		glVertex2d(standard*(xmin - width / 2 + xtrans) - (standard - 1) * ww / 2, standard*(ymax + ytrans + width / 2) - (standard - 1) * wh / 2);
		glVertex2d(standard*(xmax + width / 2 + xtrans) - (standard - 1) * ww / 2, standard*(ymax + ytrans + width / 2) - (standard - 1) * wh / 2);
		glVertex2d(standard*(xmax + width / 2 + xtrans) - (standard - 1) * ww / 2, standard*(ymin + ytrans - width / 2) - (standard - 1) * wh / 2);
		glEnd();
		glPopName();
		glLineStipple(1, 0xFFFF);
	}
	void Entry::showPoints() {
		glPushName(1);
		glLineWidth(1);
		vertice_node *temp = vhead->next;
		while (temp != NULL) {
			glColor4d(0, 0, 0, 1);
			if (_type == CURVE || _type == CIRCLE) {
				glLineStipple(1, 0x8888);
				glBegin(GL_LINE_STRIP);
				glVertex2d(standard*(temp->left->x + xtrans) - (standard - 1) * ww / 2, standard*(temp->left->y + ytrans) - (standard - 1) * wh / 2);
				glVertex2d(standard*(temp->x + xtrans) - (standard - 1) * ww / 2, standard*(temp->y + ytrans) - (standard - 1) * wh / 2);
				glVertex2d(standard*(temp->right->x + xtrans) - (standard - 1) * ww / 2, standard*(temp->right->y + ytrans) - (standard - 1) * wh / 2);
				glEnd();
				glLineStipple(1, 0xFFFF);
			}

			glColor4d(1,1,1,1);
			glBegin(GL_POLYGON);
			glVertex2d(standard*(temp->left->x + xtrans) - (standard - 1) * ww / 2 - 3, standard*(temp->left->y + ytrans) - (standard - 1) * wh / 2 - 3);
			glVertex2d(standard*(temp->left->x + xtrans) - (standard - 1) * ww / 2 - 3, standard*(temp->left->y + ytrans) - (standard - 1) * wh / 2 + 3);
			glVertex2d(standard*(temp->left->x + xtrans) - (standard - 1) * ww / 2 + 3, standard*(temp->left->y + ytrans) - (standard - 1) * wh / 2 + 3);
			glVertex2d(standard*(temp->left->x + xtrans) - (standard - 1) * ww / 2 + 3, standard*(temp->left->y + ytrans) - (standard - 1) * wh / 2 - 3);
			glEnd();																															   
			glBegin(GL_POLYGON);																												   
			glVertex2d(standard*(temp->x + xtrans) - (standard - 1) * ww / 2 - 3, standard*(temp->y + ytrans) - (standard - 1) * wh / 2 - 3);	   
			glVertex2d(standard*(temp->x + xtrans) - (standard - 1) * ww / 2 - 3, standard*(temp->y + ytrans) - (standard - 1) * wh / 2 + 3);
			glVertex2d(standard*(temp->x + xtrans) - (standard - 1) * ww / 2 + 3, standard*(temp->y + ytrans) - (standard - 1) * wh / 2 + 3);
			glVertex2d(standard*(temp->x + xtrans) - (standard - 1) * ww / 2 + 3, standard*(temp->y + ytrans) - (standard - 1) * wh / 2 - 3);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex2d(standard*(temp->right->x+ xtrans) - (standard - 1) * ww / 2 - 3 , standard*(temp->right->y + ytrans) - (standard - 1) * wh / 2 - 3);
			glVertex2d(standard*(temp->right->x+ xtrans) - (standard - 1) * ww / 2 - 3 , standard*(temp->right->y + ytrans) - (standard - 1) * wh / 2 + 3);
			glVertex2d(standard*(temp->right->x+ xtrans) - (standard - 1) * ww / 2 + 3 , standard*(temp->right->y + ytrans) - (standard - 1) * wh / 2 + 3);
			glVertex2d(standard*(temp->right->x+ xtrans) - (standard - 1) * ww / 2 + 3 , standard*(temp->right->y + ytrans) - (standard - 1) * wh / 2 - 3);
			glEnd();

			glColor4d(0, 0, 0, 1);
			glBegin(GL_LINE_LOOP);
			glVertex2d(standard*(temp->left->x + xtrans) - (standard - 1) * ww / 2 - 3, standard*(temp->left->y + ytrans) - (standard - 1) * wh / 2 - 3);
			glVertex2d(standard*(temp->left->x + xtrans) - (standard - 1) * ww / 2 - 3, standard*(temp->left->y + ytrans) - (standard - 1) * wh / 2 + 3);
			glVertex2d(standard*(temp->left->x + xtrans) - (standard - 1) * ww / 2 + 3, standard*(temp->left->y + ytrans) - (standard - 1) * wh / 2 + 3);
			glVertex2d(standard*(temp->left->x + xtrans) - (standard - 1) * ww / 2 + 3, standard*(temp->left->y + ytrans) - (standard - 1) * wh / 2 - 3);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2d(standard*(temp->x + xtrans) - (standard - 1) * ww / 2 - 3, standard*(temp->y + ytrans) - (standard - 1) * wh / 2 - 3);
			glVertex2d(standard*(temp->x + xtrans) - (standard - 1) * ww / 2 - 3, standard*(temp->y + ytrans) - (standard - 1) * wh / 2 + 3);
			glVertex2d(standard*(temp->x + xtrans) - (standard - 1) * ww / 2 + 3, standard*(temp->y + ytrans) - (standard - 1) * wh / 2 + 3);
			glVertex2d(standard*(temp->x + xtrans) - (standard - 1) * ww / 2 + 3, standard*(temp->y + ytrans) - (standard - 1) * wh / 2 - 3);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2d(standard*(temp->right->x + xtrans) - (standard - 1) * ww / 2 - 3, standard*(temp->right->y  + ytrans) - (standard - 1) * wh / 2- 3);
			glVertex2d(standard*(temp->right->x + xtrans) - (standard - 1) * ww / 2 - 3, standard*(temp->right->y  + ytrans) - (standard - 1) * wh / 2+ 3);
			glVertex2d(standard*(temp->right->x + xtrans) - (standard - 1) * ww / 2 + 3, standard*(temp->right->y  + ytrans) - (standard - 1) * wh / 2+ 3);
			glVertex2d(standard*(temp->right->x + xtrans) - (standard - 1) * ww / 2 + 3, standard*(temp->right->y  + ytrans) - (standard - 1) * wh / 2- 3);
			glEnd();
			temp = temp->next;
		}
		glPopName();
	}
	void Entry::show() {
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushMatrix();
		if (nvertices == 1 && _type != CIRCLE) {
			showPoint();
			glPopMatrix();
			glPopAttrib();
			return;
		}
		if (tex && ( _type == POLYGON || _type == CIRCLE) ) {
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
		if (border) {
			switch (_type) {
			case LINE:		showLine(0); break;
			case CURVE:		showCurve(0); break;
			case POLYGON:	showLine(0); break;
			case CIRCLE:	showCurve(0); break;
			default:		break;
			}
		}
		if (_text != NULL) showText();
		if (picked) showPick();
		if (blick) showPoints();
		glPopMatrix();
		glPopAttrib();
	}
	
	void Entry::setType(int x) {
		switch (x) {
		case 0:_type = LINE; break;
		case 1:_type = CURVE; break;
		case 2:_type = POLYGON; break;
		case 3:_type = POLYGON; break;
		case 4:_type = CIRCLE; break;
		case 5:_type = CIRCLE; break;
		}
	}
	void Entry::setColorInside(double c1, double c2, double c3, double c4) {
		colorInside[0] = c1;
		colorInside[1] = c2;
		colorInside[2] = c3;
		colorInside[3] = c4;
	}
	void Entry::setColorBorder(double c1, double c2, double c3, double c4) {
		colorBorder[0] = c1;
		colorBorder[1] = c2;
		colorBorder[2] = c3;
		colorBorder[3] = c4;
	}
	void Entry::setText(const char *text) {
		if (text == NULL) {
			if (_text != NULL) delete _text;
			_text = NULL;
			return;
		}
		_text = new char[strlen(text)];
		strcpy(_text, text);
	}
	void Entry::setBorder(int x) {
		border = x;
	}
	void Entry::setSolid(int x) {
		solid = x;
	}
	void Entry::setTex(int x) {
		tex = x;
	}
	int Entry::setTexImage(const char* file_name) {
		if (file_name == NULL) {
			if (tex_dir != NULL) delete tex_dir;
			tex_dir = NULL;
			return 0;
		}
		tex_dir = new char[strlen(file_name)];
		strcpy(tex_dir, file_name);
		GLint width, height, total_bytes;
		GLubyte* pixels = 0;
		GLuint last_texture_ID = 0, texture_ID = 0;

		// 打开文件，如果失败，返回    
		FILE* pFile = fopen(file_name, "rb");
		if (pFile == 0)
			return 2;

		// 读取文件中图象的宽度和高度    
		fseek(pFile, 0x0012, SEEK_SET);
		fread(&width, 4, 1, pFile);
		fread(&height, 4, 1, pFile);
		fseek(pFile, BMP_Header_Length, SEEK_SET);

		// 计算每行像素所占字节数，并根据此数据计算总像素字节数    
		{
			GLint line_bytes = width * 3;
			while (line_bytes % 4 != 0)
				++line_bytes;
			total_bytes = line_bytes * height;
		}

		// 根据总像素字节数分配内存    
		pixels = (GLubyte*)malloc(total_bytes);
		if (pixels == 0)
		{
			fclose(pFile);
			return 3;
		}

		// 读取像素数据    
		if (fread(pixels, total_bytes, 1, pFile) <= 0)
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
			if (!power_of_two(width)
				|| !power_of_two(height)
				|| width > max
				|| height > max)
			{
				const GLint new_width = 256;
				const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形    
				GLint new_line_bytes, new_total_bytes;
				GLubyte* new_pixels = 0;

				// 计算每行需要的字节数和总字节数    
				new_line_bytes = new_width * 3;
				while (new_line_bytes % 4 != 0)
					++new_line_bytes;
				new_total_bytes = new_line_bytes * new_height;

				// 分配内存    
				new_pixels = (GLubyte*)malloc(new_total_bytes);
				if (new_pixels == 0)
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
		if (texture_ID == 0)
		{
			free(pixels);
			fclose(pFile);
			return 6;
		}

		// 绑定新的纹理，载入纹理并设置纹理参数    
		// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复    
		GLint lastTextureID = last_texture_ID;
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

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, 0x80E0, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定    
		free(pixels);
		_tex = texture_ID;
		return 1;
	}
	void Entry::refreshmaxmin() {
		if (nvertices == 0) return;
		vertice_node * temp = vhead->next;
		xmin = temp->x;
		xmax = temp->x;
		ymin = temp->y;
		ymax = temp->y;
		temp = temp->next;
		while (temp != NULL) {
			double _x = temp->x;
			double _y = temp->y;
			if (_x<xmin) xmin = _x;
			if (_x>xmax) xmax = _x;
			if (_y<ymin) ymin = _y;
			if (_y>ymax) ymax = _y;
			temp = temp->next;
		}
		w = fabs(xmax - xmin);
		h = fabs(ymax - ymin);
	}

	void Entry::addPoint(double _x, double _y) {
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
		refreshmaxmin();
	}
	int Entry::deletePoint(double _x, double _y) {
		if (nvertices == 0) return 0;
		vertice_node * temp = vhead;
		while (temp->next != NULL) {
			if (temp->next->x == _x && temp->next->y == _y) break;
			temp = temp->next;
		}
		vertice_node * temp2 = temp->next;
		temp->next = temp2->next;
		delete temp2;
		refreshmaxmin();
	}
	bool Entry::checkIn(double _x, double _y) {
		
		//printf("%lf %lf %lf %lf \n",xmax,xmin,ymax,ymin);
		//printf("%lf %lf \n", _x, _y);
		if (_x <= xmax && _x >= xmin && _y <= ymax && _y >= ymin) {
			return true;
		}
		else return false;
	}

	// 函数power_of_two用于判断一个整数是不是2的整数次幂    
	int Entry::power_of_two(int n) {
		if (n <= 0)
			return 0;
		return (n & (n - 1)) == 0;
	}
	void Entry::setColor(double *color) {
		glColor4dv(color);
	}

