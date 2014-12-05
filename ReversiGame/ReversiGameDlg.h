
// ReversiGameDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CReversiGameDlg 对话框
class CReversiGameDlg : public CDialogEx
{
// 构造
public:
	CReversiGameDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_REVERSIGAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_button_start;
	CButton m_button_exit;
	CStatic m_map_painter;
	CEdit m_edit_state;
	CEdit m_edit_black_number;
	CEdit m_edit_white_number;
	ReversiGameDoc m_data;
	afx_msg void OnBnClickedStart();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
