#pragma once


// CInfraredDlg �Ի���

#include "SensorDlg.h"

#include "EsmCtrl.h"

class __declspec(dllexport) CEsmDlg : public CSensorDlg
{
public:
	CEsmDlg(LPCWSTR title, Sensor &sensor, SensorClientProxy &clientProxy, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEsmDlg();

    static void CreateDlg(CEsmDlg &dlg);

protected:
    virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
};
