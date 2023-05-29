#define _CRT_SECURE_NO_WARNINGS  //�汾���⣬��ֹ����
#include <stdio.h>
#include <graphics.h>		   //ͼ�ο���
#include <conio.h>             //����������_getch()
#include <time.h>              //���������srand()��rand()
#include <stdlib.h>            //�����ߵ��ٶ�Sleep()

//				**********�������**********
//��������
struct Point {
	int x;
	int y;
}point;
//�ߵ�����
struct Snake{
	Point s[100];  //���100��
	int length;  //���ȣ�������
	char position;  //����
}snake;
//ʳ������
struct Food {
	Point f;  //ʳ������
	int flag;  //��ǣ��������
	int grade;  //����
}food;
//�ѷ���ö�ٳ���
enum position{up,down,left,right};
//���ھ����ʵ����Ϸ�����ĵ���
HWND hwnd = NULL;

//				**********���岽��ʵ��**********
//��ʼ����
void initSnake() {
	//��ʼǰ��������
	snake.s[2].x = 0;
	snake.s[2].y = 0;
	snake.s[1].x = 10;
	snake.s[1].y = 0;
	snake.s[0].x = 20;
	snake.s[0].y = 0;
	//����
	snake.length = 3;
	//����
	snake.position = right;
}

//����
void drawSnake() {
	for (int i = 0; i < snake.length; i++) {
		setlinecolor(BLACK);  //���ñ߿���ɫ
		setfillcolor(BLUE);  //������ɫ
		//�����κ���
		fillrectangle(snake.s[i].x, snake.s[i].y, snake.s[i].x+10, snake.s[i].y+10);  
	}
}

//�ƶ���
void moveSnake() {
	//��������긲��ǰ���������ʵ���ߵ��ƶ�
	for (int i = snake.length - 1; i > 0; i--) {
		
		snake.s[i].x = snake.s[i - 1].x;
		snake.s[i].y = snake.s[i - 1].y;
	}
	//ͨ����ͷ�������ƶ�
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

//�������Ʒ���
void keyDown() {
	char key = _getch();  //��������
	//���ո������ͣ
	if (key == 32) {
		while (_getch() != 32);
	}
	//������������
	switch (key) 
	{
	case 'w':
	case 'W':
	case 72:  //���̵� �� ��Ӧ��ASCII��
		if (snake.position != down)
			snake.position = up;  //��֤�� �� ��һ���������ߵ�
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

//��ʼ��ʳ��
void initFood() {
	srand((unsigned int)time(NULL));  //���������
	food.f.x = rand() % 80 * 10;  //��Ҫ�������ڴ�С����800��
	food.f.y = rand() % 60 * 10;
	food.flag = 1;  //���Ϊ1�������
	//�ų�ʳ������������ϵ����
	for (int i = 0; i < snake.length; i++) {
		if (food.f.x == snake.s[i].x && food.f.y == snake.s[i].y) {
			//���ʳ�����ɵ������غ�����������ʳ��λ��
			food.f.x = rand() % 80 * 10;
			food.f.y = rand() % 60 * 10;
		}
	}
}

//��ʳ��
void drawFood() {
	setlinecolor(BLACK);  //�߿���ɫ
	setfillcolor(RED);  //����ɫ
	fillrectangle(food.f.x, food.f.y, food.f.x + 10, food.f.y + 10);
}

//�߳�ʳ��
void eatFood() {
	//��ͷ��ʳ�������غ����൱�ڳԵ�ʳ�ʳ����ʧ
	if (snake.s[0].x == food.f.x && snake.s[0].y == food.f.y) {
		food.flag = 0;
		snake.length++;
		food.grade += 10;
	}
}

//��ʾ����
void showGrade() {
	char grade[100] = "";
	sprintf(grade, "������%d", food.grade);  //��ʽ��д�����
	setbkmode(TRANSPARENT);  //����Ϊ͸����������ֹ������
	settextcolor(LIGHTBLUE);  //����������ɫΪǳ��ɫ
	outtextxy(650, 30, grade);  //��ӡ�����Ͻ�
}
//��Ϸ��������������
int snakeDie() {
	//ײǽ
	if (snake.s[0].x < 0 || snake.s[0].x > 800 || snake.s[0].y < 0 || snake.s[0].y > 600) {
		MessageBox(hwnd, "ײǽ����Ϸ������", "ײǽ����", 0);
		return 1;  //��Ϸ����
	}
	//ײ���Լ�
	for (int i = 1; i < snake.length; i++) {
		if (snake.s[0].x == snake.s[i].x && snake.s[0].y == snake.s[i].y) {
			MessageBox(hwnd, "��ɱ����Ϸ������", "��ɱ����", 0);
			return 1;
		}
	}
	return 0;
}

int main() {

	//���ƴ���
	hwnd = initgraph(800,600);  //����ͼ�δ���
	setbkcolor(WHITE);  //���ñ���Ϊ��ɫ
	//cleardevice();   //ˢ�´��ڣ�ʹ���ڱ��ְ�ɫ��
	initSnake();  //��ʼ����

	while (1) {
		cleardevice();
		drawSnake();  //����
		moveSnake();  //�ƶ���

		drawFood();  //��ʳ��
		eatFood();  //�߳�ʳ��
		showGrade();  //��ʾ�ɼ�
		if (snakeDie()) {
			break;  //������������ѭ��
		}
		if (food.flag == 0) {
			initFood();  //��ʼ��ʳ��
		}
		if (_kbhit()) {  //�жϰ����Ƿ���
			keyDown();  //4����������
		}
		Sleep(100);
	}
	

	//_getch();  
	closegraph();  //�رմ���

	system("pause");
	return 0;
}