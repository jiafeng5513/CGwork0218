// BGSMDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "CGwork0218.h"
#include "BGSMDialog.h"
#include "afxdialogex.h"


// BGSMDialog 对话框

IMPLEMENT_DYNAMIC(BGSMDialog, CDialogEx)

BGSMDialog::BGSMDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(BGSMDialog::IDD, pParent)
	, m_sx(0)
	, m_sy(0)
	, m_sz(0)
{

}

BGSMDialog::~BGSMDialog()
{
}

void BGSMDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sx);
	DDX_Text(pDX, IDC_EDIT2, m_sy);
	DDX_Text(pDX, IDC_EDIT3, m_sz);
}


BEGIN_MESSAGE_MAP(BGSMDialog, CDialogEx)
END_MESSAGE_MAP()


// BGSMDialog 消息处理程序
