
// DataCenterDlg.h : ͷ�ļ�
//

#pragma once

class ServerSocket;
class ClientSocket;

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

    ServerSocket *m_Socket;
    vector<ClientSocket *> m_PlaneClients;
    vector<ClientSocket *> m_FusionClients;

public:
    void OnAccept();
};
