// Sensor.h : Sensor DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSensorApp
// �йش���ʵ�ֵ���Ϣ������� Sensor.cpp
//

class CCommonApp : public CWinApp
{
public:
	CCommonApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
