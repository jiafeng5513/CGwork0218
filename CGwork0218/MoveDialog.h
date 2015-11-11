#pragma once


// CMoveDialog 对话框

class CMoveDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMoveDialog)

public:
	CMoveDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMoveDialog();

// 对话框数据
	enum { IDD = IDD_MoveDialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 存储平移量
	double m_dx;
	double m_dy;
	double m_dz;
	afx_msg void OnBnClickedOk();
};
