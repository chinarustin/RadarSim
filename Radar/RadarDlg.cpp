// RadarDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Radar.h"
#include "RadarDlg.h"


// CRadarDlg �Ի���

IMPLEMENT_DYNAMIC(CRadarDlg, CDialog)

CRadarDlg::CRadarDlg(RadarClientProxy &clientProxy, CWnd* pParent /*=NULL*/)
	: CDialog(CRadarDlg::IDD, pParent)
    , m_ClientProxy(clientProxy)
{

}

CRadarDlg::~CRadarDlg()
{
}

void CRadarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRadarDlg, CDialog)
END_MESSAGE_MAP()


// CRadarDlg ��Ϣ�������
