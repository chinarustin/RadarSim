#pragma once

#include "DataPacket.h"

class CPlaneDlg;

class DataCenterSocket :
    public CSocket
{
public:
    DataCenterSocket(CPlaneDlg *dlg);
    ~DataCenterSocket(void);

    void OnReceive(int nErrorCode);
    void OnClose(int nErrorCode);

    void SendFusionAddr(int port);
    void SendFusionData(FusionDataPacket &packet);
    void SendAttack();

public:
    CPlaneDlg *m_Dlg;
};

