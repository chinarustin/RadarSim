
// DataCenterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataCenter.h"
#include "DataCenterDlg.h"

#include "DataCenterSocket.h"
#include "PlaneSocket.h"

#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDataCenterDlg �Ի���




CDataCenterDlg::CDataCenterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataCenterDlg::IDD, pParent)
    , m_FusionConnected(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_DataCenterSocket = new DataCenterSocket(this);
}

void CDataCenterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDataCenterDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
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
        AfxMessageBox(TEXT("�׽��ִ���ʧ��"));
        exit(-1);
    }
    if (!m_DataCenterSocket->Listen())
    {
        AfxMessageBox(TEXT("����ʧ��"));
        exit(-1);
    }
    if (!m_DataCenterSocket->AsyncSelect(FD_ACCEPT))
    {
        AfxMessageBox(TEXT("ѡ��ʧ��"));
        exit(-1);
    }

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

void CDataCenterDlg::AddPlaneSocket()
{
    m_Lock.Lock();
    PlaneSocket *socket = new PlaneSocket(this);
    if (m_DataCenterSocket->Accept(*socket))
    {
        socket->AsyncSelect(FD_CLOSE | FD_READ | FD_WRITE);
    }
    m_PlaneSockets.push_back(socket);
    if (m_FusionConnected)
    {
        socket->SendFusionAddr(m_FusionAddr, m_FusionPort);
    }
    m_Lock.Unlock();
}

void CDataCenterDlg::SetFusionAddr(const CString &addr, int port)
{
    m_FusionAddr = addr;
    m_FusionPort = port;
    m_FusionConnected = true;

    for (int i = 0; i < m_PlaneSockets.size(); ++i)
    {
        m_PlaneSockets[i]->SendFusionAddr(m_FusionAddr, m_FusionPort);
    }
}

void CDataCenterDlg::ResetSockets()
{
    m_Lock.Lock();
    for (int i = 0; i < m_PlaneSockets.size(); ++i)
    {
        m_PlaneSockets[i]->Close();
        delete m_PlaneSockets[i];
    }
    m_PlaneSockets.clear();

    m_FusionConnected = false;
    m_Lock.Unlock();
}
