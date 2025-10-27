
// Step3_PropertyPageDlg.h: 头文件
//

#pragma once


// CStep3PropertyPageDlg 对话框
class CStep3PropertyPageDlg : public CDialogEx
{
// 构造
public:
	CStep3PropertyPageDlg(CWnd* pParent = nullptr);	// 标准构造函数
	afx_msg void OnBnClickedButton1();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STEP3_PROPERTYPAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
