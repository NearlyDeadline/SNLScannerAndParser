
// GUIDlg.h: 头文件
//

#pragma once

// CGUIDlg 对话框
class CGUIDlg : public CDialogEx
{
// 构造
public:
	CGUIDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EDIT_FILEPATH;
	afx_msg void OnBnClickedButtonChooseFilepath();
	CEdit m_EDIT_SCANNER_RESULT;
	CEdit m_EDIT_PARSER_RESULT;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonBeginParser();
	afx_msg void OnBnClickedButtonBeginScanner();
private:
	CString snl_filepath;
public:
	afx_msg void OnBnClickedAbout();
private:
	CString INIT_VALUE_EDIT_SCANNER_RESULT;
	CString INIT_VALUE_EDIT_PARSER_RESULT;
};
