// Step16_FileFindClass.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "framework.h"
#include "Step16_FileFindClass.h"

using namespace std;

void Find(CString path)
{
    CString strPath = path;
    strPath += "/*.*";
    CFileFind find;
    BOOL goFind = find.FindFile(strPath);
    while (goFind)
    {
        goFind = find.FindNextFile();//找到当前文件，将文件信息保存在find对象的成员变量中
        CString filename = find.GetFileName();
        CString filePath = find.GetFilePath();
        if (find.IsDirectory())
        {
            cout << "[" << filename << "]" << endl;
        }
        else
        {
            cout << filename << endl;
        }
    }
}

int main()
{
    Find("c:");

    return 0;
}
