
// FusionPlaneDlg.h : ͷ�ļ�
//

#pragma once
#include "PlaneDlg.h"

// CFusionPlaneDlg �Ի���
class CFusionPlaneDlg : public CPlaneDlg
{
// ����
public:
	CFusionPlaneDlg(LPCWSTR title, CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FUSION_PLANE_DIALOG };

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
