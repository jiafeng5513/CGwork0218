// MoveCubeDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "CGwork0218.h"
#include "MoveCubeDialog.h"
#include "afxdialogex.h"


// MoveCubeDialog 对话框

IMPLEMENT_DYNAMIC(MoveCubeDialog, CDialogEx)

MoveCubeDialog::MoveCubeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(MoveCubeDialog::IDD, pParent)
	, m_dx(0)
	, m_dy(0)
	, m_dz(0)
{

}

MoveCubeDialog::~MoveCubeDialog()
{
}

void MoveCubeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dx);
	DDX_Text(pDX, IDC_EDIT2, m_dy);
	DDX_Text(pDX, IDC_EDIT3, m_dz);
}


BEGIN_MESSAGE_MAP(MoveCubeDialog, CDialogEx)
END_MESSAGE_MAP()


// MoveCubeDialog 消息处理程序
