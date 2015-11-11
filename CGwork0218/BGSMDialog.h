#pragma once


// BGSMDialog 对话框

class BGSMDialog : public CDialogEx
{
	DECLARE_DYNAMIC(BGSMDialog)

public:
	BGSMDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BGSMDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_sx;
	double m_sy;
	double m_sz;
};
