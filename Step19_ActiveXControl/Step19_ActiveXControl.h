#pragma once

// Step19_ActiveXControl.h: Step19_ActiveXControl.DLL 的主标头文件

#if !defined( __AFXCTL_H__ )
#error "在包括此文件之前包括“afxctl.h”"
#endif

#include "resource.h"       // 主符号


// CStep19ActiveXControlApp: 请参阅 Step19_ActiveXControl.cpp 了解实现。

class CStep19ActiveXControlApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

