
// ReversiGame.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReversiGameApp:
// �йش����ʵ�֣������ ReversiGame.cpp
//

class CReversiGameApp : public CWinApp
{
public:
	CReversiGameApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReversiGameApp theApp;