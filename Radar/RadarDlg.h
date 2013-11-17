#pragma once

#include "RadarClientProxy.h"

// CRadarDlg �Ի���

class CRadarDlg : public CDialog
{
	DECLARE_DYNAMIC(CRadarDlg)

public:
	CRadarDlg(RadarClientProxy &clientProxy, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRadarDlg();

// �Ի�������
	enum { IDD = IDD_RADAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
    RadarClientProxy &m_ClientProxy;
};
