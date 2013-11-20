#include "Sensor.h"

CString Sensor::SensorTypeNames[] = {TEXT("��Դ������"), TEXT("��Դ������")};

Sensor::Sensor(SensorType type, Plane &plane)
: Type(type)
, Enable(TRUE)
, MaxDis(100)
, MaxTheta(120)
, MaxPhi(90)
, DisVar(0)
, ThetaVar(0)
, PhiVar(0)
, ProDet(0)
, ShowScanline(TRUE)
, ShowTrack(TRUE)
, m_Plane(plane)
{
}

Sensor::~Sensor(void)
{
}
