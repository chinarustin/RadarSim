#include "StdAfx.h"
#include "DataCenterSocket.h"
#include "Resource.h"
#include "PlaneDlg.h"

DataCenterSocket::DataCenterSocket(CPlaneDlg *dlg)
: m_Dlg(dlg)
{
}

DataCenterSocket::~DataCenterSocket(void)
{
}

void DataCenterSocket::OnReceive(int nErrorCode)
{
    CSocketFile file(this);
    CArchive ar(&file, CArchive::load);

    int type;
    ar >> type;
    switch (type)
    {
    case PacketTypeFusionAddr:
        {
            CString addr;
            int port;
            ar >> addr >> port;
            ar.Flush();
            m_Dlg->ConnectFusion(addr, port);
        }
        break;
    default:
        AfxMessageBox(TEXT("δ֪���ݰ�����"));
        break;
    }
}

void DataCenterSocket::OnClose(int nErrorCode)
{
    AfxMessageBox(TEXT("���������ĵ����ӶϿ�"));
    m_Dlg->ResetSockets();
    m_Dlg->ConnectDataCenter();
}

void DataCenterSocket::SendFusionAddr(int port)
{
    CSocketFile file(this);
    CArchive ar(&file, CArchive::store);

    ar << PacketTypeImFusion << port;
    ar.Flush();
}
