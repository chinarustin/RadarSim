
// Plane.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPlaneApp:
// �йش����ʵ�֣������ Plane.cpp
//

class CPlaneApp : public CWinAppEx
{
public:
	CPlaneApp();
    virtual ~CPlaneApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPlaneApp theApp;