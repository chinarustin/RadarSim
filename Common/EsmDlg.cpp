// InfraredDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EsmDlg.h"


// CInfraredDlg 对话框

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

// CInfraredDlg 消息处理程序

BOOL CEsmDlg::OnInitDialog()
{
    CSensorDlg::OnInitDialog();

    return TRUE;
}
