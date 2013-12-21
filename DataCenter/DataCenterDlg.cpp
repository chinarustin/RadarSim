
// DataCenterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataCenter.h"
#include "DataCenterDlg.h"

#include "DataCenterSocket.h"
#include "PlaneSocket.h"

#include <algorithm>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "FusionLocalAlgo.h"
#include "FusionVcAlgo.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDataCenterDlg �Ի���


#define TIMES 10
#define TIME_FRAMES 100
#define WM_TIME_FRAME (WM_USER + 1)


CDataCenterDlg::CDataCenterDlg(CWnd* pParent /*=NULL*/)
	: CCommonDlg(CDataCenterDlg::IDD, pParent)
    , m_FusionConnected(false)
    , m_ConnectedPlanes(0)
    , m_ShowStateMapDlg(true)
    , m_ShowMatlabDlg(true)
    , m_StateMapDlg(TEXT("̬��"), m_StateMap, this)
    , m_CurrentFrame(0)
    , m_CurrentRound(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_DataCenterSocket = new DataCenterSocket(this);
}

CDataCenterDlg::~CDataCenterDlg()
{
    for (int i = 0; i < m_FusionAlgos.size(); ++i)
    {
        delete m_FusionAlgos[i];
    }
    for (int i = 0; i < m_NaviAlgos.size(); ++i)
    {
        delete m_NaviAlgos[i];
    }
}

void CDataCenterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDataCenterDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, &CDataCenterDlg::OnBnClickedOk)
    ON_WM_TIMER()
    ON_WM_MBUTTONDBLCLK()
END_MESSAGE_MAP()


// CDataCenterDlg ��Ϣ�������

BOOL CDataCenterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // TODO: �ڴ���Ӷ���ĳ�ʼ������
    if (!m_DataCenterSocket->Create(DATA_CENTER_PORT))
    {
        AfxMessageBox(TEXT("�׽��ִ���ʧ��."));
        exit(-1);
    }
    if (!m_DataCenterSocket->Listen())
    {
        AfxMessageBox(TEXT("����ʧ��."));
        exit(-1);
    }
    if (!m_DataCenterSocket->AsyncSelect(FD_ACCEPT))
    {
        AfxMessageBox(TEXT("ѡ��ʧ��."));
        exit(-1);
    }

    ReadAlgoConfigFile();
    if (m_FusionAlgos.size() == 0)
    {
        AfxMessageBox(TEXT("δ�ܶ�ȡ�κ��ں��㷨."));
        exit(-1);
    }
    if (0 && m_NaviAlgos.size() == 0)
    {
        AfxMessageBox(TEXT("δ�ܶ�ȡ�κε����㷨."));
        exit(-1);
    }

    CStateMapDlg::CreateDlg(m_StateMapDlg);
    if (m_ShowStateMapDlg)
    {
        m_StateMapDlg.ShowWindow(SW_SHOW);
    }
    {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
    }

    ResetCtrls();
    ResetSockets();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDataCenterDlg::OnPaint()
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
HCURSOR CDataCenterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDataCenterDlg::OnSubDlgClose(void *subDlg)
{
    /*
    if (subDlg == (void *)&m_DataListDlg)
    {
        OnNMDblclkDatalistCtrl(0, 0);
    }
    */
    if (subDlg == (void *)&m_StateMapDlg)
    {
        OnLButtonDblClk(0, 0);
    }
}

void CDataCenterDlg::AddPlaneSocket()
{
    m_Lock.Lock();
    PlaneSocket *socket = new PlaneSocket(this);
    if (m_DataCenterSocket->Accept(*socket))
    {
        socket->AsyncSelect(FD_CLOSE | FD_READ | FD_WRITE);
    }

    int i;
    for (i = 0; i < PLANE_COUNT; ++i)
    {
        if (m_PlaneClients[i].m_PlaneSocket == NULL)
        {
            m_PlaneClients[i].m_PlaneSocket = socket;
            break;
        }
    }
    if (i == PLANE_COUNT)
    {
        AfxMessageBox(TEXT("��������"));
        socket->Close();
        delete socket;
        return;
    }
    m_ConnectedPlanes++;
    if (m_FusionConnected)
    {
        socket->SendFusionAddr(m_FusionAddr, m_FusionPort);
    }
    m_Lock.Unlock();
    if (m_FusionConnected && m_ConnectedPlanes == PLANE_COUNT)
    {
        GetDlgItem(IDOK)->EnableWindow(TRUE);
    }
}

void CDataCenterDlg::SetFusionAddr(const CString &addr, int port)
{
    m_FusionAddr = addr;
    m_FusionPort = port;
    m_FusionConnected = true;

    for (int i = 0; i < PLANE_COUNT; ++i)
    {
        if (m_PlaneClients[i].m_PlaneSocket)
        {
            m_PlaneClients[i].m_PlaneSocket->SendFusionAddr(m_FusionAddr, m_FusionPort);
        }
    }
    if (m_FusionConnected && m_ConnectedPlanes == PLANE_COUNT)
    {
        GetDlgItem(IDOK)->EnableWindow(TRUE);
    }
}

void CDataCenterDlg::ResetSockets()
{
    m_Lock.Lock();
    for (int i = 0; i < PLANE_COUNT; ++i)
    {
        if (m_PlaneClients[i].m_PlaneSocket)
        {
            m_PlaneClients[i].m_PlaneSocket->Close();
            delete m_PlaneClients[i].m_PlaneSocket;
            m_PlaneClients[i].m_PlaneSocket = NULL;
        }
    }

    m_FusionConnected = false;
    m_ConnectedPlanes = 0;
    m_Lock.Unlock();

    GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CDataCenterDlg::ResetCtrls()
{
    if (m_FusionConnected && m_ConnectedPlanes != PLANE_COUNT)
    {
        GetDlgItem(IDOK)->EnableWindow(FALSE);
    }

    // m_DataList.Reset();
    // m_DataListCtrl.Reset();
    // m_DataListDlg.Reset();

    m_StateMap.Reset();
    m_StateMapDlg.Reset();
    m_MatlabDlg.Reset();
}

void CDataCenterDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    // OnOK();
    m_CurrentRound = 0;
    StartSim();
}

void CDataCenterDlg::GeneratePlaneClients()
{
    for (int i = 0; i < PLANE_COUNT; ++i)
    {
        m_PlaneClients[i].m_Plane.m_Type = (TargetType)i;
        m_PlaneClients[i].m_Plane.m_MoveType = (TargetMoveType)(i % 2);
        m_PlaneClients[i].m_Plane.m_Position = Position(100, 10 + 200 * i, 100);
        // m_PlaneClients[i].m_Plane.m_Vel = Position(i + 1, ((double)rand() - (double)RAND_MAX / 2) / ((double)RAND_MAX / 2) * 2, rand() % 3);
        m_PlaneClients[i].m_Plane.m_Vel = Position(i + 1, 0, rand() % 3);
        m_PlaneClients[i].m_Plane.m_Acc = Position(rand() % 1, rand() % 1, rand() % 1);
        m_PlaneClients[i].m_Plane.m_Color = (TargetColor)i;
        m_PlaneClients[i].m_Radar.m_MaxDis = 300 + i * 10;
        m_PlaneClients[i].m_Radar.m_MaxTheta = 120 + i * 10;
        m_PlaneClients[i].m_Esm.m_MaxDis = 250 + i * 10;
        m_PlaneClients[i].m_Esm.m_MaxTheta = 90 + i * 10;
        m_PlaneClients[i].m_Esm.m_ThetaRangeColor = Color::Red;
        m_PlaneClients[i].m_Esm.m_ShowHeight = FALSE;
        m_PlaneClients[i].m_Infrared.m_MaxDis = 350 + i * 10;
        m_PlaneClients[i].m_Infrared.m_MaxTheta = 60 + i * 10;
        m_PlaneClients[i].m_Infrared.m_ShowScanline = FALSE;
        m_PlaneClients[i].m_Infrared.m_ShowThetaRange = FALSE;
        m_PlaneClients[i].m_Infrared.m_ThetaRangeColor = Color::Yellow;
        m_PlaneClients[i].m_Infrared.m_ShowHeight = FALSE;
        m_PlaneClients[i].m_StateMap.m_Background = StateMapBackground3;
        m_PlaneClients[i].m_StateMap.m_MaxX = 1200;
        m_PlaneClients[i].m_StateMap.m_MaxY = 800;
    }
}

void CDataCenterDlg::GenerateTargetClients()
{
    m_TargetClients.clear();
    for (int i = 0; i < TARGET_COUNT; ++i)
    {
        TargetClient client;
        client.m_Target.m_Type = (TargetType)((int)TargetTypeShipboard + rand() % ((int)TargetTypeMissile - (int)TargetTypeShipboard + 1));
        client.m_Target.m_MoveType = TargetMoveTypeUniVel;
        client.m_Target.m_Position = Position(130, 150 + 150 * i, 150) + Position(10 * (rand() % 3), 10 * (rand() % 3), 10 * (rand() % 3));
        client.m_Target.m_Vel = Position(i + 1, 0, rand() % 3);
        client.m_Target.m_Color = (TargetColor)(i + PLANE_COUNT);
        m_TargetClients.push_back(client);
    }
}

void CDataCenterDlg::GenerateTrueData()
{
    for (int i = 0; i < PLANE_COUNT; ++i)
    {
        m_PlaneClients[i].m_PlaneTrueDatas.clear();
    }
    for (int i = 0; i < m_TargetClients.size(); ++i)
    {
        m_TargetClients[i].m_TargetTrueDatas.clear();
    }
    for (int i = m_GlobalData.m_StartTime; i < m_GlobalData.m_EndTime + 1; i += m_GlobalData.m_Interval)
    {
        for (int j = 0; j < PLANE_COUNT; ++j)
        {
            m_PlaneClients[j].m_Plane.Move(m_GlobalData.m_Interval);
            // m_Plane.m_Position = m_PlaneClients[j].m_Plane.m_Position + Position(rand() % 3, (double)rand() / (double)RAND_MAX * cos(j * 3.1415926), rand() % 2);
            // m_PlaneClients[j].m_Plane.m_Position = m_PlaneClients[j].m_Plane.m_Position + Position(3, 3, 3);
            TrueDataFrame frame;
            frame.m_Time = i;
            frame.m_Id = m_PlaneClients[j].m_Plane.m_Id;
            frame.m_Pos = m_PlaneClients[j].m_Plane.m_Position;
            m_PlaneClients[j].m_PlaneTrueDatas.push_back(frame);
        }
        for (int j = 0; j < m_TargetClients.size(); ++j)
        {
            m_TargetClients[j].m_Target.Move(m_GlobalData.m_Interval);
            // m_TargetClients[j].m_Target.m_Position = m_TargetClients[j].m_Target.m_Position + Position(3, 0, 0);
            TrueDataFrame frame;
            frame.m_Time = i;
            frame.m_Id = m_TargetClients[j].m_Target.m_Id;
            frame.m_Pos = m_TargetClients[j].m_Target.m_Position;
            m_TargetClients[j].m_TargetTrueDatas.push_back(frame);
        }
    }
}

void CDataCenterDlg::GenerateGlobalData()
{
}

void CDataCenterDlg::AddFusionData(FusionDataPacket &packet)
{
    m_FusionDatas.push_back(packet);
    ResumeSim();
}

void CDataCenterDlg::StartSim()
{
    m_CurrentFrame = m_GlobalData.m_StartTime;

    GeneratePlaneClients();
    GenerateTargetClients();
    for (int i = 0; i < PLANE_COUNT; ++i)
    {
        m_PlaneClients[i].m_PlaneSocket->SendReset();
        m_PlaneClients[i].m_PlaneSocket->SendPlane(m_PlaneClients[i].m_Plane);
        m_PlaneClients[i].m_PlaneSocket->SendRadar(m_PlaneClients[i].m_Radar);
        m_PlaneClients[i].m_PlaneSocket->SendEsm(m_PlaneClients[i].m_Esm);
        m_PlaneClients[i].m_PlaneSocket->SendInfrared(m_PlaneClients[i].m_Infrared);
        m_PlaneClients[i].m_PlaneSocket->SendStateMap(m_PlaneClients[i].m_StateMap);
        if (m_PlaneClients[i].m_PlaneSocket->IsFusion())
        {
            m_PlaneClients[i].m_PlaneSocket->SendFusionAlgo(m_FusionAlgos[3]);
        }
        if (m_PlaneClients[i].m_PlaneSocket->IsAttack())
        {
            // m_PlaneClients[i].m_PlaneSocket->SendNaviAlgo(m_NaviAlgos[0]);
        }
        for (int j = 0; j < m_TargetClients.size(); ++j)
        {
            m_PlaneClients[i].m_PlaneSocket->SendTarget(m_TargetClients[j].m_Target);
        }
        m_PlaneClients[i].m_PlaneSocket->SendGlobalData(m_GlobalData);
    }

    ResetCtrls();

    m_StateMap.m_Background = StateMapBackground3;
    m_StateMap.m_MaxX = 1200;
    m_StateMap.m_MaxY = 800;

    for (int i = 0; i < PLANE_COUNT; ++i)
    {
        m_StateMap.AddPlane(m_PlaneClients[i].m_Plane, &m_PlaneClients[i].m_Radar, &m_PlaneClients[i].m_Esm, &m_PlaneClients[i].m_Infrared);
        m_StateMapDlg.AddPlane(m_PlaneClients[i].m_Plane);
        m_MatlabDlg.AddPlane(m_PlaneClients[i].m_Plane);
    }

    for (int i = 0; i < m_TargetClients.size(); ++i)
    {
        m_StateMap.AddTarget(m_TargetClients[i].m_Target);
        m_StateMapDlg.AddTarget(m_TargetClients[i].m_Target);
        m_MatlabDlg.AddTarget(m_TargetClients[i].m_Target);
    }

    m_MatlabDlg.SetSize((m_GlobalData.m_EndTime - m_GlobalData.m_StartTime + 1) / m_GlobalData.m_Interval);
    if (m_ShowMatlabDlg)
    {
        m_MatlabDlg.Show();
    }

    m_StateMapDlg.m_Ctrl.DrawBackground();
    m_StateMapDlg.m_Ctrl.DrawTargets();
    m_StateMapDlg.m_Ctrl.BlendAll();
    m_StateMapDlg.m_Ctrl.Invalidate();

    m_FusionDatas.clear();
    GenerateTrueData();
    m_CurrentFrame = 0;
    SetTimer(WM_TIME_FRAME, 800, NULL);
}

void CDataCenterDlg::PauseSim()
{
    KillTimer(WM_TIME_FRAME);
}

void CDataCenterDlg::ResumeSim()
{
    SetTimer(WM_TIME_FRAME, 800, NULL);
}

void CDataCenterDlg::FinishSim()
{
    m_CurrentRound++;
    if (m_CurrentRound >= m_GlobalData.m_Rounds)
    {
    }
    else
    {
        StartSim();
    }
    // Save dat files at last.
}

void CDataCenterDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    CDialog::OnTimer(nIDEvent);
    PauseSim();

    if (nIDEvent == WM_TIME_FRAME)
    {
        if (m_CurrentFrame > m_GlobalData.m_EndTime)
        {
            FinishSim();
            return;
        }

        int index = m_CurrentFrame / m_GlobalData.m_Interval;

        for (int i = 0; i < PLANE_COUNT; ++i)
        {
            TrueDataPacket packet;
            packet.m_PlaneTrueData = m_PlaneClients[i].m_PlaneTrueDatas[index];
            for (int j = 0; j < m_TargetClients.size(); ++j)
            {
                packet.m_TargetTrueDatas.push_back(m_TargetClients[j].m_TargetTrueDatas[index]);
            }
            m_PlaneClients[i].m_PlaneSocket->SendTrueData(packet);
        }

        for (int i = 0; i < PLANE_COUNT; ++i)
        {
            m_StateMap.AddPlaneData(i, m_PlaneClients[i].m_PlaneTrueDatas[index].m_Pos);
            m_MatlabDlg.AddPlaneData(i, m_PlaneClients[i].m_PlaneTrueDatas[index].m_Pos);
        }
        for (int i = 0; i < TARGET_COUNT; ++i)
        {
            m_StateMap.AddTargetData(i, m_TargetClients[i].m_TargetTrueDatas[index].m_Pos);
            m_MatlabDlg.AddTargetData(i, m_TargetClients[i].m_TargetTrueDatas[index].m_Pos);
        }

        m_StateMapDlg.m_Ctrl.DrawTargets();
        m_StateMapDlg.m_Ctrl.BlendAll();
        m_StateMapDlg.m_Ctrl.Invalidate();

        m_CurrentFrame += m_GlobalData.m_Interval;
    }
}

void CDataCenterDlg::OnMButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if (m_ShowStateMapDlg)
    {
        m_StateMapDlg.ShowWindow(SW_HIDE);
        m_ShowStateMapDlg = false;
    }
    else
    {
        m_StateMapDlg.ShowWindow(SW_SHOW);
        m_ShowStateMapDlg = true;
    }

    CCommonDlg::OnMButtonDblClk(nFlags, point);
}

void CDataCenterDlg::ReadAlgoConfigFile()
{
    wifstream in(ConfigFileName);
    in.imbue(locale("chs"));

    wstring nextLine = TEXT("");

    while(in || nextLine.length() > 0)
    {
        wstring line;
        if(nextLine.length() > 0)
        {
            line = nextLine;  // we read ahead; use it now
            nextLine = L"";
        }
        else
        {
            getline(in, line);
        }

        line = line.substr(0, line.find(TEXT("#")));

        if (line.length() == 0)
        {
            continue;
        }

        wistringstream ist(line);
        wstring key;
        ist >> key;
        if (key == TEXT("FUSION_ALGO"))
        {
            int type;
            ist >> type;
            switch (type)
            {
            case FusionAlgoTypeLocal:
                {
                    wstring name;
                    int localType;
                    ist >> name;
                    ist >> localType;
                    FusionAlgo *algo = new FusionLocalAlgo(name.c_str(), (FusionLocalAlgoType)localType);
                    m_FusionAlgos.push_back(algo);
                }
                break;
            case FusionAlgoTypeVc:
                {
                    wstring name, dllFileName, funcName;
                    ist >> name >> dllFileName >> funcName;
                    FusionAlgo *algo = new FusionVcAlgo(name.c_str(), dllFileName.c_str(), funcName.c_str());
                    m_FusionAlgos.push_back(algo);
                }
                break;
            case FusionAlgoTypeMatlab:
                {
                    wstring name, dllFileName, funcName;
                    ist >> name >> dllFileName >> funcName;
                    FusionAlgo *algo;// = new FusionLocalAlgo(name.c_str(), (FusionLocalAlgoType)localType);
                    m_FusionAlgos.push_back(algo);
                }
                break;
            default:
                CString msg;
                msg.AppendFormat(TEXT("δ֪�ں��㷨����%d."), type);
                AfxMessageBox(msg);
                break;
            }
        }
        else if (key == TEXT("NAVI_ALGO"))
        {
        }
    }

    in.close();
}
