// DataCenterDlg.h : ͷ�ļ�
//

#pragma once

#include <afxmt.h>

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
    vector<Target> m_Targets;
    void GeneratePlaneClients();
    void GenerateTargets();
    void StartSim();
};
