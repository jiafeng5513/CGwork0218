// RoateCubeDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "CGwork0218.h"
#include "RoateCubeDialog.h"
#include "afxdialogex.h"


// RoateCubeDialog 对话框

IMPLEMENT_DYNAMIC(RoateCubeDialog, CDialogEx)

RoateCubeDialog::RoateCubeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(RoateCubeDialog::IDD, pParent)
	, m_degree(0)
	, m_rc(_T(""))
{

}

RoateCubeDialog::~RoateCubeDialog()
{
}

void RoateCubeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_degree);
	DDX_Text(pDX, IDC_EDIT2, m_rc);
}


BEGIN_MESSAGE_MAP(RoateCubeDialog, CDialogEx)
END_MESSAGE_MAP()


// RoateCubeDialog 消息处理程序
