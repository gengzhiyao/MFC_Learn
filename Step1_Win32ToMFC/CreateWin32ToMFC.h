//#include "pch.h"

class CreateWin32ToMFC : public CWinApp
{
public:
	CreateWin32ToMFC();
	virtual BOOL InitInstance();
};

class mfcFrame :public CFrameWnd
{
public:
	virtual LRESULT WindowProc(UINT msgID, WPARAM wParam, LPARAM lParam) override;
};

class UseMapFrame :public CFrameWnd
{
public:
	LRESULT OnMyCreate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};