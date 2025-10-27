
// Step5_FileDialog.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CStep5FileDialogApp:
// 有关此类的实现，请参阅 Step5_FileDialog.cpp
//

class CStep5FileDialogApp : public CWinApp
{
public:
	CStep5FileDialogApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CStep5FileDialogApp theApp;
