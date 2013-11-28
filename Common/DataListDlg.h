#pragma once

#include "Common.h"

#include "DataList.h"
#include "DataListCtrl.h"
#include "CommonDlg.h"

// CDataListDlg �Ի���

class __declspec(dllexport) CDataListDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataListDlg)

public:
	CDataListDlg(LPCWSTR title, DataList &dataList, CCommonDlg *dlg, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDataListDlg();

    static void CreateDlg(CDataListDlg &dlg);

// �Ի�������
	enum { IDD = IDD_DATALIST_DLG };

protected:
    HICON m_hIcon;
    virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
    CString m_Title;
    DataList &m_DataList;
    CCommonDlg *m_Dlg;
    CDataListCtrl *m_Ctrl;
    afx_msg void OnClose();

    bool m_Initialized;
    virtual void Resize();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    CComboBox m_TargetId;
    afx_msg void OnCbnSelchangeSensorTargetId();
    CComboBox m_TargetColor;
    afx_msg void OnCbnSelchangeSensorTargetColor();

    void Reset();
    void AddTarget(Target &target);
};