// InfraredDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EsmDlg.h"


// CInfraredDlg �Ի���

CEsmDlg::CEsmDlg(LPCWSTR title, Sensor &sensor, CCommonDlg *dlg, CWnd* pParent /*=NULL*/)
	: CSensorDlg(title, sensor, dlg, pParent)
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
