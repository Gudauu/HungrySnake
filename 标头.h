#include <iostream>
#include<string>
#include<sstream>
#include<Windows.h>
#include<conio.h>
#include<iomanip>
#include<list>
#include<random>
#include<graphics.h>
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )
using namespace std;


enum CONSTANTS{
	DIA=16,   //一个单位的大小。为了纪念守护甜心的阶砖（dia）
	NUM=30,  //阶砖数
	XMARGIN = 15,   //留点给操作介绍和分数
	YMARGIN=5,
	WALL_SIZE=NUM*DIA,    //蛇的活动范围
	PLA_X = (NUM+XMARGIN)*DIA,   //整个界面的范围
	PLA_Y= (NUM + YMARGIN) * DIA,
	MAXNUM = 80,
	
	LEFT='a',
	RIGHT='d',
	DOWN='s',
	UP='w',

	PLATFORM = RGB(100,100,100),  //整个界面
	WALL=BLACK,   //蛇的活动范围
	BODY=GREEN,
	HEAD=YELLOW,
	FOOD =GREEN,
	BONUS=RED,   //还要闪烁
	EMP=-1,
	FAIL = -1,
	BLANK = ' '
};
enum  COLORS {Zero=YELLOW,One=GREEN ,Two=RED, Three=BLUE, Four=WHITE};
struct Node
{
	int X;
	int Y;
	Node() {};
	Node(int a, int b) :X(a), Y(b) {};
	bool operator^(Node);
};
unsigned RandomU(int, int);
class Platform
{
public:
	Platform() {};
	void Front();
	
	
};
class Puzzle
{
private:
	COLORREF bodycolor;
	COLORREF bonuscolor;
	list<Node>Snake;    //记录蛇的每个Node位置
	Node curfood;  //记录当前食物位置
	Node curbonus;    //记录当前（如果有）bonus位置。若无，为（EMP,EMP）
	int score;
	int length;
	int lives = 1;
	void ReAlive();
	void PrintScore();

	void SetHead(Node node);  //把某个Node画成头.
	void SetBody(Node node);
	void SetFood(Node node);
	bool SetBonus(Node node);  //0变颜色,1普通功能
	void SetClear(Node node);  //即画成背景色
	void SetClear(Node,int,int,char);  //重载，指定大小和颜色
	void SetText(int,int, string,char);


	void IniSnake();    //以指定长度得到一条蛇
	void IniWall();

	void Ini();  //初始外墙;初始蛇;

	void DelTail();   //在蛇尾减去一个。无食物时用。
	void MoveSnake(int aa,int bb);   //长度不变。

	bool InSnake(Node);  //判断该Node是否在蛇身上
	char CheckInput(char,char);   //接受键盘输入。若不属于，返回空格
	int NextWhat(char,Node&); //当输入合法，判断下一方向是死，空，还是食物
	
	bool GeneNew(int); //1Food,2Bonus
	long GetSpeed(int);   //根据score给出暂停时间
	//friend class Platform;
	void ClearMargin(int);
	friend unsigned RandomU(int,int);
public:
	Puzzle(){};  //默认构造，只设置默认长宽
	void Play();
};
