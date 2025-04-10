
#include "pch.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include "Resource.h"

//CGameDlg 对话框
CString CGameDlg::BGPath = _T("theme/picture/cxk_bg.bmp");
//元素图片路径
CString CGameDlg::ElementPath = _T("theme/picture/cxk_element.bmp");
//掩码图片路径
CString CGameDlg::MaskPath = _T("theme/picture/cxk_mask.bmp");

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_GameRegionTop.y = MAP_TOP;
	m_GameRegionTop.x = MAP_LEFT;
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	m_GameRegion.top = MAP_TOP;
	m_GameRegion.left = MAP_LEFT;
	m_GameRegion.right = MAP_LEFT + PIC_WIDTH * Cols;
	m_GameRegion.bottom = MAP_TOP + PIC_HEIGHT * Rows;

	playing = false;
	firstSelect = false;
	GameMode = 0;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CGameDlg::OnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_PROMPT, &CGameDlg::OnClickedBtnPrompt)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnClickedBtnReset)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


//设置背景
void CGameDlg::InitBackground(void) {
	//加载背景，留着后面更新地图的使用
	HANDLE Backbmp = ::LoadImageW(NULL, BGPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(Backbmp);

	//加载内存
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}

// CGameDlg 消息处理程序
BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);      // Set big icon
	SetIcon(m_hIcon, FALSE);     // Set small icon
	// 让弹出窗口作为应用程序窗口显示
	this->ModifyStyleEx(0, WS_EX_APPWINDOW);
	//设置背景
	InitBackground();
	//设置模式
	InitMode(this->GameMode);
	// 设置游戏窗口按钮的初始状态
	SetButton(TRUE, FALSE, FALSE, FALSE);

	//初始化加载水果元素和掩码
	InitElement(ElementPath, MaskPath);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

void CGameDlg::SetGameMode(int mode) {
	this->GameMode = mode;
}

void CGameDlg::InitMode(int mode) {
	if (mode == 1) {
		this->SetWindowTextW(_T("欢乐连连看--基本模式"));
	}
	else if (mode == 0) {
		this->SetWindowTextW(_T("欢乐连连看--休闲模式"));
	}
	else {
		this->SetWindowTextW(_T("欢乐连连看--关卡模式"));
	}
}


void CGameDlg::OnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化地图，地图用一个二维数组保存
	bool status = m_GameC.StartGame(Rows, Cols, PicNum);
	if (status)  //初始化地图成功
	{
		//设置状态
		playing = true;
		firstSelect = true;

		// 设置按钮
		SetButton(FALSE, TRUE, TRUE, TRUE);
		UpdateMap();//展示地图信息
	}
	else
		AfxMessageBox(L"行列和图片个数不匹配，无法绘制地图！", MB_OKCANCEL);
	InvalidateRect(FALSE);
}


void CGameDlg::OnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameDlg::OnClickedBtnPrompt()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGameDlg::OnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGameDlg::SetButton(bool start, bool stop, bool prompt, bool reset) {
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(start);
	this->GetDlgItem(IDC_BTN_STOP)->EnableWindow(stop);
	this->GetDlgItem(IDC_BTN_PROMPT)->EnableWindow(prompt);
	this->GetDlgItem(IDC_BTN_RESET)->EnableWindow(reset);
}

void CGameDlg::InitElement(CString ElementPath, CString MaskPath)
{
	CClientDC dc(this);
	HANDLE hBmp = ::LoadImageW(NULL, ElementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcEle.CreateCompatibleDC(&dc);
	m_dcEle.SelectObject(hBmp);  // 图片加载到m_dcEle中

	HANDLE hMask = ::LoadImageW(NULL, MaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);  // 图片掩码加载到m_dcMask中

}

//地图刷新
void CGameDlg::UpdateMap()
{
	// 读取地图的信息，并且在界面上显示
	int nTop = MAP_TOP;
	int nLeft = MAP_LEFT;
	int nElemW = PIC_WIDTH;
	int nElemH = PIC_HEIGHT;
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			int nElemVal = m_GameC.GetElement(i, j);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcEle, 0, nElemVal * nElemH, SRCAND);
		}
	}
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!playing) return;

	if (point.y<m_GameRegion.top || point.y>m_GameRegion.bottom || point.x<m_GameRegion.left || point.x>m_GameRegion.right)
	{
		//如果没有在地图的区域内，则不管
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//计算当前点的坐标
	int nRow = (point.y - m_GameRegionTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_GameRegionTop.x) / m_sizeElem.cx;
	if (nRow > Rows - 1 || nCol > Cols - 1) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_GameC.GetElement(nRow, nCol) == BLANK)
	{
		//如果这个区域没有图片，则返回
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (firstSelect) {
		//如果是此次点击是第一个点，则画边框，并进行设置
		DrawTipFrame(nRow, nCol);
		m_GameC.SetFirstPoint(nRow, nCol);
	}
	else
	{
		//如果此次点击是第二个点，怎画边框，并进行设置
		DrawTipFrame(nRow, nCol);
		m_GameC.SetSecondPoint(nRow, nCol);
		//同时判断两个点是否相连
		stack<Vertex> verList;
		bool bSuc = m_GameC.Link(verList);
		if (bSuc) {
			//如果相连，则画连接线路，
			DrawTipLine(verList);
			//重新加载地图背景，并更新最新地图
			m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
			UpdateMap();
		}
		Sleep(200);
		InvalidateRect(FALSE);
		if (bSuc && m_GameC.isWin())
		{
			MessageBox(TEXT("恭喜你！获胜！"));
			// 设置按钮
			SetButton(TRUE, FALSE, FALSE, FALSE);
			playing = false;
		}
	}
	firstSelect = !firstSelect;//第一次和第二次点击切换标志
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_GameRegionTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_GameRegionTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

void CGameDlg::DrawTipLine(stack<Vertex> verList)
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen* pOldPen = dc.SelectObject(&penLine);
	Vertex vTop;
	CPoint cp;
	if (!verList.empty())
	{
		vTop = verList.top();
		cp.x = m_GameRegionTop.x + vTop.col * m_sizeElem.cx + m_sizeElem.cx / 2;
		cp.y = m_GameRegionTop.y + vTop.row * m_sizeElem.cy + m_sizeElem.cy / 2;
		dc.MoveTo(cp);
		verList.pop();
		while (!verList.empty())
		{
			vTop = verList.top();
			cp.x = m_GameRegionTop.x + vTop.col * m_sizeElem.cx + m_sizeElem.cx / 2;
			cp.y = m_GameRegionTop.y + vTop.row * m_sizeElem.cy + m_sizeElem.cy / 2;
			dc.LineTo(cp);
			verList.pop();
		}
	}
	dc.SelectObject(pOldPen);
}