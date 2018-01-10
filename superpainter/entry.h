#ifndef ENTRY_H
#define ENTRY_H

#define BMP_Header_Length 54  //图像数据在内存块中的偏移量  

/*
包含entry，graphic，button和polygons的声明
*/

struct vertice_node {
	double x, y;
	vertice_node * next;
	vertice_node * left;
	vertice_node * right;
	vertice_node():right(NULL),left(NULL),next(NULL){}
};

class Entry {
public:
	enum type {
		LINE,	// 直线
		CURVE,	// 曲线
		POLYGON,// 多边形
		CIRCLE	// 圆
	};

	type _type;
	double xmin, xmax, ymin, ymax;
	double x, y;
	double w, h;
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
	GLuint _tex;
	int tex;
	int picked;
	int blick;
	char *_text;
	char *tex_dir;
	int nvertices;
	vertice_node * vhead;
	vertice_node * vtail;
	Entry(double _x = 0, double _y = 0, double _w = 125, double _h = 25);

	void showTex();
	void showText();
	void showPoint();
	void showLine(int flag);
	void showCurve(int flag);
	void showPick();
	void showPoints();
	void show();
	
	void setType(int x);
	void setColorInside(double c1, double c2, double c3, double c4 = 1.0);
	void setColorBorder(double c1, double c2, double c3, double c4 = 1.0);
	void setText(const char *text);
	void setBorder(int x = 1);
	void setSolid(int x = 1);
	void setTex(int x = 0);
	int setTexImage(const char* file_name);
	void refreshmaxmin();

	void addPoint(double _x, double _y);
	int deletePoint(double _x, double _y);
	bool checkIn(double _x, double _y);

	// 函数power_of_two用于判断一个整数是不是2的整数次幂    
	int power_of_two(int n);
	void setColor(double *color);
};

class Button : public Entry{
public:
	char *button_name;

	Button(double _x = 0, double _y = 0, double _w = 125, double _h = 25);
	void show();
	void setPosition(double _x, double _y);
	void setSize(double _w, double _h);
	void mouseHover();
	void mouseUnhover();
	void setName(char* _name);
};

class Graphic : public Entry {
public:
	Graphic * next;

	Graphic(double _x = 0, double _y = 0, double _w = 125, double _h = 25);

	//旋转
	void spin(double theta);
	void movePoint(double _x, double _y, double newx, double newy);
	void changePoints(double _x, double _y, double newx, double newy);
	void movePoints(double _x, double _y, double newx, double newy);

	void save_status(int & type, int & no_of_vertices, double  vertices_list[], int  status_int[], double  status_double[], char * & tex_, char * & text);
	void load_status(int  type_, int no_of_vertices, double  vertices_list[], int  status_int[], double  status_double[], char *tex_, char *text);

	void _spin(double x, double y, double theta, double &_x, double &_y);
};


class polygons {
public:
	int size;
	Graphic * phead;
	Graphic * ptail;
	polygons();
	void newOne(double _x, double _y, double _w, double _h);
	void newOne(Graphic * sample);
	int remove(int i);
	void showAll();
	void clearAll();
};

extern polygons graphList;

#endif // !ENTRY_H
