// NaviVcAlgoTest2.h : NaviVcAlgoTest2 DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNaviVcAlgoTest2App
// �йش���ʵ�ֵ���Ϣ������� NaviVcAlgoTest2.cpp
//

class CNaviVcAlgoTest2App : public CWinApp
{
public:
	CNaviVcAlgoTest2App();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
