
// DataCenterDlg.h : ͷ�ļ�
//

#pragma once

class DataCenterSocket;
class PlaneSocket;

#include <map>

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
    map<int, PlaneSocket *> m_PlaneSockets;
    // vector<PlaneSocket *> m_FusionClients;

public:
    void AddPlaneSocket(int id, PlaneSocket *socket);
    void RemovePlaneSocket(int id);
};
