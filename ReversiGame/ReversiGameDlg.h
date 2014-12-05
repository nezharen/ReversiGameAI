
// ReversiGameDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CReversiGameDlg �Ի���
class CReversiGameDlg : public CDialogEx
{
// ����
public:
	CReversiGameDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_REVERSIGAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
