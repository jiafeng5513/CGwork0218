#pragma once


// RoateCubeDialog 对话框

class RoateCubeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(RoateCubeDialog)

public:
	RoateCubeDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RoateCubeDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_degree;
	CString m_rc;
};
