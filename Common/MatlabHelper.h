/**
* @file
* @brief MatLab��������ͷ�ļ�.
* @author ruoxi
*
* ������MatLab��������.
*/

#pragma once

#include <mclmcrrt.h>

#include <vector>
#include <string>

#include <engine.h>

using namespace std;

typedef mxArray Array;

namespace MatlabHelper
{
    typedef bool (*RealFunc)(int, Array *[], int, Array *[]);

    typedef bool (*InitializeFunc)(void);
    /** @brief ʵ����DLL�е��㷨��ʼ��������ǰ׺. */
    extern LPCSTR InitializeFuncPrefix;

    /** @brief ʵ����DLL�е���ں�����ǰ׺. */
    extern LPCSTR FuncPrefix;

    typedef void (*PrintStackFunc)(void);
    extern LPCSTR PrintStackFuncPrefix;

    typedef void (*TerminateFunc)(void);
    /** @brief ʵ����DLL�е��㷨���ٺ�����ǰ׺. */
    extern LPCSTR TerminateFuncPrefix;

    Array *CreateDoubleArray(INT32 x, INT32 y,
        const unsigned char *content,
        INT32 width, INT32 height,
        INT32 startX, INT32 startY);
    Array *CreateDoubleArray(INT32 x, INT32 y,
        const double *content,
        INT32 width, INT32 height,
        INT32 startX, INT32 startY);
    Array *CreateDoubleArray(INT32 x, INT32 y,
        const unsigned char *content,
        INT32 size, INT32 start);
    Array *CreateDoubleArray(INT32 x, INT32 y,
        const double *content,
        INT32 size, INT32 start);
    void DestroyArray(Array *a);

    bool RunFunc(LPCWSTR dllFileName, LPCWSTR funcName, vector<Array *> &outputList, vector<Array *> &inputList);
    bool RealRunFunc(HINSTANCE algorithmDllHandle, const string &fullFuncName, vector<Array *> &outputList, vector<Array *> &inputList, bool &result);
};

