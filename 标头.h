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
	DIA=16,   //һ����λ�Ĵ�С��Ϊ�˼����ػ����ĵĽ�ש��dia��
	NUM=30,  //��ש��
	XMARGIN = 15,   //������������ܺͷ���
	YMARGIN=5,
	WALL_SIZE=NUM*DIA,    //�ߵĻ��Χ
	PLA_X = (NUM+XMARGIN)*DIA,   //��������ķ�Χ
	PLA_Y= (NUM + YMARGIN) * DIA,
	MAXNUM = 80,
	
	LEFT='a',
	RIGHT='d',
	DOWN='s',
	UP='w',

	PLATFORM = RGB(100,100,100),  //��������
	WALL=BLACK,   //�ߵĻ��Χ
	BODY=GREEN,
	HEAD=YELLOW,
	FOOD =GREEN,
	BONUS=RED,   //��Ҫ��˸
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
	list<Node>Snake;    //��¼�ߵ�ÿ��Nodeλ��
	Node curfood;  //��¼��ǰʳ��λ��
	Node curbonus;    //��¼��ǰ������У�bonusλ�á����ޣ�Ϊ��EMP,EMP��
	int score;
	int length;
	int lives = 1;
	void ReAlive();
	void PrintScore();

	void SetHead(Node node);  //��ĳ��Node����ͷ.
	void SetBody(Node node);
	void SetFood(Node node);
	bool SetBonus(Node node);  //0����ɫ,1��ͨ����
	void SetClear(Node node);  //�����ɱ���ɫ
	void SetClear(Node,int,int,char);  //���أ�ָ����С����ɫ
	void SetText(int,int, string,char);


	void IniSnake();    //��ָ�����ȵõ�һ����
	void IniWall();

	void Ini();  //��ʼ��ǽ;��ʼ��;

	void DelTail();   //����β��ȥһ������ʳ��ʱ�á�
	void MoveSnake(int aa,int bb);   //���Ȳ��䡣

	bool InSnake(Node);  //�жϸ�Node�Ƿ���������
	char CheckInput(char,char);   //���ܼ������롣�������ڣ����ؿո�
	int NextWhat(char,Node&); //������Ϸ����ж���һ�����������գ�����ʳ��
	
	bool GeneNew(int); //1Food,2Bonus
	long GetSpeed(int);   //����score������ͣʱ��
	//friend class Platform;
	void ClearMargin(int);
	friend unsigned RandomU(int,int);
public:
	Puzzle(){};  //Ĭ�Ϲ��죬ֻ����Ĭ�ϳ���
	void Play();
};
