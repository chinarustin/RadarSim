#pragma once


// CInfraredDlg �Ի���

#include "SensorDlg.h"

#include "InfraredCtrl.h"

class __declspec(dllexport) CInfraredDlg : public CSensorDlg
{
public:
	CInfraredDlg(LPCWSTR title, Sensor &sensor, SensorClientProxy &clientProxy, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInfraredDlg();

    static void CreateDlg(CInfraredDlg &dlg);

protected:
    virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
};
