#pragma once


// DlgRotate 对话框

class DlgRotate : public CDialogEx
{
	DECLARE_DYNAMIC(DlgRotate)

public:
	DlgRotate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgRotate();

// 对话框数据
	enum { IDD = IDD_DLGROTATE };
	double	m_RotateAngle;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
