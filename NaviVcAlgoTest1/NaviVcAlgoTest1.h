// NaviVcAlgoTest1.h : NaviVcAlgoTest1 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNaviVcAlgoTest1App
// �йش���ʵ�ֵ���Ϣ������� NaviVcAlgoTest1.cpp
//

class CNaviVcAlgoTest1App : public CWinApp
{
public:
	CNaviVcAlgoTest1App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
