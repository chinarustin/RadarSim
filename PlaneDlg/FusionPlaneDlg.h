
// FusionPlaneDlg.h : ͷ�ļ�
//

#pragma once
#include "PlaneDlg.h"

#include <afxmt.h>
#include <map>

using namespace std;

// CFusionPlaneDlg �Ի���
class CFusionPlaneDlg : public CPlaneDlg
{
// ����
public:
	CFusionPlaneDlg(LPCWSTR title, CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FUSION_PLANE_DIALOG };

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

    virtual void ConnectDataCenter();
    virtual void ConnectFusion(const CString &addr, int port);
    virtual void AddPlaneSocket();
    virtual void AddNoiseData(SocketPacketPair spp);
    virtual void SendNoiseData(NoiseDataPacket &packet);
    virtual void DoFusion();
    map<int, SocketPacketPair> m_NoiseDatas;
    virtual void ResetSockets();

    FusionSocket *m_FusionSocket;
    vector<PlaneSocket *> m_PlaneSockets;
    CCriticalSection m_Lock;
};
