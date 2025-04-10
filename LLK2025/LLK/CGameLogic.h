#pragma once
#include<iostream>
#include<stack>
#include"global.h"

using namespace std;

class CGameLogic
{
public:
	int** GameMap; // ��ͼ��Ϣ ����Ҫ�õ������ݽṹ
	int rows; // ��ͼ��
	int cols; // ��ͼ��
	int picNum; // ��ͼ������ͼƬ�ĸ���
private:
	stack<Vertex> verList; // ���ڱ�������ͼƬ������·��
public:
	~CGameLogic();
	int GetElement(int nRow, int nCol);
	// �൱�ڶ� GameMap ���г�ʼ��
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