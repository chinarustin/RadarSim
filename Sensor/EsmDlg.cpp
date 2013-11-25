// InfraredDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sensor.h"
#include "InfraredDlg.h"


// CInfraredDlg �Ի���

CInfraredDlg::CInfraredDlg(LPCWSTR title, Sensor &sensor, SensorClientProxy &clientProxy, CWnd* pParent /*=NULL*/)
	: CSensorDlg(title, sensor, clientProxy, pParent)
{
    delete m_Ctrl;
    m_Ctrl = new CInfraredCtrl(sensor);
    m_Sensor.m_ShowScanline = FALSE;
}

CInfraredDlg::~CInfraredDlg()
{
}

void CInfraredDlg::CreateDlg(CInfraredDlg &dlg)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    dlg.Create(IDD_SENSOR_DLG, GetDesktopWindow());
}

void CInfraredDlg::DoDataExchange(CDataExchange* pDX)
{
    CSensorDlg::DoDataExchange(pDX);
    // DDX_Control(pDX, IDC_INFRARED, m_Ctrl);
}

// CInfraredDlg ��Ϣ�������

BOOL CInfraredDlg::OnInitDialog()
{
    CSensorDlg::OnInitDialog();
    GetDlgItem(IDC_SENSOR_SHOW_SCANLINE)->EnableWindow(FALSE);

    return TRUE;
}
