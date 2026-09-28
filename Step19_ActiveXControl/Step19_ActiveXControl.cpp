// Step19_ActiveXControl.cpp: CStep19ActiveXControlApp 和 DLL 注册的实现。

#include "pch.h"
#include "framework.h"
#include "Step19_ActiveXControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CStep19ActiveXControlApp theApp;

const GUID CDECL _tlid = {0x05e6855b,0xe638,0x45d5,{0xb7,0x98,0x8a,0x7c,0x6f,0x17,0xf1,0x83}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CStep19ActiveXControlApp::InitInstance - DLL 初始化

BOOL CStep19ActiveXControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CStep19ActiveXControlApp::ExitInstance - DLL 终止

int CStep19ActiveXControlApp::ExitInstance()
{
	// TODO:  在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
