
#include "afxdialogex.h"
#include "CGameControl.h"
#include "CGameLogic.h"
#include "global.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

private:
	int GameMode;//标识游戏模式
	CPoint m_GameRegionTop;  // 窗体地图左上角坐标
	CSize m_sizeElem;  // 每个图片的大小
	CRect m_GameRegion;  // 地图所在的矩形框

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon; //系统图标
	CDC m_dcMem;//内存DC
	CDC m_dcBG;//背景
	CDC m_dcEle;//元素
	CDC m_dcMask;//掩码

	static CString BGPath;//背景图片路径
	static CString ElementPath;//元素图片路径
	static CString MaskPath;//掩码图片路径

	//创建一个CGameControl对象
	CGameControl m_GameC;
	bool playing;  // 游戏是否进行中
	bool firstSelect;  // true表示为第一个点做准备


	DECLARE_MESSAGE_MAP()
public:
	void SetGameMode(int mode);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();
	afx_msg void OnClickedBtnStop();
	afx_msg void OnClickedBtnPrompt();
	afx_msg void OnClickedBtnReset();
private:
	//设置背景
	void InitBackground(void);
	void InitMode(int mode);
	void SetButton(bool start, bool stop, bool prompt, bool reset);
	void InitElement(CString ElementPath, CString MaskPath);
	void UpdateMap(void);
	// 绘制提示框架，可能用于提示用户可操作区域等
	void DrawTipFrame(int nRow, int nCol);
	// 绘制提示连线，可能用于显示两个元素连接路径等
	void DrawTipLine(stack<Vertex> verList);

public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);  //鼠标左键松开事件
};
