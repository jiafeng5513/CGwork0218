#pragma once


// MoveCubeDialog 对话框

class MoveCubeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MoveCubeDialog)

public:
	MoveCubeDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MoveCubeDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_dx;
	double m_dy;
	double m_dz;
};
