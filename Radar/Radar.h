// Radar.h : Radar DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRadarApp
// �йش���ʵ�ֵ���Ϣ������� Radar.cpp
//

class CRadarApp : public CWinApp
{
public:
	CRadarApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
