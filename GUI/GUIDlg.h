
// GUIDlg.h: 头文件
//

#pragma once
#include "../CompilerPrincipleProject/table.h"
#include "../CompilerPrincipleProject/Scanner.h"
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
	CString snl_filepath;//SNL代码文件完整绝对路径名称，例：E:\\snltest.txt
public:
	afx_msg void OnBnClickedAbout();
private:
	CString INIT_VALUE_EDIT_SCANNER_RESULT;
	CString INIT_VALUE_EDIT_PARSER_RESULT;
	Table* table;
	Scanner* scanner;
	bool scan_finished;//词法分析完成
	CString snl_filetitle;//SNL代码文件名，不含扩展名，例：snltest
	CString snl_folderpath;//SNL代码文件夹路径，最后有一个反斜杠，例：E:\\
	//如果本行下面没有其他代码，不要删除本行注释，否则程序会报错
	std::string tokenfilepath;//token文件路径，包含路径和文件名和扩展名
};
