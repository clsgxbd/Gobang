//引入标准库的头文件
#include <iostream>
#include <graphics.h>
#include<windows.h>
#include <conio.h> 
#pragma comment(lib, "winmm.lib")
#pragma comment( lib, "MSIMG32.LIB")
using namespace std;
//全局变量：
int winku[15][15]={0};
bool Sound;//记录音效
bool isRobot;//记录是否是人机
IMAGE Player[2][2] 	;//存放落子玩家提示图
void chessboard( bool roBot,bool sound );//棋盘函数
//引入自定义的头文件
#include"Coordinate.h"
#include"MyStack.h"
#include"Menu.h"
MyStack *pStack = new MyStack( 225 );//实例化栈
#include"Game.h"
