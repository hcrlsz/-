#pragma once
#include<iostream>
using namespace std;

// 定义顶点结构体
typedef struct tagVertex {
	int row; // 行
	int col; // 列
	int info; // 值为 BLANK 表示当前点没有图片
} Vertex;


// 宏定义
#define GAMEWND_WIDTH 800 // 游戏界面宽度
#define GAMEWND_HEIGHT 600 // 游戏界面高度
#define MAP_TOP 50 // 地图距离游戏界面上方的间距
#define MAP_LEFT 20 // 地图距离游戏界面左侧的间距
#define PIC_WIDTH 40 // 图片的宽度
#define PIC_HEIGHT 40 // 图片的高度
#define Rows 10 // 地图的行数
#define Cols 14 // 地图的列数
#define PicNum 10 // 图片的个数
#define BLANK -1 // 地图没有图片