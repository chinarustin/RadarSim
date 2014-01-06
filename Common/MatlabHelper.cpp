/**
* @file
* @brief MatLab��������cpp�ļ�.
* @author ruoxi
*
* ʵ����MatLab��������.
*/
#include "stdafx.h"

#include "MatlabHelper.h"
#include <shlwapi.h>
#include "utility.h"

namespace MatlabHelper
{

LPCSTR InitializeFuncPrefix = "Initialize";

LPCSTR FuncPrefix = "mlx";

LPCSTR PrintStackFuncPrefix = "PrintStackTrace";

LPCSTR TerminateFuncPrefix = "Terminate";

Array *CreateDoubleArray(INT32 x, INT32 y,
                         const unsigned char *content,
                         INT32 width, INT32 height,
                         INT32 startX, INT32 startY)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (width && height)
        {
            for (INT32 yy = max(0, -startY); yy < min(y, height - startY); ++yy)
            {
                for (INT32 xx = max(0, -startX); xx < min(x, width - startX); ++xx)
                {
                    p[yy * x + xx] = content[(startY + yy) * width + startX + xx];
                }
            }
        }
        else
        {
            for (INT32 i = 0; i < x * y; ++i)
            {
                p[i] = content[i];
            }
        }
    }

    return a;
}

Array *CreateDoubleArray(INT32 x, INT32 y,
                         const double *content,
                         INT32 width, INT32 height,
                         INT32 startX, INT32 startY)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (width && height)
        {
            for (INT32 yy = max(0, -startY); yy < min(y, height - startY); ++yy)
            {
                for (INT32 xx = max(0, -startX); xx < min(x, width - startX); ++xx)
                {
                    p[yy * x + xx] = content[(startY + yy) * width + startX + xx];
                }
            }
        }
        else
        {
            for (INT32 i = 0; i < x * y; ++i)
            {
                p[i] = content[i];
            }
        }
    }

    return a;
}

Array *CreateDoubleArray(INT32 x, INT32 y,
                         const unsigned char *content,
                         INT32 size, INT32 start)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (size)
        {
            for (INT32 i = max(0, -start); i < min(x * y, size - start); ++i)
            {
                p[i] = content[start + i];
            }
        }
        else
        {
            for (INT32 i = 0; i < x * y; ++i)
            {
                p[i] = content[i];
            }
        }
    }

    return a;
}

Array *CreateDoubleArray(INT32 x, INT32 y,
                         const double *content,
                         INT32 size, INT32 start)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (size)
        {
            for (INT32 i = max(0, -start); i < min(x * y, size - start); ++i)
            {
                p[i] = content[start + i];
            }
        }
        else
        {
            for (INT32 i = 0; i < x * y; ++i)
            {
                p[i] = content[i];
            }
        }
    }

    return a;
}

void DestroyArray(Array *a)
{
    mxDestroyArray(a);
}

bool RunFunc(LPCWSTR dllFileName, LPCWSTR funcName, vector<Array *> &outputList, vector<Array *> &inputList)
{
    HINSTANCE algorithmDllHandle = LoadLibrary(dllFileName);

    if (!algorithmDllHandle)
    {
        return false;
    }

    bool result;
    wstring wsFuncName(funcName);
    string sFuncName(wsFuncName.begin(), wsFuncName.end());

    string initializeFuncName = sFuncName;
    initializeFuncName += InitializeFuncPrefix;

    InitializeFunc initializeFunc = (InitializeFunc)GetProcAddress(
        (HMODULE)algorithmDllHandle,
        initializeFuncName.c_str());

    if (!initializeFunc)
    {
        return false;
    }

    result = initializeFunc();

    if (!result)
    {
        return false;
    }

    string fullFuncName = sFuncName;
    fullFuncName[0] = toupper(fullFuncName[0]);
    fullFuncName = FuncPrefix + fullFuncName;

    if(!RealRunFunc(algorithmDllHandle, fullFuncName, outputList, inputList, result))
    {
        return false;
    }

    if (!result)
    {
        string printStackFuncName = sFuncName;
        printStackFuncName += PrintStackFuncPrefix;

        PrintStackFunc printStackFunc = (PrintStackFunc)GetProcAddress(
            (HMODULE)algorithmDllHandle,
            printStackFuncName.c_str());

        printStackFunc();

        return false;
    }

    string terminateFuncName = sFuncName;
    terminateFuncName += TerminateFuncPrefix;

    TerminateFunc terminateFunc = (TerminateFunc)GetProcAddress(
        (HMODULE)algorithmDllHandle,
        terminateFuncName.c_str());

    if (!terminateFunc)
    {
        return false;
    }

    // terminateFunc();

    return true;
}

/**
* @param algorithmDllHandle �㷨DLL�ļ����.
* @param fullFuncName �㷨��ں���ȫ��.
* @param paramList �㷨�����б�.
* @param output �㷨���.
* @param result �㷨���ý��.
* @return �������.
*
* �ú������㷨���и�����������,
* ����ʵ�ֶ�һ���㷨��ں����ľ������.
* �ú��������㷨DLL�ļ�����Լ��㷨��ں���ȫ��(ͨ��MatLab�����ĺ��������ǰ׺),
* ���տɱ�����Ĳ���,
* �Բ����������б���,
* ʵ�ֶԲ����б��޲�����(Ŀǰ���֧��5������, ������Ҫ����������),
* ���Ҽ�¼�㷨���ý��.
*/
bool RealRunFunc(HINSTANCE algorithmDllHandle, const string &fullFuncName, vector<Array *> &outputList, vector<Array *> &inputList, bool &result)
{
    UINT32 outputCount = outputList.size();
    UINT32 inputCount = inputList.size();

    RealFunc func = (RealFunc)GetProcAddress(
        algorithmDllHandle,
        fullFuncName.c_str());
    if (!func)
    {
        return false;
    }
    result = func(outputCount, &outputList[0], inputCount, &inputList[0]);

    return true;
}

}
