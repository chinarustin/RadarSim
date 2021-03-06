#pragma once

class __declspec(dllexport) Target
{
public:
    Target();
    virtual ~Target(void);

    int m_Id;
    TargetType m_Type;

    Position m_InitPosition;
    Velocity m_InitVel;
    Acceleration m_InitAcc;

    Position m_Position;
    Velocity m_Vel;
    Acceleration m_Acc;

    // 圆周运动参数
    Position m_Center; // 初始化为m_Position
    double m_Pal; // 角速度
    double m_Radius; // 半径

    Point3D m_HeadDir;

    TargetMoveType m_MoveType;

    TargetColor m_Color;

    void Move(double t);
    void MoveTo(const Position &pos);

    void Reset();
};

typedef Target Plane;

__declspec(dllexport) CArchive & operator << (CArchive &ar, Target &target);

__declspec(dllexport) CArchive & operator >> (CArchive &ar, Target &target);
