// DataCenterDlg.h : ͷ�ļ�
//

#pragma once

#include <afxmt.h>

#include "../Common/StateMap.h"
#include "../Common/StateMapDlg.h"
#include "PlaneClient.h"

class DataCenterSocket;
class PlaneSocket;

// CDataCenterDlg �Ի���
class CDataCenterDlg : public CDialog
{
// ����
public:
	CDataCenterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DATACENTER_DIALOG };

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

    bool m_ShowStateMapDlg;
    StateMap m_StateMap;
    CStateMapDlg m_StateMapDlg;

    DataCenterSocket *m_DataCenterSocket;
    vector<PlaneSocket *> m_PlaneSockets;
    bool m_FusionConnected;
    CString m_FusionAddr;
    int m_FusionPort;

public:
    void AddPlaneSocket();
    void SetFusionAddr(const CString &addr, int port);
    void ResetSockets();
    void ResetCtrls();
    CCriticalSection m_Lock;
    afx_msg void OnBnClickedOk();
    PlaneClient m_PlaneClients[PLANE_COUNT];
    Target m_Targets[TARGET_COUNT];
    void GeneratePlaneClients();
    void GenerateTargets();
    void GenerateSimData();
    Path m_PlaneDatas[PLANE_COUNT];
    Path m_TargetDatas[TARGET_COUNT];
    void StartSim();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
