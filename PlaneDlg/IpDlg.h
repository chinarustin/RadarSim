#pragma once


// CIpDlg �Ի���

class CIpDlg : public CDialog
{
	DECLARE_DYNAMIC(CIpDlg)

public:
	CIpDlg(LPCWSTR hostName, int port, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIpDlg();

// �Ի�������
	enum { IDD = IDD_IP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CString m_HostName;
    int m_Port;
};
