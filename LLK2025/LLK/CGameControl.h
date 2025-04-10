#include<iostream>
#include<stack>
#include"global.h"
#include"CGameLogic.h"

using namespace std;

class CGameControl
{
public:
    Vertex selFirst;    // 选择的第一个点
    Vertex selSecond;   // 选择的第二个点
    CGameLogic m_GameLogic;  // 实现具体的逻辑
public:
    CGameControl();  // 带参数的构造函数
    // 设置第一个点的坐标
    void SetFirstPoint(int nRow, int nCol);
    // 设置第二个点的坐标
    void SetSecondPoint(int nRow, int nCol);
    // 获取地图中的数据
    int GetElement(int nRow, int nCol);
    // 开始游戏，供CGameDlg类调用
    bool StartGame(int rows, int cols, int picNum);
    // 判断selFirst和selSecond是否相连，相连路径放在verList中
    bool Link(stack<Vertex>& verList);
    // 判断游戏是否结束
    bool isWin();
};