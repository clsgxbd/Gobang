//�����׼���ͷ�ļ�
#include <iostream>
#include <graphics.h>
#include<windows.h>
#include <conio.h> 
#pragma comment(lib, "winmm.lib")
#pragma comment( lib, "MSIMG32.LIB")
using namespace std;
//ȫ�ֱ�����
int winku[15][15]={0};
bool Sound;//��¼��Ч
bool isRobot;//��¼�Ƿ����˻�
IMAGE Player[2][2] 	;//������������ʾͼ
void chessboard( bool roBot,bool sound );//���̺���
//�����Զ����ͷ�ļ�
#include"Coordinate.h"
#include"MyStack.h"
#include"Menu.h"
MyStack *pStack = new MyStack( 225 );//ʵ����ջ
#include"Game.h"
