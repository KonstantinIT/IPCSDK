
// HSAGRAccessTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHSAGRAccessTestApp:
// �йش����ʵ�֣������ HSAGRAccessTest.cpp
//

class CHSAGRAccessTestApp : public CWinApp
{
public:
	CHSAGRAccessTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHSAGRAccessTestApp theApp;