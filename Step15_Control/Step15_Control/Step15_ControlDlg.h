
// Step15_ControlDlg.h: 头文件
//

#pragma once


// CStep15ControlDlg 对话框
class CStep15ControlDlg : public CDialogEx
{
// 构造
public:
	CStep15ControlDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STEP15_CONTROL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();//处理对话框的创建消息
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_btn;
	afx_msg void OnClickedButton1();
	afx_msg void OnDoubleclickedButton1();
	CButton m_checkBox;
	afx_msg void OnClickedCheck1();
	CComboBox m_comboBox1;
	CComboBox m_comboBox2;
	CComboBox m_comboBox3;
	CComboBox m_cbListCtl;
	CListCtrl m_listCtl;
	afx_msg void OnSelchangeComboListctl();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	CTreeCtrl m_tree;
};
