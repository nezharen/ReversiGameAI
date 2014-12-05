
// ReversiGameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReversiGame.h"
#include "ReversiGameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReversiGameDlg 对话框

bool getPosition(CPoint point, int &x, int &y);
UINT __cdecl whiteGo(LPVOID pParam);

CReversiGameDlg::CReversiGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReversiGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReversiGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_START, m_button_start);
	DDX_Control(pDX, IDCANCEL, m_button_exit);
	DDX_Control(pDX, ID_MAP, m_map_painter);
	DDX_Control(pDX, IDC_EDIT_STATE, m_edit_state);
	DDX_Control(pDX, IDC_EDIT_BLACK_NUMBER, m_edit_black_number);
	DDX_Control(pDX, IDC_EDIT_WHITE_NUMBER, m_edit_white_number);
}

BEGIN_MESSAGE_MAP(CReversiGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_START, &CReversiGameDlg::OnBnClickedStart)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CReversiGameDlg 消息处理程序

BOOL CReversiGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	MoveWindow(0, 0, 560, 650);
	m_button_start.MoveWindow(10, 10, 100, 25);
	m_button_exit.MoveWindow(130, 10, 100, 25);
	m_edit_state.MoveWindow(250, 10, 280, 25);
	m_edit_black_number.MoveWindow(10, 45, 250, 25);
	m_edit_white_number.MoveWindow(280, 45, 250, 25);
	m_map_painter.MoveWindow(10, 80, 520, 520);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReversiGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	CString s;
	int sum = -1;
	if ((m_data.m_state == STATE_BLACK_GO) || (m_data.m_state == STATE_WHITE_GO))
		if (m_data.m_number[MAP_BLACK] + m_data.m_number[MAP_WHITE] < 64)
			sum = 0;
	switch (m_data.m_state)
	{
	case STATE_NOT_START:
		m_edit_state.SetWindowText(_T("游戏未开始。"));
		break;
	case STATE_BLACK_GO:
		m_edit_state.SetWindowText(_T("请黑方（玩家）下棋。"));
		break;
	case STATE_WHITE_GO:
		m_edit_state.SetWindowText(_T("请白方（电脑）下棋。"));
		break;
	case STATE_BLACK_WIN:
		m_edit_state.SetWindowText(_T("黑方（玩家）获胜。"));
		break;
	case STATE_WHITE_WIN:
		m_edit_state.SetWindowText(_T("白方（电脑）获胜。"));
		break;
	case STATE_PEACE:
		m_edit_state.SetWindowText(_T("黑白双方和棋。"));
		break;
	}
	s.Format(_T("黑方（玩家）棋子数：%d"), m_data.m_number[MAP_BLACK]);
	m_edit_black_number.SetWindowText(s);
	s.Format(_T("白方（电脑）棋子数：%d"), m_data.m_number[MAP_WHITE]);
	m_edit_white_number.SetWindowText(s);

	CPaintDC dc(&m_map_painter);
	HGDIOBJ oldPen = dc.SelectObject(GetStockObject(NULL_PEN));
	HGDIOBJ oldBrush = dc.SelectObject(GetStockObject(DC_BRUSH));
	COLORREF oldBrushColor = dc.SetDCBrushColor(RGB(166, 83, 0));
	dc.Rectangle(0, 0, 520, 520);

	int oldBkMode = dc.SetBkMode(TRANSPARENT);
	COLORREF oldTextColor = dc.SetTextColor(RGB(255, 255, 142));
	for (int i = 0; i < 8; i++)
	{
		s.Format(_T("%c"), 'A' + i);
		dc.TextOut(45 + 60 * i, 0, s);
		s.Format(_T("%d"), i + 1);
		dc.TextOut(10, 45 + 60 * i, s);
	}
	dc.SetTextColor(oldTextColor);
	dc.SetBkMode(oldBkMode);

	dc.SelectObject(GetStockObject(DC_PEN));
	COLORREF oldPenColor = dc.SetDCPenColor(RGB(255, 255, 200));
	dc.SetDCBrushColor(RGB(34, 177, 76));
	CPen pen;
	pen.CreatePen(0, 3, RGB(255, 128, 0));
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if ((m_data.m_last_put.x == i) && (m_data.m_last_put.y == j))
				dc.SelectObject(&pen);
			dc.Rectangle(20 + 60 * i, 20 + 60 * j, 80 + 60 * i, 80 + 60 * j);
			if ((m_data.m_last_put.x == i) && (m_data.m_last_put.y == j))
			{
				dc.SelectObject(GetStockObject(DC_PEN));
				dc.SetDCPenColor(RGB(255, 255, 200));
			}
			if (m_data.m_map[i][j] == MAP_NULL)
				if (m_data.m_state == STATE_BLACK_GO)
				{
					if (m_data.ableToPut(i, j, MAP_BLACK))
					{
						dc.SetDCPenColor(RGB(0, 0, 0));
						dc.SetDCBrushColor(RGB(255, 0, 0));
						dc.Ellipse(45 + 60 * i, 45 + 60 * j, 55 + 60 * i, 55 + 60 * j);
						dc.SetDCBrushColor(RGB(34, 177, 76));
						dc.SetDCPenColor(RGB(255, 255, 200));
						sum++;
					}
				}
				else
					if (m_data.m_state == STATE_WHITE_GO)
					{
						if (m_data.ableToPut(i, j, MAP_WHITE))
						{
							dc.SetDCPenColor(RGB(0, 0, 0));
							dc.SetDCBrushColor(RGB(255, 0, 0));
							dc.Ellipse(45 + 60 * i, 45 + 60 * j, 55 + 60 * i, 55 + 60 * j);
							dc.SetDCBrushColor(RGB(34, 177, 76));
							dc.SetDCPenColor(RGB(255, 255, 200));
							sum++;
						}
					}
			if (m_data.m_map[i][j] == MAP_BLACK)
			{
				dc.SetDCPenColor(RGB(0, 0, 0));
				dc.SetDCBrushColor(RGB(0, 0, 0));
				dc.Ellipse(25 + 60 * i, 25 + 60 * j, 75 + 60 * i, 75 + 60 * j);
				dc.SetDCBrushColor(RGB(34, 177, 76));
				dc.SetDCPenColor(RGB(255, 255, 200));
			}
			if (m_data.m_map[i][j] == MAP_WHITE)
			{
				dc.SetDCPenColor(RGB(255, 255, 255));
				dc.SetDCBrushColor(RGB(255, 255, 255));
				dc.Ellipse(25 + 60 * i, 25 + 60 * j, 75 + 60 * i, 75 + 60 * j);
				dc.SetDCBrushColor(RGB(34, 177, 76));
				dc.SetDCPenColor(RGB(255, 255, 200));
			}
		}
	dc.SetDCBrushColor(oldBrushColor);
	dc.SelectObject(oldBrush);
	dc.SetDCPenColor(oldPenColor);
	dc.SelectObject(oldPen);

	if (sum == 0)
	{
		if ((m_data.m_state == STATE_BLACK_GO))
		{
			MessageBox(_T("白方破阵，黑方此轮不能下棋。"), _T("黑白棋"));
			m_data.m_state = STATE_WHITE_GO;
		}
		else
			if ((m_data.m_state == STATE_WHITE_GO))
			{
				MessageBox(_T("黑方破阵，白方此轮不能下棋。"), _T("黑白棋"));
				m_data.m_state = STATE_BLACK_GO;
			}
		Invalidate();
	}
	if (m_data.m_state == STATE_WHITE_GO)
		AfxBeginThread(whiteGo, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CReversiGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReversiGameDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	m_data.initiateMap();
	m_data.m_state = STATE_BLACK_GO;
	Invalidate();
}


void CReversiGameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ((m_data.m_state != STATE_BLACK_GO))
	{
		if (m_data.m_state == STATE_NOT_START)
			MessageBox(_T("游戏未开始。"), _T("黑白棋"));
		else
			if (m_data.m_state != STATE_WHITE_GO)
				MessageBox(_T("游戏已结束。"), _T("黑白棋"));
		return;
	}
	CPoint p = point;
	int tx, ty;
	ClientToScreen(&p);
	m_map_painter.ScreenToClient(&p);
	if ((p.x < 20) || (p.x > 500) || (p.y < 20) || (p.y > 500))
		return;
	if (!getPosition(p, tx, ty))
		return;
	if (m_data.ableToPut(tx, ty, MAP_BLACK))
	{
		m_data.put(tx, ty, MAP_BLACK);
		m_data.m_last_put.x = tx;
		m_data.m_last_put.y = ty;
		m_data.m_state = STATE_WHITE_GO;
		Invalidate();
		if (m_data.checkEnd())
		{
			if (m_data.m_state == STATE_BLACK_WIN)
				MessageBox(_T("黑方（玩家）获胜！"), _T("黑白棋"));
			else
				if (m_data.m_state == STATE_WHITE_WIN)
					MessageBox(_T("白方（电脑）获胜！"), _T("黑白棋"));
				else
					MessageBox(_T("黑白双方和棋。"), _T("黑白棋"));
		}
	}
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

UINT __cdecl whiteGo(LPVOID pParam)
{
	CReversiGameDlg *pDlg = (CReversiGameDlg *)pParam;
	Sleep(1000);
	int tx_good[16] = {0, 7, 0, 7, 2, 5, 2, 5, 2, 5, 0, 0, 7, 7, 2, 5};
	int ty_good[16] = {0, 0, 7, 7, 2, 2, 5, 5, 0, 0, 2, 5, 2, 5, 7, 7};
	int tx_bad[20] = {2, 1, 1, 2, 5, 6, 6, 5, 1, 6, 0, 0, 7, 7, 1, 6, 1, 1, 6, 6};
	int ty_bad[20] = {1, 2, 5, 6, 6, 5, 2, 1, 0, 0, 1, 6, 1, 6, 7, 7, 1, 6, 1, 6};

	for (int i = 0; i < 16; i++)
		if (pDlg->m_data.ableToPut(tx_good[i], ty_good[i], MAP_WHITE))
		{
			pDlg->m_data.put(tx_good[i], ty_good[i], MAP_WHITE);
			pDlg->m_data.m_last_put.x = tx_good[i];
			pDlg->m_data.m_last_put.y = ty_good[i];
			goto loop1;
		}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 20; k++)
				if ((tx_bad[k] == i) && (ty_bad[k] == j))
					goto loop2;
			if (pDlg->m_data.ableToPut(i, j, MAP_WHITE))
			{
				pDlg->m_data.put(i, j, MAP_WHITE);
				pDlg->m_data.m_last_put.x = i;
				pDlg->m_data.m_last_put.y = j;
				goto loop1;
			}
loop2:;
		}
	for (int i = 0; i < 20; i++)
		if (pDlg->m_data.ableToPut(tx_bad[i], ty_bad[i], MAP_WHITE))
		{
			pDlg->m_data.put(tx_bad[i], ty_bad[i], MAP_WHITE);
			pDlg->m_data.m_last_put.x = tx_bad[i];
			pDlg->m_data.m_last_put.y = ty_bad[i];
		}

loop1:;
	pDlg->m_data.m_state = STATE_BLACK_GO;
	pDlg->Invalidate();
	if (pDlg->m_data.checkEnd())
	{
		if (pDlg->m_data.m_state == STATE_BLACK_WIN)
			pDlg->MessageBox(_T("黑方（玩家）获胜！"), _T("黑白棋"));
		else
			if (pDlg->m_data.m_state == STATE_WHITE_WIN)
				pDlg->MessageBox(_T("白方（电脑）获胜！"), _T("黑白棋"));
			else
				pDlg->MessageBox(_T("黑白双方和棋。"), _T("黑白棋"));
	}
	return 0;
}

bool getPosition(CPoint point, int &x, int &y)
{
	point.x -= 20;
	if (point.x % 60 == 0)
		return false;
	point.y -= 20;
	if (point.y % 60 == 0)
		return false;
	x = point.x / 60;
	y = point.y / 60;
	return true;
}
