// DataCenterDlg.h : ͷ�ļ�
//

#pragma once

#include <afxmt.h>

#include "../Common/StateMap.h"
#include "../Common/StateMapDlg.h"
#include "PlaneClient.h"
#include "TargetClient.h"

#include "CommonDlg.h"

class DataCenterSocket;
class PlaneSocket;

// CDataCenterDlg �Ի���
class CDataCenterDlg : public CCommonDlg
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
    bool m_FusionConnected;
    CString m_FusionAddr;
    int m_FusionPort;
    int m_ConnectedPlanes;
    void OnSubDlgClose(void *subDlg);

public:
    void AddPlaneSocket();
    void SetFusionAddr(const CString &addr, int port);
    void ResetSockets();
    void ResetCtrls();
    CCriticalSection m_Lock;
    afx_msg void OnBnClickedOk();

    PlaneClient m_PlaneClients[PLANE_COUNT];
    vector<TargetClient> m_TargetClients;

    void GeneratePlaneClients();
    void GenerateTargetClients();
    void GenerateTrueData();
    void AddFusionData(FusionDataPacket &packet);
    vector<FusionDataPacket> m_FusionDatas;

    void StartSim();
    void PauseSim();
    void ResumeSim();
    void FinishSim();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
    int m_CurrentFrame;
};
