
// GUIDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GUI.h"
#include "GUIDlg.h"
#include "afxdialogex.h"
#include <string>
#include <fstream>
#include "../CompilerPrincipleProject/driver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGUIDlg 对话框



CGUIDlg::CGUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	snl_filepath = _T("");
	INIT_VALUE_EDIT_SCANNER_RESULT = _T("");
	INIT_VALUE_EDIT_PARSER_RESULT = _T("");
	snl_filetitle = _T("");
	snl_folderpath = _T("");
}

void CGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_EDIT_FILEPATH);
	DDX_Control(pDX, IDC_EDIT_SCANNER_RESULT, m_EDIT_SCANNER_RESULT);
	DDX_Control(pDX, IDC_EDIT_PARSER_RESULT, m_EDIT_PARSER_RESULT);
}

BEGIN_MESSAGE_MAP(CGUIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_FILEPATH, &CGUIDlg::OnBnClickedButtonChooseFilepath)
	ON_BN_CLICKED(IDOK, &CGUIDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_BEGIN_PARSER, &CGUIDlg::OnBnClickedButtonBeginParser)
	ON_BN_CLICKED(IDC_BUTTON_BEGIN_SCANNER, &CGUIDlg::OnBnClickedButtonBeginScanner)
	ON_BN_CLICKED(IDABOUT, &CGUIDlg::OnBnClickedAbout)
END_MESSAGE_MAP()


// CGUIDlg 消息处理程序

BOOL CGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	INIT_VALUE_EDIT_SCANNER_RESULT = "在此处显示词法分析结果——Token序列";
	INIT_VALUE_EDIT_PARSER_RESULT = "在此处显示语法分析结果——调用产生式\r\n进行推导的过程";
	m_EDIT_SCANNER_RESULT.SetWindowTextW(INIT_VALUE_EDIT_SCANNER_RESULT);
	m_EDIT_PARSER_RESULT.SetWindowTextW(INIT_VALUE_EDIT_PARSER_RESULT);
	table = new Table("productions.txt");
	scanner = nullptr;
	scan_finished = false;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGUIDlg::OnBnClickedButtonChooseFilepath()
{
	CFileDialog dlg(TRUE/*这个参数为TRUE就是“打开”对话框，为FALSE就是“保存”对话框*/, NULL/*默认文件类型*/, NULL/*默认文件名*/, OFN_HIDEREADONLY/*样式，这里设置为“隐藏只读”*/, _T("所有文件(*.*)|*.*||")/*文件类型列表*/, NULL, NULL, FALSE/*指定文件打开对话框是否为Vista样式*/);
	if (dlg.DoModal() == IDOK)//如果用户在文件对话框中点击了“确定”按钮
	{
		snl_filepath = dlg.GetPathName();//获取文件路径到snl_filepath
		auto idx = snl_filepath.ReverseFind('\\');
		snl_folderpath = snl_filepath.Mid(0, idx + 1);//+1取到反斜杠，不加1不取，获取文件夹路径到snl_folderpath
		snl_filetitle = dlg.GetFileTitle();//获取文件名到snl_filename
		m_EDIT_FILEPATH.SetWindowText(snl_filepath);//显示文件路径到编辑框
		m_EDIT_SCANNER_RESULT.SetWindowTextW(INIT_VALUE_EDIT_SCANNER_RESULT);
		m_EDIT_PARSER_RESULT.SetWindowTextW(INIT_VALUE_EDIT_PARSER_RESULT);
		scan_finished = false;
	}
}


void CGUIDlg::OnBnClickedOk()
{
	if (table != nullptr)
	    delete table;
	if (scanner != nullptr)
		delete scanner;
	CDialogEx::OnOK();
}


void CGUIDlg::OnBnClickedButtonBeginParser()//开始语法分析按钮
{
	if (scan_finished) {//如果词法分析已完成，则可以开始语法分析
		CString showline("开始语法分析\r\n");
		m_EDIT_PARSER_RESULT.SetWindowTextW(showline);
		vector<string> parser_linetext = driver(*table, tokenfilepath);
		for (const string& showstring: parser_linetext) {
			showline += showstring.data();
			showline += "\r\n";
		}
		showline += "语法分析完成";
		m_EDIT_PARSER_RESULT.SetWindowTextW(showline);
	}
	else {
		m_EDIT_PARSER_RESULT.SetWindowTextW(_T("请先完成词法分析！"));
	}
}


void CGUIDlg::OnBnClickedButtonBeginScanner()//开始词法分析按钮
{
	if (!snl_filepath.IsEmpty()) {
		if (scanner != nullptr)
			delete scanner;
		scanner = new Scanner(std::string(CW2A(snl_filepath.GetString())));
		tokenfilepath = CW2A(snl_folderpath.GetString());
		tokenfilepath += snl_filetitle + "_token.txt";
		scanner->getTokenList();
		scanner->printTokenList(tokenfilepath);
		std::ifstream tokenfile(tokenfilepath);
		if (tokenfile.is_open()) {
			CString showline;
			std::string showstring;
			while (std::getline(tokenfile, showstring, '\n')) {
				showline += showstring.data();//使用data函数完成string到CString的转化
				showline += "\r\n";
			}
			m_EDIT_SCANNER_RESULT.SetWindowTextW(showline);
			scan_finished = true;
		}
	}
	else {
		m_EDIT_SCANNER_RESULT.SetWindowTextW(_T("尚未选择SNL代码文件！"));
	}
}


void CGUIDlg::OnBnClickedAbout()
{
	this->MessageBox(_T("组号：2117-25-04\n组长：张    磊——词法分析程序\n组员：孙博文——构造LL(1)分析表，设计界面\n组员：张    康——语法分析驱动程序"),
		_T("制作人员名单"));
}
