#include "stdafx.h"

#include "Defines.h"
#include <mclmcrrt.h>

Color TargetColors[] =
{
    Color::Red,
    Color::Orange,
    Color::Yellow,
    Color::Green,
    Color::Cyan,
    Color::Blue,
    Color::Purple,
};

CString TargetColorNames[] =
{
    TEXT("��ɫ"),
    TEXT("��ɫ"),
    TEXT("��ɫ"),
    TEXT("��ɫ"),
    TEXT("��ɫ"),
    TEXT("��ɫ"),
    TEXT("��ɫ"),
};

Image *StateMapBackgrounds[];

CString StateMapBackgroundNames[] = 
{
    TEXT("��ͼ0"),
    TEXT("��ͼ1"),
    TEXT("��ͼ2"),
    TEXT("��ͼ3"),
    TEXT("��ͼ4"),
};

Image *TargetTypeImages[] =
{
    Image::FromFile(TEXT("Heli.ico")),
    Image::FromFile(TEXT("Fighter.ico")),
    Image::FromFile(TEXT("Aew.ico")),
    Image::FromFile(TEXT("Bomber.ico")),
    Image::FromFile(TEXT("Shipboard.ico")),
    Image::FromFile(TEXT("Tank.ico")),
    Image::FromFile(TEXT("Panzer.ico")),
    Image::FromFile(TEXT("Missile.ico")),
};

CString TargetTypeNames[] =
{
    TEXT("ֱ����"),
    TEXT("�ߵл�"),
    TEXT("Ԥ����"),
    TEXT("��ը��"),
    TEXT("���ػ�"),
    TEXT("̹��"),
    TEXT("װ�׳�"),
    TEXT("����"),
};

CArchive & operator << (CArchive &ar, Position &pos)
{
    ar << pos.X << pos.Y << pos.Z;

    return ar;
}

CArchive & operator >> (CArchive &ar, Position &pos)
{
    ar >> pos.X >> pos.Y >> pos.Z;

    return ar;
}

void GlobalInit()
{
    srand((unsigned int)time(NULL));

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    StateMapBackgrounds[StateMapBackground0] = Image::FromFile(TEXT("StateMapBackground0.bmp"));
    StateMapBackgrounds[StateMapBackground1] = Image::FromFile(TEXT("StateMapBackground1.bmp"));
    StateMapBackgrounds[StateMapBackground2] = Image::FromFile(TEXT("StateMapBackground2.bmp"));
    StateMapBackgrounds[StateMapBackground3] = Image::FromFile(TEXT("StateMapBackground3.bmp"));
    StateMapBackgrounds[StateMapBackground4] = Image::FromFile(TEXT("StateMapBackground4.bmp"));

    TargetTypeImages[TargetTypeHeli] = Image::FromFile(TEXT("Heli.ico"));
    TargetTypeImages[TargetTypeFighter] = Image::FromFile(TEXT("Fighter.ico"));
    TargetTypeImages[TargetTypeAew] = Image::FromFile(TEXT("Aew.ico"));
    TargetTypeImages[TargetTypeBomber] = Image::FromFile(TEXT("Bomber.ico"));
    TargetTypeImages[TargetTypeShipboard] = Image::FromFile(TEXT("Shipboard.ico"));
    TargetTypeImages[TargetTypeTank] = Image::FromFile(TEXT("Tank.ico"));
    TargetTypeImages[TargetTypePanzer] = Image::FromFile(TEXT("Panzer.ico"));
    TargetTypeImages[TargetTypeMissile] = Image::FromFile(TEXT("Missile.ico"));

    mclInitializeApplication(NULL, 0);
}

void GlobalShut()
{
    for (int i = StateMapBackground0; i < StateMapBackgroundLast; ++i)
    {
        delete StateMapBackgrounds[i];
    }
    for (int i = TargetTypeHeli; i < TargetTypeLast; ++i)
    {
        delete TargetTypeImages[i];
    }
    ULONG_PTR gdiplusToken = NULL; 
    GdiplusShutdown(gdiplusToken);

    mclTerminateApplication();
}
