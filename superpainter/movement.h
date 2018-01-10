extern char * opened_file;

extern double trans;
extern double colorInside_buff[4];
extern double colorBorder_buff[4];
extern double smooth;

extern int leftMouse;
extern int choosedType;
extern int choosingColor;
extern int slipType;
extern int buttonin;

extern double standard;
extern double xtrans, ytrans;
extern double oldx,oldy;
extern double newx,newy;

/*
缩放矩阵;//
[ x  ww/2 ] [rate  ] = [x']
[ y  wh/2 ] [rate-1]   [y']
*/

enum user_op{
	sys,
	drawing,
	picking,
	slipping,
	movingpoint
};

extern user_op now_op;
extern user_op last_op;
extern int movingcanvas;
extern int spinning;
extern int changingpoints;

void my_Mouse(int button, int state, double x, double y);//鼠标按键事件
void my_PassiveMotion(double x, double y);//鼠标一般移动事件
void my_Motion(double x, double y);//鼠标按键移动事件
Button * checkInButton(double x, double y);//检查鼠标进入按钮
int checkPressButton(double x, double y);//点击按钮
void checkPressEntry(double x, double y);//选择图形
void saveEntry(int flag = 0);
void loadEntry();
void newFile();
void newColor();
void refreshStatus();
void chooseTex();
void makeSlip(double x, double y);
void showMoving();
WCHAR * charToWchar(char *s);
char* wcharToChar(LPWSTR lpwszStrIn);