#include "stdafx.h"
#include "DataList.h"

DataList::DataList(Sensor &radar, Sensor &esm, Sensor &infrared)
: m_Radar(radar)
, m_Esm(esm)
, m_Infrared(infrared)
{
}

DataList::~DataList(void)
{
}

void DataList::Reset()
{
    m_TargetColors.clear();
    m_Times.clear();
}

void DataList::AddTarget(Target &target)
{
    m_TargetColors.push_back(target.m_Color);
    m_Times.push_back(vector<int>());
}

void DataList::AddTargetData(int target, int time)
{
    m_Times[target].push_back(time);
}
