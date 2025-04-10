#include "pch.h"

#include"CGameControl.h"

// 带参数的构造函数
CGameControl::CGameControl() {
	/*m_GameLogic = gameLogic;*/
}

// 获取地图中的数据zzz
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_GameLogic.GetElement(nRow, nCol);
}

// 开始游戏，供 CGameDlg 类调用
bool CGameControl::StartGame(int rows, int cols, int picNum)
{
	// 首先判断 3 个参数是否合理，不合理，返回 false
	// 进行地图初始化，填充 m_pGameMap 返回 true
	if ((rows * cols) % (picNum * 2) != 0)
		return false;
	else
		m_GameLogic.InitMap(rows, cols, picNum);
	return true;
}

// 设置第一个点的坐标
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	selFirst.row = nRow;
	selFirst.col = nCol;
}

// 设置第二个点的坐标
void CGameControl::SetSecondPoint(int nRow, int nCol)
{
	selSecond.row = nRow;
	selSecond.col = nCol;
}

bool CGameControl::Link(stack<Vertex>& verList)
{
	if (m_GameLogic.IsLink(selFirst, selSecond))
	{
		m_GameLogic.Clear(selFirst, selSecond);
		verList = m_GameLogic.GetVerList();
		return true;
	}
	return false;
}

bool CGameControl::isWin()
{
	return m_GameLogic.isBlank();
}