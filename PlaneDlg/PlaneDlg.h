
// PlaneDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "../Sensor/Resource.h"
#include "../Sensor/SensorCtrl.h"
#include "../Sensor/SensorDlg.h"

#include "PlaneRadarProxy.h"
#include "PlaneEsmProxy.h"

#include "Target.h"

#include <vector>

using namespace std;

// CPlaneDlg �Ի���
class CPlaneDlg : public CDialog
{
// ����
public:
	CPlaneDlg(LPCWSTR title, CWnd* pParent = NULL);	// ��׼���캯��

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
    CString m_Title;
    void Resize();
    afx_msg void OnSize(UINT nType, int cx, int cy);

    bool m_ShowRadarDlg;
    Sensor m_Radar;
    CSensorCtrl m_RadarCtrl;
    PlaneRadarProxy m_PlaneRadarProxy;
    CSensorDlg m_RadarDlg;
    afx_msg void OnStnDblclickRadarCtrl();

    bool m_ShowEsmDlg;
    Sensor m_Esm;
    CSensorCtrl m_EsmCtrl;
    PlaneEsmProxy m_PlaneEsmProxy;
    CSensorDlg m_EsmDlg;
    afx_msg void OnStnDblclickEsmCtrl();

    Plane m_Plane;
    afx_msg void OnTimer(UINT_PTR nIDEvent);

    void Reset();
    void AddTarget(Target &target);
};
