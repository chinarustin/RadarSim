
// DataCenter.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDataCenterApp:
// �йش����ʵ�֣������ DataCenter.cpp
//

class CDataCenterApp : public CWinAppEx
{
public:
	CDataCenterApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDataCenterApp theApp;