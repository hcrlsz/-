#include<iostream>
#include<stack>
#include"global.h"
#include"CGameLogic.h"

using namespace std;

class CGameControl
{
public:
    Vertex selFirst;    // ѡ��ĵ�һ����
    Vertex selSecond;   // ѡ��ĵڶ�����
    CGameLogic m_GameLogic;  // ʵ�־�����߼�
public:
    CGameControl();  // �������Ĺ��캯��
    // ���õ�һ���������
    void SetFirstPoint(int nRow, int nCol);
    // ���õڶ����������
    void SetSecondPoint(int nRow, int nCol);
    // ��ȡ��ͼ�е�����
    int GetElement(int nRow, int nCol);
    // ��ʼ��Ϸ����CGameDlg�����
    bool StartGame(int rows, int cols, int picNum);
    // �ж�selFirst��selSecond�Ƿ�����������·������verList��
    bool Link(stack<Vertex>& verList);
    // �ж���Ϸ�Ƿ����
    bool isWin();
};