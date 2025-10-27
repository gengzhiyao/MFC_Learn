// StartDialog.cpp: 实现文件
//

#include "pch.h"
#include "Step3_PropertyPage.h"
#include "StartDialog.h"


// StartDialog 对话框

IMPLEMENT_DYNCREATE(StartDialog, CPropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(StartDialog, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &StartDialog::OnBnClickedButton1)
END_MESSAGE_MAP()

// StartDialog::StartDialog - 构造函数

// TODO:  定义页标题的字符串资源；用 ID 替换下面的“0”。

StartDialog::StartDialog() :
	CPropertyPage(IDD_DIALOG1)
{

}



// StartDialog::DoDataExchange - 在页和属性间移动数据

void StartDialog::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// StartDialog 消息处理程序

void StartDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
