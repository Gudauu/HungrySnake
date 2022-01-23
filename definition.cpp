// stdafx.cpp : source file that includes just the standard includes
//	2_6.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "head.h"


// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
bool Node::operator^(Node node)
{
	if (node.X == X && node.Y == Y)return true;
	else return false;
}

void Puzzle::SetHead(Node node)  //把某个Node画成头.
{
	int x = node.X * DIA;
	int y = node.Y * DIA;
	setfillcolor(HEAD);
	bar(x, y, x + DIA, y + DIA);
}
void Puzzle::SetBody(Node node)    //比头稍小一些
{
	int x = (node.X) * DIA;
	int y = (node.Y) * DIA;
	setfillcolor(bodycolor);
	bar(x, y, x + DIA-2, y + DIA-2);
}
void Puzzle::SetFood(Node node)
{
	int x = node.X * DIA;
	int y = node.Y * DIA;
	setfillcolor(bodycolor);
	bar(x, y, x + DIA, y + DIA);
}
bool Puzzle::SetBonus(Node node)
{
	int x = node.X * DIA;
	int y = node.Y * DIA;
;	int mode = RandomU(0, 4);
	if (mode != 0)bonuscolor = RED;  //普通功能是RED
	else bonuscolor = RGB(RandomU(0, 255), RandomU(0, 255), RandomU(0, 255));
	setfillcolor(bonuscolor); 
	bar(x, y, x + DIA, y + DIA);    //bonus比DIA稍大一些
	return mode != 0;
}
void Puzzle::SetClear(Node node)  //即画成背景色
{
	int x = node.X * DIA;
	int y = node.Y * DIA;
	setfillcolor(WALL);
	bar(x, y, x + DIA, y + DIA);
}
void Puzzle::SetClear(Node node,int l,int w,char color)  //重载,指定删除大小和颜色（w:WALL p:PLATFORM）
{
	int x = node.X * DIA;
	int y = node.Y * DIA;
	if (color == 'w')setfillcolor(WALL);
	else setfillcolor(PLATFORM);
	bar(x, y, x + l, y + w);
}
void Puzzle::SetText(int x,int y,string str,char color)
{
	if (color == 'w')setbkcolor(WALL);
	else setbkcolor(PLATFORM);
	outtextxy(x, y, str.c_str());
}

void Puzzle::ClearMargin(int s)
{
	setfillcolor(PLATFORM);
	bar(0, WALL_SIZE * DIA, WALL_SIZE * DIA, WALL_SIZE * DIA + s);
	bar(WALL_SIZE * DIA, 0, WALL_SIZE * DIA + s, WALL_SIZE * DIA);
}
void Puzzle::IniWall()     //贪吃蛇活动范围。默认对齐左上。
{
	setfillcolor(WALL);
	setbkcolor(WALL);
	bar(0, 0, WALL_SIZE, WALL_SIZE);
}
void Puzzle::IniSnake()
{
	Snake.push_back(Node(NUM / 2, NUM/2));
	Snake.push_back(Node(NUM / 2+1, NUM/2));
	Snake.push_front(Node(NUM/ 2-1, NUM/2));;
	SetHead(Node(NUM / 2, NUM / 2));
	SetHead(Node(NUM / 2 + 1, NUM / 2));
	SetHead(Node(NUM/ 2-1,NUM/2));
	SetBody(Node(NUM / 2, NUM / 2));
	SetBody(Node(NUM / 2 + 1, NUM / 2));
}

void Puzzle::Ini() {
	IniWall();
	IniSnake();
}

void Puzzle::DelTail() {   //在蛇尾减少一个。
	Node pretail = Snake.back();
	SetClear(pretail);
	Snake.pop_back();
}
void Puzzle::MoveSnake(int x, int y)  //长度不变。
{
	Node prehead = Snake.front();  //前一个头，需要改成身子
	Node add = Node(x, y);    //新头
	Snake.push_front(add);
	SetBody(prehead);
	SetHead(add);
}



char Puzzle::CheckInput(char input,char pre)   //接受键盘输入并判断下一个方向合法性
{
	if (input != LEFT && input != RIGHT && input != UP && input != DOWN)return BLANK;  //无效输入，忽略
	switch (pre)
	{
	case LEFT:
		if (input == RIGHT)return BLANK;
		break;
	case RIGHT:
		if (input == LEFT)return BLANK;
		break;
	case UP:
		if (input == DOWN)return BLANK;
		break;
	case DOWN:
		if (input == UP)return BLANK;
	}
	return input;    
}
bool Puzzle::InSnake(Node node)
{
	list<Node>::iterator iter=Snake.begin();
	for (; iter !=Snake.end(); iter++)
	{
		if (node^(*iter))return true;   //我重载的^,表示是否相等
	}
	return false;
}
int Puzzle::NextWhat(char input,Node&nxt) //当输入合法，判断下一方向死(FAIL)，空(0),食物(1)，bonus(2)
{
	Node prehead = Snake.front();
	int x = prehead.X; int y = prehead.Y;
	switch (input)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
	}
	if (InSnake(Node(x,y))||x == -1 || x == NUM|| y == -1 || y ==NUM)return FAIL;  //可能有bug
	nxt.X = x;nxt.Y=y;    //记录下一合法方向
	if (Node(x,y)^curfood)return 1;
	if (Node(x, y) ^ curbonus)return 2;
	else return 0;
}
unsigned RandomU(int a, int b)
{
	std::mt19937 rng;   //mt19937_64unsigned long long   现在是unsigned int
	rng.seed(std::random_device()());
	std::uniform_int_distribution< std::mt19937::result_type>dist(a, b);
	//default_random_engine e;
	//e.seed(time(0));
	return dist(rng);
}
bool Puzzle::GeneNew(int choice)
{
	int x = RandomU(0, NUM-1);     //x先固定，再选有空的y
	int y;
	int mode=1;  //当choice2,即bonus的情况。0为变颜色；1为普通功能；
	do {
		y = RandomU(0, NUM-1);
	} while (InSnake(Node(x,y))||y==curfood.Y); //可能有bug。不论food还是bonus都不能在蛇和food上。
	switch (choice)
	{
	case 1:
		SetFood(Node(x, y));
		curfood.X = x; curfood.Y = y;
		break;
	case 2:
		mode=SetBonus(Node(x, y));
		curbonus.X = x; curbonus.Y = y;
	}
	return mode;
}
long Puzzle::GetSpeed(int score)
{
	if (score < 5)return 300;
	else if (score < 10)return 250;
	else if (score < 20)return 200;
	else if (score < 30)return 150;
	else if (score < 40)return 100;
	else if (score < 60)return 60;
	else if (score < 80)return 50;
	else return 30;
}
void Puzzle::PrintScore()
{
	string show = "Score: ";show.append(to_string(score));
	SetClear(Node(NUM / 5 ,NUM + YMARGIN / 2), 10 * DIA, 2 * DIA, 'p');
	SetText(NUM / 5*DIA, (NUM + YMARGIN / 2)*DIA, show, 'p');
}
void Puzzle::ReAlive()
{
	SetClear(Node(NUM, DIA),XMARGIN*DIA,2*DIA,'p');
	string show = "HP: ";
	show.append(to_string(lives));
	//show.append("条命！");
	SetText((NUM + XMARGIN / 5) * DIA, DIA, show, 'p');
	Sleep(3000);

	IniWall();
	curfood = Node(EMP, EMP);
	curbonus = Node(EMP, EMP);

	SetClear(Node(NUM, 0), XMARGIN*DIA, 3 * DIA, 'p');
	SetText((NUM + XMARGIN /10) * DIA, DIA, "Get ready, your snake is going back in 3 seconds...", 'p');
	Sleep(3000);
	SetClear(Node(NUM, 0), XMARGIN*DIA, 2 * DIA, 'p');
	//length = Snake.size();
	while (!Snake.empty())Snake.pop_front();
	IniSnake();  
	
}
void Puzzle::Play()
{
	score = 0;   //吃到的食物数
	lives = 1;
	length = 3;
	bodycolor = RGB(69,190,255);
	Ini();    //画一个墙界面给蛇
	curfood = Node(EMP, EMP);
	curbonus = Node(EMP, EMP);
	char input;
	char preinput = LEFT;
	Node nxt;
	bool needfood = true;
	bool needbonus = false;
	int bonuschoice;
	int flushcount = 1;  //右侧消息栏；空值1时不需刷新；
	long bonusstay = 1;    //bonus；持续多久后消失
	long speedscore = 0;   //有bonus时减少，否则和score一样。
	while (!_kbhit()) {}
	input = _getch();
	//BeginBatchDraw();
	while (1)
	{
		input = CheckInput(input, preinput);
		if (input == BLANK)input = preinput; //新输入无效时维持前一方向
		int next = NextWhat(input, nxt);
		if ((next != FAIL) && (Snake.size() != length)) {
			next = 3;
			//needbonus = false; needfood = false; 
		}//复活状态，绝食

		if (needfood && next != 3) {   //needfood && next != 3
			GeneNew(1); needfood = false;
		}
		if (needbonus && next != 3) { bonuschoice = GeneNew(2); bonusstay = 5000; needbonus = false; }
		switch (next)
		{
		case FAIL:
			//EndBatchDraw();
			lives--;
			if (lives <= 0)return;  //退出游戏
			else {
				ReAlive();
				needfood = true;
				curfood = Node(EMP, EMP);
				speedscore %= 20;
				input = preinput = LEFT;
				continue;
			}
			break;
		case 1:    //有食物
			MoveSnake(nxt.X, nxt.Y);
			score += 5; length++;
			speedscore += 5;
			needfood = true; curfood = Node(EMP, EMP); //恢复空值
			if ((score / 5 % 5 == 0) && curbonus.X == EMP)needbonus = true;
			break;
		case 3:    //复活长身体
			MoveSnake(nxt.X, nxt.Y);
			break;
		case 2:    //bonus
			MoveSnake(nxt.X, nxt.Y);
			DelTail();
			if(bonuschoice == 0)
			{
				bodycolor = bonuscolor;
				SetClear(Node(NUM, 0), XMARGIN * DIA, 2 * DIA, 'p');
				SetText((NUM + XMARGIN / 5) * DIA, DIA, "Color change!", 'p');
				flushcount = 2000;
			}
			else {
				bonuschoice = RandomU(1, 2);
				if (bonuschoice == 1) {
					lives++;
					SetClear(Node(NUM, 0), XMARGIN * DIA, 2 * DIA, 'p');
					SetText((NUM + XMARGIN / 5) * DIA, DIA, "HP+1", 'p');
					flushcount = 2000;
				}
				else if (bonuschoice == 2) {
					speedscore %= 20;
					SetClear(Node(NUM, 0), XMARGIN * DIA, 2 * DIA, 'p');
					SetText((NUM + XMARGIN / 5) * DIA, DIA, "Slowed down!", 'p');
					flushcount = 2000;
				}
			}
			curbonus = Node(EMP, EMP); //恢复空值
			break;
		case 0:    //空白
			MoveSnake(nxt.X, nxt.Y);
			DelTail();
		}
		PrintScore();
		preinput = input;
		//FlushBatchDraw();
		int slp = GetSpeed(speedscore);
		Sleep(slp);
		if (flushcount != 1) {
			flushcount -= slp;
			if (flushcount <= 0)    //flushcount默认值为1
			{
				flushcount = 1;
				SetClear(Node(NUM, 0), XMARGIN * DIA, 2 * DIA, 'p');
			}
		}
		if (curbonus.X != EMP) {     //显示bonus剩余时间
			bonusstay -= slp;
			setbkcolor(bonuscolor);
			outtextxy(curbonus.X * DIA + DIA / 4, curbonus.Y * DIA, to_string(bonusstay / 1000).c_str());
			if (bonusstay <= 0) {    //时间没了，bonus消失
				SetClear(curbonus); bonusstay = 1; curbonus.X = EMP; curbonus.Y = EMP;
			}
		}
		if (!_kbhit())input = preinput;
		else input = _getch();
	}
	//EndBatchDraw();
}

void Platform::Front()
{
	
	initgraph(PLA_X, PLA_Y);
	
	setfillcolor(PLATFORM);
	loadimage(NULL, "coversnake.jfif",WALL_SIZE, WALL_SIZE);
	
	outtextxy((NUM + XMARGIN / 3) * DIA-5, DIA, "INSTRUCTION");
	outtextxy((NUM + XMARGIN / 3) * DIA, 3*DIA, "UP:w");
	outtextxy((NUM + XMARGIN / 3) * DIA, 5 * DIA, "DOWN:s");
	outtextxy((NUM + XMARGIN / 3) * DIA, 7 * DIA, "LEFT:a");
	outtextxy((NUM + XMARGIN / 3) * DIA, 9 * DIA, "RIGHT:d");
	outtextxy((NUM + XMARGIN / 5) * DIA-4, 11 * DIA, "Press any key to start!");
	_getch();
	setlinecolor(PLATFORM);
	fillrectangle(0, 0, PLA_X, PLA_Y);
	Puzzle puz;
	puz.Play();
	setbkcolor(PLATFORM);
	outtextxy((NUM + XMARGIN / 3) * DIA - 5, DIA, "OOPS U ARE DEAD!");
	//closegraph();
	_getch();
}


