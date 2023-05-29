#define _CRT_SECURE_NO_WARNINGS  //版本问题，防止报错
#include <stdio.h>
#include <graphics.h>		   //图形库插件
#include <conio.h>             //按键交互，_getch()
#include <time.h>              //随机函数，srand()和rand()
#include <stdlib.h>            //控制蛇的速度Sleep()

//				**********数据设计**********
//坐标属性
struct Point {
	int x;
	int y;
}point;
//蛇的属性
struct Snake{
	Point s[100];  //蛇最长100节
	int length;  //长度（节数）
	char position;  //方向
}snake;
//食物属性
struct Food {
	Point f;  //食物坐标
	int flag;  //标记（存在与否）
	int grade;  //分数
}food;
//把方向枚举出来
enum position{up,down,left,right};
//窗口句柄（实现游戏结束的弹框）
HWND hwnd = NULL;

//				**********具体步骤实现**********
//初始化蛇
void initSnake() {
	//初始前三节坐标
	snake.s[2].x = 0;
	snake.s[2].y = 0;
	snake.s[1].x = 10;
	snake.s[1].y = 0;
	snake.s[0].x = 20;
	snake.s[0].y = 0;
	//长度
	snake.length = 3;
	//方向
	snake.position = right;
}

//画蛇
void drawSnake() {
	for (int i = 0; i < snake.length; i++) {
		setlinecolor(BLACK);  //设置边框颜色
		setfillcolor(BLUE);  //设置颜色
		//填充矩形函数
		fillrectangle(snake.s[i].x, snake.s[i].y, snake.s[i].x+10, snake.s[i].y+10);  
	}
}

//移动蛇
void moveSnake() {
	//后面的坐标覆盖前面的坐标来实现蛇的移动
	for (int i = snake.length - 1; i > 0; i--) {
		
		snake.s[i].x = snake.s[i - 1].x;
		snake.s[i].y = snake.s[i - 1].y;
	}
	//通过蛇头来控制移动
	switch (snake.position)
	{
	case up:
		snake.s[0].y -= 10;
		break;
	case down:
		snake.s[0].y += 10;
		break;
	case left:
		snake.s[0].x -= 10;
		break;
	case right:
		snake.s[0].x += 10;
		break;
	default:
		break;
	}
}

//按键控制方向
void keyDown() {
	char key = _getch();  //键盘输入
	//按空格进行暂停
	if (key == 32) {
		while (_getch() != 32);
	}
	//控制上下左右
	switch (key) 
	{
	case 'w':
	case 'W':
	case 72:  //键盘的 ↑ 对应的ASCII码
		if (snake.position != down)
			snake.position = up;  //保证按 ↑ 键一定是向上走的
		break;
	case 's':
	case 'S':
	case 80:
		if (snake.position != up)
			snake.position = down;
		break;
	case 'a':
	case 'A':
	case 75:
		if (snake.position != right)
			snake.position = left;
		break;
	case 'd':
	case 'D':
	case 77:
		if (snake.position != left)
			snake.position = right;
		break;
	}

}

//初始化食物
void initFood() {
	srand((unsigned int)time(NULL));  //随机数种子
	food.f.x = rand() % 80 * 10;  //不要超过窗口大小（长800）
	food.f.y = rand() % 60 * 10;
	food.flag = 1;  //标记为1代表存在
	//排除食物出现在蛇身上的情况
	for (int i = 0; i < snake.length; i++) {
		if (food.f.x == snake.s[i].x && food.f.y == snake.s[i].y) {
			//如果食物生成点与蛇重合则重新生成食物位置
			food.f.x = rand() % 80 * 10;
			food.f.y = rand() % 60 * 10;
		}
	}
}

//画食物
void drawFood() {
	setlinecolor(BLACK);  //边框颜色
	setfillcolor(RED);  //背景色
	fillrectangle(food.f.x, food.f.y, food.f.x + 10, food.f.y + 10);
}

//蛇吃食物
void eatFood() {
	//蛇头与食物坐标重合则相当于吃掉食物，食物消失
	if (snake.s[0].x == food.f.x && snake.s[0].y == food.f.y) {
		food.flag = 0;
		snake.length++;
		food.grade += 10;
	}
}

//显示分数
void showGrade() {
	char grade[100] = "";
	sprintf(grade, "分数：%d", food.grade);  //格式化写入分数
	setbkmode(TRANSPARENT);  //设置为透明背景，防止挡到蛇
	settextcolor(LIGHTBLUE);  //设置字体颜色为浅蓝色
	outtextxy(650, 30, grade);  //打印在右上角
}
//游戏结束（蛇死亡）
int snakeDie() {
	//撞墙
	if (snake.s[0].x < 0 || snake.s[0].x > 800 || snake.s[0].y < 0 || snake.s[0].y > 600) {
		MessageBox(hwnd, "撞墙，游戏结束！", "撞墙警告", 0);
		return 1;  //游戏结束
	}
	//撞到自己
	for (int i = 1; i < snake.length; i++) {
		if (snake.s[0].x == snake.s[i].x && snake.s[0].y == snake.s[i].y) {
			MessageBox(hwnd, "自杀，游戏结束！", "自杀警告", 0);
			return 1;
		}
	}
	return 0;
}

int main() {

	//绘制窗口
	hwnd = initgraph(800,600);  //创建图形窗口
	setbkcolor(WHITE);  //设置背景为白色
	//cleardevice();   //刷新窗口（使窗口保持白色）
	initSnake();  //初始化蛇

	while (1) {
		cleardevice();
		drawSnake();  //画蛇
		moveSnake();  //移动蛇

		drawFood();  //画食物
		eatFood();  //蛇吃食物
		showGrade();  //显示成绩
		if (snakeDie()) {
			break;  //蛇死亡，跳出循环
		}
		if (food.flag == 0) {
			initFood();  //初始化食物
		}
		if (_kbhit()) {  //判断按键是否按下
			keyDown();  //4、按键控制
		}
		Sleep(100);
	}
	

	//_getch();  
	closegraph();  //关闭窗口

	system("pause");
	return 0;
}