
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
    , m_ShowInfraredDlg(true)
    , m_Infrared(Sensor::SensorTypeNonSource, m_Plane)
    , m_InfraredCtrl(m_Infrared)
    , m_PlaneInfraredProxy(*this)
    , m_InfraredDlg(TEXT("����"), m_Infrared, m_PlaneInfraredProxy)
    , m_ShowDataListDlg(true)
    , m_DataList(m_Radar, m_Esm, m_Infrared, m_Plane)
    , m_DataListCtrl(m_DataList)
    , m_PlaneDataListProxy(*this)
    , m_DataListDlg(TEXT("�����б�"), m_DataList, m_PlaneDataListProxy)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    ResetSensors();
}

void CPlaneDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RADAR_CTRL, m_RadarCtrl);
    DDX_Control(pDX, IDC_ESM_CTRL, m_EsmCtrl);
    DDX_Control(pDX, IDC_INFRARED_CTRL, m_InfraredCtrl);
    DDX_Control(pDX, IDC_DATALIST_CTRL, m_DataListCtrl);
}

BEGIN_MESSAGE_MAP(CPlaneDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_WM_SIZE()
    ON_STN_DBLCLK(IDC_RADAR_CTRL, &CPlaneDlg::OnStnDblclickRadarCtrl)
    ON_STN_DBLCLK(IDC_ESM_CTRL, &CPlaneDlg::OnStnDblclickEsmCtrl)
    ON_STN_DBLCLK(IDC_INFRARED_CTRL, &CPlaneDlg::OnStnDblclickInfraredCtrl)
    ON_WM_TIMER()
    ON_NOTIFY(NM_DBLCLK, IDC_DATALIST_CTRL, &CPlaneDlg::OnNMDblclkDatalistCtrl)
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

    CInfraredDlg::CreateDlg(m_InfraredDlg);
    if (m_ShowInfraredDlg)
    {
        m_InfraredDlg.ShowWindow(SW_SHOW);
    }
    {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
    }

    CDataListDlg::CreateDlg(m_DataListDlg);
    if (m_ShowDataListDlg)
    {
        m_DataListDlg.ShowWindow(SW_SHOW);
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

    // Resize DataList.
    left = left + width + PAD + PAD * 2;
    width = rect.right - PAD - left;
    top = rect.top + PAD;
    height = (rect.bottom - rect.top) / 2 - PAD * 2;
    GetDlgItem(IDC_DATALIST_CTRL_GRP)->MoveWindow(left, top, width, height);

    left = left + PAD;
    width = width - PAD * 2;
    top = top + PAD * 2;
    height = height - PAD * 3;
    m_DataListCtrl.MoveWindow(left, top, width, height);

    // Resize Infrared.
    left = left - PAD;
    width = width + PAD * 2;
    top = (rect.bottom - rect.top) / 2 + PAD;
    height = (rect.bottom - rect.top) / 2 - PAD * 2;
    GetDlgItem(IDC_INFRARED_CTRL_GRP)->MoveWindow(left, top, width, height);

    left = left + PAD;
    width = width - PAD * 2;
    top = top + PAD * 2;
    height = height - PAD * 3;
    m_InfraredCtrl.MoveWindow(left, top, width, height);
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

void CPlaneDlg::OnStnDblclickInfraredCtrl()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if (m_ShowInfraredDlg)
    {
        m_InfraredDlg.ShowWindow(SW_HIDE);
        m_ShowInfraredDlg = false;
    }
    else
    {
        m_InfraredDlg.ShowWindow(SW_SHOW);
        m_ShowInfraredDlg = true;
    }
}

void CPlaneDlg::OnNMDblclkDatalistCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    // pResult = 0;
    if (m_ShowDataListDlg)
    {
        m_DataListDlg.ShowWindow(SW_HIDE);
        m_ShowDataListDlg = false;
    }
    else
    {
        m_DataListDlg.ShowWindow(SW_SHOW);
        m_ShowDataListDlg = true;
    }
}

void CPlaneDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    CDialog::OnTimer(nIDEvent);

    static int count = 0;

    if (++count <= 500)
    {
#if 1
        m_Targets[0].m_Position = m_Targets[0].m_Position + Position(rand() % 3, rand() % 3, rand() % 3);
        m_Targets[1].m_Position = m_Targets[1].m_Position + Position(rand() % 3, rand() % 3, rand() % 3);

        m_Plane.m_Position = m_Plane.m_Position + Position(rand() % 3, rand() % 3, rand() % 3);
#else
        m_Targets[0].m_Position = m_Targets[0].m_Position + Position(0, 1, -1);
        m_Targets[1].m_Position = m_Targets[1].m_Position + Position(-1, 1, 1);
#endif

        m_Plane.m_Position = m_Plane.m_Position + Position(0, 0, 0);

        Position rel0 = m_Targets[0].m_Position - m_Plane.m_Position;
        Position rel1 = m_Targets[1].m_Position - m_Plane.m_Position;

        m_Radar.AddTargetData(0, rel0);
        m_Esm.AddTargetData(0, rel0);
        m_Infrared.AddTargetData(0, rel0);
        m_Radar.AddTargetData(1, rel1);
        m_Esm.AddTargetData(1, rel1);
        m_Infrared.AddTargetData(1, rel1);

        m_RadarCtrl.DrawTargets();
        m_RadarCtrl.BlendAll();
        m_RadarCtrl.Invalidate();

        m_RadarDlg.m_Ctrl->DrawTargets();
        m_RadarDlg.m_Ctrl->BlendAll();
        m_RadarDlg.m_Ctrl->Invalidate();

        m_EsmCtrl.DrawTargets();
        m_EsmCtrl.BlendAll();
        m_EsmCtrl.Invalidate();

        m_EsmDlg.m_Ctrl->DrawTargets();
        m_EsmDlg.m_Ctrl->BlendAll();
        m_EsmDlg.m_Ctrl->Invalidate();

        m_InfraredCtrl.DrawTargets();
        m_InfraredCtrl.BlendAll();
        m_InfraredCtrl.Invalidate();

        m_InfraredDlg.m_Ctrl->DrawTargets();
        m_InfraredDlg.m_Ctrl->BlendAll();
        m_InfraredDlg.m_Ctrl->Invalidate();

        m_DataListCtrl.AddTargetData();
        m_DataListDlg.m_Ctrl->AddTargetData();
    }
    else
    {
        KillTimer(0);
        Reset();
    }
}

void CPlaneDlg::Reset()
{
    m_Plane.Reset();

    ResetSensors();

    m_RadarCtrl.Reset();
    m_EsmCtrl.Reset();
    m_InfraredCtrl.Reset();
    m_DataListCtrl.Reset();

    m_RadarDlg.Reset();
    m_EsmDlg.Reset();
    m_InfraredDlg.Reset();
    m_DataListDlg.Reset();
}

void CPlaneDlg::ResetSensors()
{
    m_Radar.Reset();
    m_Esm.Reset();
    m_Infrared.Reset();
    m_DataList.Reset();

    m_Esm.m_ThetaRangeColor = Color::Red;
    m_Esm.m_ShowHeight = FALSE;
    m_Infrared.m_ShowScanline = FALSE;
    m_Infrared.m_ShowThetaRange = FALSE;
    m_Infrared.m_ThetaRangeColor = Color::Yellow;
    m_Infrared.m_ShowHeight = FALSE;
}

void CPlaneDlg::AddTarget(Target &target)
{
    m_Targets.push_back(target);

    m_Radar.AddTarget(target);
    m_Esm.AddTarget(target);
    m_Infrared.AddTarget(target);
    m_DataList.AddTarget(target);

    m_RadarCtrl.AddTarget(target);
    m_EsmCtrl.AddTarget(target);
    m_InfraredCtrl.AddTarget(target);
    m_DataListCtrl.AddTarget(target);

    m_RadarDlg.AddTarget(target);
    m_EsmDlg.AddTarget(target);
    m_InfraredDlg.AddTarget(target);
    m_DataListDlg.AddTarget(target);
}
