
// PlaneDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "../Radar/Resource.h"
#include "../Radar/RadarCtrl.h"
#include "../Radar/RadarDlg.h"

#include "PlaneRadarProxy.h"

#include "Target.h"

#include <vector>

using namespace std;

// CPlaneDlg �Ի���
class CPlaneDlg : public CDialog
{
// ����
public:
	CPlaneDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PLANE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

    bool m_Initialized;
    void Resize();
    afx_msg void OnSize(UINT nType, int cx, int cy);

    bool m_ShowRadarDlg;
    Sensor m_Radar;
    CRadarCtrl m_RadarCtrl;
    PlaneRadarProxy m_PlaneRadarProxy;
    CRadarDlg m_RadarDlg;
    afx_msg void OnStnDblclickRadarCtrl();

    Plane m_Plane;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
