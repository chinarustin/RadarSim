// InfraredDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SensorApp.h"
#include "EsmDlg.h"


// CInfraredDlg �Ի���

CEsmDlg::CEsmDlg(LPCWSTR title, Sensor &sensor, SensorClientProxy &clientProxy, CWnd* pParent /*=NULL*/)
	: CSensorDlg(title, sensor, clientProxy, pParent)
{
}

CEsmDlg::~CEsmDlg()
{
}

void CEsmDlg::CreateDlg(CEsmDlg &dlg)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    dlg.Create(IDD_SENSOR_DLG, GetDesktopWindow());
}

// CInfraredDlg ��Ϣ�������

BOOL CEsmDlg::OnInitDialog()
{
    CSensorDlg::OnInitDialog();

    return TRUE;
}
