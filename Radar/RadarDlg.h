#pragma once

#include "Sensor.h"
#include "RadarClientProxy.h"
#include "RadarCtrl.h"
#include "afxwin.h"

// CRadarDlg �Ի���

class __declspec(dllexport) CRadarDlg : public CDialog
{
	DECLARE_DYNAMIC(CRadarDlg)

public:
	CRadarDlg(Sensor &radar, RadarClientProxy &clientProxy, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRadarDlg();

    static void CreateDlg(CRadarDlg &dlg);

// �Ի�������
	enum { IDD = IDD_RADAR_DLG };

protected:
    HICON m_hIcon;
    virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
    Sensor &m_Radar;
    RadarClientProxy &m_ClientProxy;
    CRadarCtrl m_Ctrl;
    afx_msg void OnClose();
    afx_msg void OnBnClickedRadarShowScanline();

    bool m_Initialized;
    void Resize();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedRadarEnable();
    afx_msg void OnEnChangeRadarMaxDis();
    CComboBox m_TargetId;
    afx_msg void OnBnClickedRadarShowTrack();
    afx_msg void OnCbnSelchangeRadarTargetId();
    CComboBox m_TargetColor;
    afx_msg void OnCbnSelchangeRadarTargetColor();
};
