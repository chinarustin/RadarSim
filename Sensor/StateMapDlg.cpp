// StateMapDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SensorApp.h"
#include "StateMapDlg.h"


// CStateMapDlg �Ի���

IMPLEMENT_DYNAMIC(CStateMapDlg, CDialog)

CStateMapDlg::CStateMapDlg(LPCWSTR title, StateMap &stateMap, CWnd* pParent /*=NULL*/)
	: CDialog(CStateMapDlg::IDD, pParent)
    , m_Title(title)
    , m_StateMap(stateMap)
    , m_Initialized(false)
    , m_Ctrl(stateMap)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CStateMapDlg::~CStateMapDlg()
{
}

void CStateMapDlg::CreateDlg(CStateMapDlg &dlg)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    dlg.Create(IDD_STATEMAP_DLG, GetDesktopWindow());
}

void CStateMapDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATEMAP, m_Ctrl);
}
BEGIN_MESSAGE_MAP(CStateMapDlg, CDialog)
END_MESSAGE_MAP()


// CStateMapDlg ��Ϣ�������

BOOL CStateMapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // TODO: �ڴ���Ӷ���ĳ�ʼ������
    m_Initialized = true;

    SetWindowTextW(m_Title);
    GetDlgItem(IDC_STATEMAP_GRP)->SetWindowTextW(m_Title);

    /*
    for (int i = 0; i < TargetColorLast; ++i)
    {
        m_TargetColor.InsertString(i, TargetColorNames[i]);
    }

    Resize();
    */

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CStateMapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStateMapDlg::Reset()
{
    m_Ctrl.Reset();

    UpdateData(FALSE);
}

void CStateMapDlg::AddTarget(Target &target)
{
}
