// DataCenterDlg.h : ͷ�ļ�
//

#pragma once

#include <afxmt.h>

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
    afx_msg LRESULT OnNetwork(WPARAM wParam, LPARAM lParam);
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
    CCriticalSection m_Lock;
};
