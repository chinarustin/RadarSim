// RadarDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Radar.h"
#include "RadarDlg.h"


// CRadarDlg �Ի���

IMPLEMENT_DYNAMIC(CRadarDlg, CDialog)

CRadarDlg::CRadarDlg(Sensor &radar, RadarClientProxy &clientProxy, CWnd* pParent /*=NULL*/)
	: CDialog(CRadarDlg::IDD, pParent)
    , m_Radar(radar)
    , m_ClientProxy(clientProxy)
    , m_Ctrl(m_Radar)
    , m_Initialized(false)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CRadarDlg::~CRadarDlg()
{
}

void CRadarDlg::CreateDlg(CRadarDlg &dlg)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    dlg.Create(IDD_RADAR_DLG, GetDesktopWindow());

    dlg.SetIcon(dlg.m_hIcon, TRUE);
    dlg.SetIcon(dlg.m_hIcon, FALSE);

    dlg.m_Initialized = true;

    for (map<int, Target>::iterator it = dlg.m_Radar.m_Plane.m_Targets.begin();
        it != dlg.m_Radar.m_Plane.m_Targets.end();
        ++it)
    {
        CString str;
        str.AppendFormat(TEXT("%d"), it->first);
        dlg.m_TargetId.InsertString(dlg.m_TargetId.GetCount(), str);
        dlg.m_TargetId.SetItemData(dlg.m_TargetId.GetCount() - 1, it->first);
    }

    for (int i = 0; i < Target::TargetColorLast; ++i)
    {
        dlg.m_TargetColor.InsertString(i, Target::TargetColorNames[i]);
    }

    if (!dlg.m_Ctrl.Init())
    {
        ASSERT(0);
    }
    dlg.Resize();
}

void CRadarDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RADAR, m_Ctrl);
    DDX_Text(pDX, IDC_RADAR_TYPE, Sensor::SensorTypeNames[m_Radar.Type]);
    DDX_Check(pDX, IDC_RADAR_ENABLE, m_Radar.Enable);
    DDX_Text(pDX, IDC_RADAR_MAX_DIS, m_Radar.MaxDis);
    DDX_Text(pDX, IDC_RADAR_MAX_THETA, m_Radar.MaxTheta);
    DDX_Text(pDX, IDC_RADAR_MAX_PHI, m_Radar.MaxPhi);
    DDX_Text(pDX, IDC_RADAR_DIS_VAR, m_Radar.DisVar);
    DDX_Text(pDX, IDC_RADAR_THETA_VAR, m_Radar.ThetaVar);
    DDX_Text(pDX, IDC_RADAR_PHI_VAR, m_Radar.PhiVar);
    DDX_Text(pDX, IDC_RADAR_PRO_DET, m_Radar.ProDet);
    DDX_Check(pDX, IDC_RADAR_SHOW_SCANLINE, m_Radar.ShowScanline);
    DDX_Check(pDX, IDC_RADAR_SHOW_TRACK, m_Radar.ShowTrack);
    DDX_Control(pDX, IDC_RADAR_TARGET_ID, m_TargetId);
    DDX_Control(pDX, IDC_RADAR_TARGET_COLOR, m_TargetColor);
}


BEGIN_MESSAGE_MAP(CRadarDlg, CDialog)
	ON_WM_QUERYDRAGICON()
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_RADAR_SHOW_SCANLINE, &CRadarDlg::OnBnClickedRadarShowScanline)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_RADAR_ENABLE, &CRadarDlg::OnBnClickedRadarEnable)
    ON_BN_CLICKED(IDC_RADAR_SHOW_TRACK, &CRadarDlg::OnBnClickedRadarShowTrack)
    ON_EN_CHANGE(IDC_RADAR_MAX_DIS, &CRadarDlg::OnEnChangeRadarMaxDis)
    ON_CBN_SELCHANGE(IDC_RADAR_TARGET_ID, &CRadarDlg::OnCbnSelchangeRadarTargetId)
    ON_CBN_SELCHANGE(IDC_RADAR_TARGET_COLOR, &CRadarDlg::OnCbnSelchangeRadarTargetColor)
END_MESSAGE_MAP()


// CRadarDlg ��Ϣ�������


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRadarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRadarDlg::OnClose()
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    // CDialog::OnClose();
    m_ClientProxy.OnClose();
}

void CRadarDlg::Resize()
{
    RECT rect;
    GetClientRect(&rect);

    int left = rect.left + PAD, width = 2 * (80 + PAD), top = rect.top + PAD, height = rect.bottom - rect.top - PAD * 2;
    int left2 = left + width + PAD, width2 = rect.right - PAD - left2, top2 = top, height2 = height;

    GetDlgItem(IDC_RADAR_PARAM_GRP)->MoveWindow(left, top, width, height);

    left = left + PAD;
    width = 80;
    top = top + PAD * 2;
    height = 20;
    GetDlgItem(IDC_RADAR_TYPE_STATIC)->MoveWindow(left, top, width, height);
    GetDlgItem(IDC_RADAR_TYPE)->MoveWindow(left + width, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_ENABLE)->MoveWindow(left, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_MAX_DIS_STATIC)->MoveWindow(left, top, width, height);
    GetDlgItem(IDC_RADAR_MAX_DIS)->MoveWindow(left + width, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_MAX_THETA_STATIC)->MoveWindow(left, top, width, height);
    GetDlgItem(IDC_RADAR_MAX_THETA)->MoveWindow(left + width, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_MAX_PHI_STATIC)->MoveWindow(left, top, width, height);
    GetDlgItem(IDC_RADAR_MAX_PHI)->MoveWindow(left + width, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_DIS_VAR_STATIC)->MoveWindow(left, top, width, height);
    GetDlgItem(IDC_RADAR_DIS_VAR)->MoveWindow(left + width, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_THETA_VAR_STATIC)->MoveWindow(left, top, width, height);
    GetDlgItem(IDC_RADAR_THETA_VAR)->MoveWindow(left + width, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_PHI_VAR_STATIC)->MoveWindow(left, top, width, height);
    GetDlgItem(IDC_RADAR_PHI_VAR)->MoveWindow(left + width, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_PRO_DET_STATIC)->MoveWindow(left, top, width, height);
    GetDlgItem(IDC_RADAR_PRO_DET)->MoveWindow(left + width, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_SHOW_SCANLINE)->MoveWindow(left, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_SHOW_TRACK)->MoveWindow(left, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_TARGET_ID_STATIC)->MoveWindow(left, top, width, height);
    GetDlgItem(IDC_RADAR_TARGET_ID)->MoveWindow(left + width, top, width, height);

    top = top + height + PAD;
    GetDlgItem(IDC_RADAR_TARGET_COLOR_STATIC)->MoveWindow(left, top, width, height);
    GetDlgItem(IDC_RADAR_TARGET_COLOR)->MoveWindow(left + width, top, width, height);

    GetDlgItem(IDC_RADAR_GRP)->MoveWindow(left2, top2, width2, height2);
    GetDlgItem(IDC_RADAR)->MoveWindow(left2 + PAD, top2 + PAD * 2, width2 - PAD * 2, height2 - PAD * 3);
}

void CRadarDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: �ڴ˴������Ϣ����������
    if (m_Initialized)
    {
        Resize();
    }
}

void CRadarDlg::OnBnClickedRadarEnable()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    m_Radar.Enable = !m_Radar.Enable;
    m_Ctrl.BlendAll();
    m_Ctrl.Invalidate();
    m_ClientProxy.BlendAll();
    m_ClientProxy.Invalidate();
}

void CRadarDlg::OnBnClickedRadarShowScanline()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    m_Radar.ShowScanline = !m_Radar.ShowScanline;
    m_Ctrl.BlendAll();
    m_Ctrl.Invalidate();
    m_ClientProxy.BlendAll();
    m_ClientProxy.Invalidate();
}

void CRadarDlg::OnBnClickedRadarShowTrack()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    m_Radar.ShowTrack = !m_Radar.ShowTrack;
    m_Ctrl.DrawTargets();
    m_Ctrl.BlendAll();
    m_Ctrl.Invalidate();
    m_ClientProxy.DrawTargets();
    m_ClientProxy.BlendAll();
    m_ClientProxy.Invalidate();
}

void CRadarDlg::OnEnChangeRadarMaxDis()
{
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
    // ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
    // ���������� CRichEditCtrl().SetEventMask()��
    // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    m_Radar.MaxDis = GetDlgItemInt(IDC_RADAR_MAX_DIS);
    m_Ctrl.BlendAll();
    m_Ctrl.Invalidate();
    m_ClientProxy.BlendAll();
    m_ClientProxy.Invalidate();
}

void CRadarDlg::OnCbnSelchangeRadarTargetId()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    int index = m_TargetId.GetCurSel();
    int count = m_TargetId.GetCount();
    if ((index != CB_ERR) && (count >= 1))
    {
        int targetId = m_TargetId.GetItemData(index);
        m_TargetColor.SetCurSel(m_Radar.m_Plane.m_Targets[targetId].m_Color);
    }
}

void CRadarDlg::OnCbnSelchangeRadarTargetColor()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    int index = m_TargetId.GetCurSel();
    int count = m_TargetId.GetCount();
    if ((index != CB_ERR) && (count >= 1))
    {
        int targetId = m_TargetId.GetItemData(index);
        m_Radar.m_Plane.m_Targets[targetId].m_Color = (Target::TargetColor)m_TargetColor.GetCurSel();
        m_Ctrl.DrawTargets();
        m_Ctrl.BlendAll();
        m_Ctrl.Invalidate();
        m_ClientProxy.DrawTargets();
        m_ClientProxy.BlendAll();
        m_ClientProxy.Invalidate();
    }
}
