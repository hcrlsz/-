#pragma once
#include<iostream>
using namespace std;

// ���嶥��ṹ��
typedef struct tagVertex {
	int row; // ��
	int col; // ��
	int info; // ֵΪ BLANK ��ʾ��ǰ��û��ͼƬ
} Vertex;


// �궨��
#define GAMEWND_WIDTH 800 // ��Ϸ������
#define GAMEWND_HEIGHT 600 // ��Ϸ����߶�
#define MAP_TOP 50 // ��ͼ������Ϸ�����Ϸ��ļ��
#define MAP_LEFT 20 // ��ͼ������Ϸ�������ļ��
#define PIC_WIDTH 40 // ͼƬ�Ŀ��
#define PIC_HEIGHT 40 // ͼƬ�ĸ߶�
#define Rows 10 // ��ͼ������
#define Cols 14 // ��ͼ������
#define PicNum 10 // ͼƬ�ĸ���
#define BLANK -1 // ��ͼû��ͼƬ