#include "StdAfx.h"
#include "RadarCtrl.h"

RadarCtrl::RadarCtrl(RadarParam &param)
: m_Param(param)
{
}

RadarCtrl::~RadarCtrl(void)
{
}

BEGIN_MESSAGE_MAP(RadarCtrl, CStatic)
    ON_WM_PAINT()
END_MESSAGE_MAP()

void RadarCtrl::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �ڴ˴������Ϣ����������
    // ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
}
