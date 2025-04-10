#pragma once
#include<iostream>
#include<stack>
#include"global.h"

using namespace std;

class CGameLogic
{
public:
	int** GameMap; // 地图信息 所需要用到的数据结构
	int rows; // 地图行
	int cols; // 地图列
	int picNum; // 地图包含的图片的个数
private:
	stack<Vertex> verList; // 用于保存两个图片相连的路径
public:
	~CGameLogic();
	int GetElement(int nRow, int nCol);
	// 相当于对 GameMap 进行初始化
	void InitMap(int nRows, int nCols, int nPicNum);
	bool IsLink(Vertex V1, Vertex V2);
	void Clear(Vertex V1, Vertex V2);
	void ClearVerList();
	stack<Vertex> GetVerList();
	bool isBlank();
private:
	bool LinkInRow(Vertex V1, Vertex V2);
	bool LinkInCol(Vertex V1, Vertex V2);
	bool LinkOneCorner(Vertex V1, Vertex V2);
	bool LinkTwoCorner(Vertex V1, Vertex V2);
	bool LinkY(int Row1, int Row2, int Col);
	bool LinkX(int Row, int Col1, int Col2);
};