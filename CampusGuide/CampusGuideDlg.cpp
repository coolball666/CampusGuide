﻿
// CampusGuideDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CampusGuide.h"
#include "CampusGuideDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCampusGuideDlg 对话框



CCampusGuideDlg::CCampusGuideDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CAMPUSGUIDE_DIALOG, pParent)
{
	m_w = 1241;
	m_h = 816;
	m_x1 = 450;
	m_y1 = 10;
	m_x2 = m_w - 20;
	m_y2 = m_h - 20;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCampusGuideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCampusGuideDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_VIEW, &CCampusGuideDlg::OnBnClickedView)
	ON_EN_CHANGE(IDC_NAME, &CCampusGuideDlg::OnEnChangeName)
	ON_EN_CHANGE(IDC_PSW, &CCampusGuideDlg::OnEnChangePsw)
	ON_BN_CLICKED(IDC_LOGIN, &CCampusGuideDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_SHORTEST, &CCampusGuideDlg::OnBnClickedShortest)
	ON_BN_CLICKED(IDC_ALLPATH, &CCampusGuideDlg::OnBnClickedAllpath)
	ON_BN_CLICKED(IDC_HAMILTON, &CCampusGuideDlg::OnBnClickedHamilton)
	ON_BN_CLICKED(IDC_SAMECATEGORY, &CCampusGuideDlg::OnBnClickedSamecategory)
	ON_BN_CLICKED(IDC_NEARBY, &CCampusGuideDlg::OnBnClickedNearby)
	ON_BN_CLICKED(IDC_CHANGEMAP, &CCampusGuideDlg::OnBnClickedChangemap)
	ON_CBN_SELCHANGE(IDC_LOCATION, &CCampusGuideDlg::OnCbnSelchangeLocation)
	ON_CBN_SELCHANGE(IDC_CATEGORY, &CCampusGuideDlg::OnCbnSelchangeCategory)
	ON_CBN_SELCHANGE(IDC_START, &CCampusGuideDlg::OnCbnSelchangeStart)
	ON_CBN_SELCHANGE(IDC_DESTINATION, &CCampusGuideDlg::OnCbnSelchangeDestination)
	ON_EN_CHANGE(IDC_OUTPUT, &CCampusGuideDlg::OnEnChangeOutput)
END_MESSAGE_MAP()


// CCampusGuideDlg 消息处理程序

BOOL CCampusGuideDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetWindowPos(NULL, 0, 0, m_w, m_h, SWP_NOZORDER | SWP_NOMOVE);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCampusGuideDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCampusGuideDlg::OnPaint()
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
		CPaintDC dc(this);
		CRgn Rgn;
		Rgn.CreateRectRgn(m_x1, m_y1, m_x2, m_y2);
		dc.SelectClipRgn(&Rgn);
		DrawMap(&dc);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCampusGuideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CCampusGuideDlg::OnClose()
{
	// TODO: 关闭窗口
	CDialogEx::OnClose();
}


void CCampusGuideDlg::OnBnClickedView()
{
	//TODO: 查看所有景点
}


void CCampusGuideDlg::OnEnChangeName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnEnChangePsw()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnBnClickedShortest()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnBnClickedAllpath()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnBnClickedHamilton()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnBnClickedSamecategory()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnBnClickedNearby()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnBnClickedChangemap()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnCbnSelchangeLocation()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnCbnSelchangeCategory()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnCbnSelchangeStart()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnCbnSelchangeDestination()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCampusGuideDlg::OnEnChangeOutput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CCampusGuideDlg::DrawMap(CDC* pDC)
{
}

CCampusMap CCampusGuideDlg::GetMapFromJSON()
{
	return CCampusMap();
}
