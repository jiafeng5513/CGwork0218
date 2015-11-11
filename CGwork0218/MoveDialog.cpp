// MoveDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "CGwork0218.h"
#include "MoveDialog.h"
#include "afxdialogex.h"


// CMoveDialog 对话框

IMPLEMENT_DYNAMIC(CMoveDialog, CDialogEx)

CMoveDialog::CMoveDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMoveDialog::IDD, pParent)
	, m_dx(0)
	, m_dy(0)
	, m_dz(0)
{

}

CMoveDialog::~CMoveDialog()
{
}

void CMoveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMoveDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMoveDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CMoveDialog 消息处理程序


void CMoveDialog::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	
}
