#include "StdAfx.h"
#include "StateMapCtrl.h"
#include "Utility.h"
using namespace Utility;

#include <math.h>

CStateMapCtrl::CStateMapCtrl(StateMap &stateMap)
: m_StateMap(stateMap)
, m_Image(0)
, m_OldBackgroundImg(NULL)
, m_BackgroundImg(NULL)
, m_TargetsImg(NULL)
{
    m_BackgroundImg = StateMapBackgrounds[m_StateMap.m_Background];
}

CStateMapCtrl::~CStateMapCtrl(void)
{
    if (m_Image)
    {
        delete m_Image;
        m_Image = NULL;
    }
    // Don't delete bkg. GlobalShut() will do.
    /*
    if (m_BackgroundImg)
    {
        delete m_BackgroundImg;
        m_BackgroundImg = NULL;
    }
    */
    if (m_TargetsImg)
    {
        delete m_TargetsImg;
        m_TargetsImg = NULL;
    }
}

void CStateMapCtrl::DrawBackground()
{
    m_OldBackgroundImg = m_BackgroundImg;
    m_BackgroundImg = StateMapBackgrounds[m_StateMap.m_Background];
}

void CStateMapCtrl::DrawTargets()
{
    RECT rect;
    GetWindowRect(&rect);
    ScreenToClient(&rect);
    
    UINT srcWidth = m_BackgroundImg->GetWidth(), srcHeight = m_BackgroundImg->GetHeight();
    int width = rect.right - rect.left, height = rect.bottom - rect.top;
    if ((double)width / (double)srcWidth > (double)height / (double)srcHeight)
    {
        width = height * ((double)srcWidth / (double)srcHeight);
    }
    else
    {
        height = width * ((double)srcHeight / (double)srcWidth);
    }

    Image *targetsImg = new Bitmap(width, height);

    Graphics graphics(targetsImg);
    graphics.SetCompositingQuality(CompositingQualityHighQuality);
    graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);

    Pen pen(TargetColors[m_StateMap.m_PlaneColor], TARGET_TRACK_WIDTH);
    if (m_StateMap.m_ShowTrack)
    {
        for (int i = 1; i < m_StateMap.m_PlanePath.size(); ++i)
        {
            PointF pt0(m_StateMap.m_PlanePath[i - 1].X / m_StateMap.m_MaxX * (double)width,
                m_StateMap.m_PlanePath[i - 1].Y / m_StateMap.m_MaxY * (double)height);
            PointF pt1(m_StateMap.m_PlanePath[i].X / m_StateMap.m_MaxX * (double)width,
                m_StateMap.m_PlanePath[i].Y / m_StateMap.m_MaxY * (double)height);
            graphics.DrawLine(&pen, pt0, pt1);
        }
    }

    if (m_StateMap.m_PlanePath.size() > 0)
    {
        if (m_StateMap.m_PlanePath.size() > 1)
        {
            Position end = m_StateMap.m_PlanePath.back();
            Position start = m_StateMap.m_PlanePath[m_StateMap.m_PlanePath.size() - 2];
            double angle = Theta(end - start);
            graphics.RotateTransform(angle, MatrixOrderAppend);
            graphics.TranslateTransform(end.X / m_StateMap.m_MaxX * (double)width, end.Y / m_StateMap.m_MaxY * (double)height, MatrixOrderAppend);
        }
        Image *planeImg = TargetTypeImages[m_StateMap.m_PlaneType];
        PointF pt(0.0, 0.0);
        graphics.DrawImage(planeImg, PointF(pt.X - (double)planeImg->GetWidth() / 2.0, pt.Y - (double)planeImg->GetHeight() / 2.0));
        if (m_StateMap.m_ShowThetaRange)
        {
            if (m_StateMap.m_Radar.m_Enable)
            {
                Pen pen(m_StateMap.m_Radar.m_ThetaRangeColor);
                graphics.DrawPie(&pen,
                    (float)(pt.X - m_StateMap.m_Radar.m_MaxDis / m_StateMap.m_MaxX * (double)width),
                    (float)(pt.Y - m_StateMap.m_Radar.m_MaxDis / m_StateMap.m_MaxY * (double)height),
                    (float)(m_StateMap.m_Radar.m_MaxDis / m_StateMap.m_MaxX * (double)width * 2.0),
                    (float)(m_StateMap.m_Radar.m_MaxDis / m_StateMap.m_MaxY * (double)height * 2.0),
                    -m_StateMap.m_Radar.m_MaxTheta / 2.0,
                    m_StateMap.m_Radar.m_MaxTheta);
            }
            if (m_StateMap.m_Esm.m_Enable)
            {
                Pen pen(m_StateMap.m_Esm.m_ThetaRangeColor);
                graphics.DrawPie(&pen,
                    (float)(pt.X - m_StateMap.m_Esm.m_MaxDis / m_StateMap.m_MaxX * (double)width),
                    (float)(pt.Y - m_StateMap.m_Esm.m_MaxDis / m_StateMap.m_MaxY * (double)height),
                    (float)(m_StateMap.m_Esm.m_MaxDis / m_StateMap.m_MaxX * (double)width * 2.0),
                    (float)(m_StateMap.m_Esm.m_MaxDis / m_StateMap.m_MaxY * (double)height * 2.0),
                    -m_StateMap.m_Esm.m_MaxTheta / 2.0,
                    m_StateMap.m_Esm.m_MaxTheta);
            }
            if (m_StateMap.m_Infrared.m_Enable)
            {
                Pen pen(m_StateMap.m_Infrared.m_ThetaRangeColor);
                graphics.DrawPie(&pen,
                    (float)(pt.X - m_StateMap.m_Infrared.m_MaxDis / m_StateMap.m_MaxX * (double)width),
                    (float)(pt.Y - m_StateMap.m_Infrared.m_MaxDis / m_StateMap.m_MaxY * (double)height),
                    (float)(m_StateMap.m_Infrared.m_MaxDis / m_StateMap.m_MaxX * (double)width * 2.0),
                    (float)(m_StateMap.m_Infrared.m_MaxDis / m_StateMap.m_MaxY * (double)height * 2.0),
                    -m_StateMap.m_Infrared.m_MaxTheta / 2.0,
                    m_StateMap.m_Infrared.m_MaxTheta);
            }
        }
        if (m_StateMap.m_PlanePath.size() > 1)
        {
            graphics.ResetTransform();
        }
    }

    if (m_StateMap.m_ShowTrack)
    {
        for (int i = 0; i < m_StateMap.m_TargetTypes.size(); ++i)
        {
            Pen pen(TargetColors[m_StateMap.m_TargetColors[i]], TARGET_TRACK_WIDTH);
            for (int j = 1; j < m_StateMap.m_PlanePath.size(); ++j)
            {
                PointF pt0(m_StateMap.m_TargetPaths[i][j - 1].X / m_StateMap.m_MaxX * (double)width,
                    m_StateMap.m_TargetPaths[i][j - 1].Y / m_StateMap.m_MaxY * (double)height);
                PointF pt1(m_StateMap.m_TargetPaths[i][j].X / m_StateMap.m_MaxX * (double)width,
                    m_StateMap.m_TargetPaths[i][j].Y / m_StateMap.m_MaxY * (double)height);
                graphics.DrawLine(&pen, pt0, pt1);
            }
        }
    }
    for (int i = 0; i < m_StateMap.m_TargetTypes.size(); ++i)
    {
        if (m_StateMap.m_TargetPaths[i].size() > 0)
        {
            if (m_StateMap.m_TargetPaths[i].size() > 1)
            {
                Position end = m_StateMap.m_TargetPaths[i].back();
                Position start = m_StateMap.m_TargetPaths[i][m_StateMap.m_TargetPaths[i].size() - 2];
                double angle = Theta(end - start);
                graphics.RotateTransform(angle, MatrixOrderAppend);
                graphics.TranslateTransform(end.X / m_StateMap.m_MaxX * (double)width, end.Y / m_StateMap.m_MaxY * (double)height, MatrixOrderAppend);
            }
            Image *targetImg = TargetTypeImages[m_StateMap.m_TargetTypes[i]];
            PointF pt(0.0, 0.0);
            graphics.DrawImage(targetImg, PointF(pt.X - (double)targetImg->GetWidth() / 2.0, pt.Y - (double)targetImg->GetHeight() / 2.0));
            if (m_StateMap.m_TargetPaths[i].size() > 1)
            {
                graphics.ResetTransform();
            }
        }
    }

    if (m_TargetsImg)
    {
        delete m_TargetsImg;
    }
    m_TargetsImg = targetsImg;
}

void CStateMapCtrl::BlendAll()
{
    RECT rect;
    GetWindowRect(&rect);
    ScreenToClient(&rect);

    UINT srcWidth = m_BackgroundImg->GetWidth(), srcHeight = m_BackgroundImg->GetHeight();
    int width = rect.right - rect.left, height = rect.bottom - rect.top;
    if ((double)width / (double)srcWidth > (double)height / (double)srcHeight)
    {
        width = height * ((double)srcWidth / (double)srcHeight);
    }
    else
    {
        height = width * ((double)srcHeight / (double)srcWidth);
    }

    Image *img = new Bitmap(width, height);
    Graphics graphics(img);
    graphics.DrawImage(m_BackgroundImg, 0, 0, width, height);
    graphics.DrawImage(m_TargetsImg, Point(0, 0));

    if (m_Image)
    {
        delete m_Image;
    }
    m_Image = img;
}

BEGIN_MESSAGE_MAP(CStateMapCtrl, CStatic)
    ON_WM_PAINT()
    ON_WM_SIZE()
END_MESSAGE_MAP()

void CStateMapCtrl::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: �ڴ˴�������Ϣ�����������
    // ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
    RECT rect;
    GetWindowRect(&rect);
    ScreenToClient(&rect);
    int width = rect.right - rect.left, height = rect.bottom - rect.top;
    int left = rect.left, top = rect.top;
    if (width >= height)
    {
        left += (width - height) / 2;
    }
    else
    {
        top += (height - width) / 2;
    }

    if (m_Image)
    {
        double left = rect.left + (double)(rect.right - rect.left - m_Image->GetWidth()) / 2,
            top = rect.top + (double)(rect.bottom - rect.top - m_Image->GetHeight()) / 2;
        Gdiplus::Graphics graphics(dc.GetSafeHdc());
        if (m_OldBackgroundImg)
        {
            Color color;
            color.SetFromCOLORREF(GetSysColor(COLOR_3DFACE));
            graphics.Clear(color);
            m_OldBackgroundImg = NULL;
        }
        graphics.DrawImage(m_Image, PointF(left, top));
    }
}

void CStateMapCtrl::OnSize(UINT nType, int cx, int cy)
{
    CStatic::OnSize(nType, cx, cy);

    // TODO: �ڴ˴�������Ϣ�����������
    DrawBackground();
    DrawTargets();
    BlendAll();
}

void CStateMapCtrl::Reset()
{
    DrawBackground();
    BlendAll();
    Invalidate();
}

void CStateMapCtrl::AddTarget(Target &target)
{
}