
// PlaneDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../PlaneDlg/Resource.h"
#include "PlaneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneDlg �Ի���




CPlaneDlg::CPlaneDlg(LPCWSTR title, CWnd* pParent /*=NULL*/)
	: CDialog(CPlaneDlg::IDD, pParent)
    , m_Title(title)
    , m_Initialized(false)
    , m_ShowRadarDlg(true)
    , m_Radar(Sensor::SensorTypeSource, m_Plane)
    , m_RadarCtrl(m_Radar)
    , m_PlaneRadarProxy(*this)
    , m_RadarDlg(TEXT("�״�"), m_Radar, m_PlaneRadarProxy)
    , m_ShowEsmDlg(true)
    , m_Esm(Sensor::SensorTypeNonSource, m_Plane)
    , m_EsmCtrl(m_Esm)
    , m_PlaneEsmProxy(*this)
    , m_EsmDlg(TEXT("ESM"), m_Esm, m_PlaneEsmProxy)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPlaneDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RADAR_CTRL, m_RadarCtrl);
    DDX_Control(pDX, IDC_ESM_CTRL, m_EsmCtrl);
}

BEGIN_MESSAGE_MAP(CPlaneDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_WM_SIZE()
    ON_STN_DBLCLK(IDC_RADAR_CTRL, &CPlaneDlg::OnStnDblclickRadarCtrl)
    ON_STN_DBLCLK(IDC_ESM_CTRL, &CPlaneDlg::OnStnDblclickEsmCtrl)
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CPlaneDlg ��Ϣ�������

BOOL CPlaneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // TODO: �ڴ���Ӷ���ĳ�ʼ������
    m_Initialized = true;

    SetWindowTextW(m_Title);

    Resize();

    CSensorDlg::CreateDlg(m_RadarDlg);
    if (m_ShowRadarDlg)
    {
        m_RadarDlg.ShowWindow(SW_SHOW);
    }
    {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
    }

    CSensorDlg::CreateDlg(m_EsmDlg);
    if (m_ShowEsmDlg)
    {
        m_EsmDlg.ShowWindow(SW_SHOW);
    }
    {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
    }

    // ��ʼ���һ���Ŀ��
    Target target0, target1;

    target0.m_Id = 3;
    target1.m_Id = 4;

    AddTarget(target0);
    AddTarget(target1);

    // Debug�õ�Timer
    SetTimer(0, 800, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPlaneDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPlaneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPlaneDlg::Resize()
{
    RECT rect;
    GetClientRect(&rect);

    // Resize Radar.
    int left = rect.left + PAD, width = (rect.right - rect.left) / 2 - PAD * 2, top = rect.top + PAD, height = (rect.bottom - rect.top) / 2 - PAD * 2;
    if (width > height)
    {
        width = height;
    }
    GetDlgItem(IDC_RADAR_CTRL_GRP)->MoveWindow(left, top, width, height);

    left = left + PAD;
    width = width - PAD *2;
    top = top + PAD * 2;
    height = height - PAD * 3;
    m_RadarCtrl.MoveWindow(left, top, width, height);

    // Resize ESM.
    left = rect.left + PAD;
    width = (rect.right - rect.left) / 2 - PAD * 2;
    top = (rect.bottom - rect.top) / 2 + PAD;
    height = (rect.bottom - rect.top) / 2 - PAD * 2;
    if (width > height)
    {
        width = height;
    }
    GetDlgItem(IDC_ESM_CTRL_GRP)->MoveWindow(left, top, width, height);

    left = left + PAD;
    width = width - PAD *2;
    top = top + PAD * 2;
    height = height - PAD * 3;
    m_EsmCtrl.MoveWindow(left, top, width, height);
}

void CPlaneDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: �ڴ˴������Ϣ����������
    if (m_Initialized)
    {
        Resize();
    }
}

void CPlaneDlg::OnStnDblclickRadarCtrl()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if (m_ShowRadarDlg)
    {
        m_RadarDlg.ShowWindow(SW_HIDE);
        m_ShowRadarDlg = false;
    }
    else
    {
        m_RadarDlg.ShowWindow(SW_SHOW);
        m_ShowRadarDlg = true;
    }
}

void CPlaneDlg::OnStnDblclickEsmCtrl()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if (m_ShowEsmDlg)
    {
        m_EsmDlg.ShowWindow(SW_HIDE);
        m_ShowEsmDlg = false;
    }
    else
    {
        m_EsmDlg.ShowWindow(SW_SHOW);
        m_ShowEsmDlg = true;
    }
}
void CPlaneDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    CDialog::OnTimer(nIDEvent);

    static int count = 0;

    if (++count <= 200)
    {
        m_Plane.m_Targets[0].MoveTo(m_Plane.m_Targets[0].m_Position + Position(2, 3, 4));
        m_Plane.m_Targets[1].MoveTo(m_Plane.m_Targets[1].m_Position + Position(3, 5, 4));

        m_Plane.MoveTo(m_Plane.m_Position + Position(1, 1, 1));

        m_RadarCtrl.DrawTargets();
        m_RadarCtrl.BlendAll();
        m_RadarCtrl.Invalidate();

        m_RadarDlg.m_Ctrl.DrawTargets();
        m_RadarDlg.m_Ctrl.BlendAll();
        m_RadarDlg.m_Ctrl.Invalidate();


        m_EsmCtrl.DrawTargets();
        m_EsmCtrl.BlendAll();
        m_EsmCtrl.Invalidate();

        m_EsmDlg.m_Ctrl.DrawTargets();
        m_EsmDlg.m_Ctrl.BlendAll();
        m_EsmDlg.m_Ctrl.Invalidate();
    }
    else
    {
        Reset();
    }
}

void CPlaneDlg::Reset()
{
    m_Plane.Reset();

    m_Radar.Reset();
    m_Esm.Reset();
    m_RadarCtrl.Reset();
    m_EsmCtrl.Reset();
    m_RadarDlg.Reset();
    m_EsmDlg.Reset();
}

void CPlaneDlg::AddTarget(Target &target)
{
    m_Radar.AddTarget(target);
    m_Esm.AddTarget(target);

    m_Plane.AddTarget(target);

    m_RadarCtrl.AddTarget(target);
    m_EsmCtrl.AddTarget(target);

    m_RadarDlg.AddTarget(target);
    m_EsmDlg.AddTarget(target);
}
