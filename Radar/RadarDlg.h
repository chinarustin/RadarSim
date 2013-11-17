#pragma once

#include "RadarParam.h"
#include "RadarClientProxy.h"
#include "RadarCtrl.h"

// CRadarDlg �Ի���

class __declspec(dllexport) CRadarDlg : public CDialog
{
	DECLARE_DYNAMIC(CRadarDlg)

public:
	CRadarDlg(RadarParam &param, RadarClientProxy &clientProxy, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRadarDlg();

    static void CreateDlg(CRadarDlg &dlg);

// �Ի�������
	enum { IDD = IDD_RADAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
    RadarParam &m_Param;
    RadarClientProxy &m_ClientProxy;
    CRadarCtrl m_Ctrl;
    afx_msg void OnClose();
};
