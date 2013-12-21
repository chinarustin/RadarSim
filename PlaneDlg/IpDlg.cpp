// IpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../PlaneDlg/Resource.h"
#include "IpDlg.h"


// CIpDlg �Ի���

IMPLEMENT_DYNAMIC(CIpDlg, CDialog)

CIpDlg::CIpDlg(LPCWSTR hostName, int port, CWnd* pParent /*=NULL*/)
	: CDialog(CIpDlg::IDD, pParent)
    , m_HostName(hostName)
    , m_Port(port)
{

}

CIpDlg::~CIpDlg()
{
}

void CIpDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_IP, m_HostName);
    DDX_Text(pDX, IDC_PORT, m_Port);
}


BEGIN_MESSAGE_MAP(CIpDlg, CDialog)
END_MESSAGE_MAP()


// CIpDlg ��Ϣ�������
