
// CampusGuideDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CampusGuide.h"
#include "CampusGuideDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>

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
public:
	afx_msg void OnCbnSelchangeLocation();
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
	m_y1 = 40;
	m_x2 = m_w - 40;
	m_y2 = m_h - 40;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCampusGuideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOCATION, m_location);
	DDX_Control(pDX, IDC_CATEGORY, m_category);
	DDX_Control(pDX, IDC_START, m_start);
	DDX_Control(pDX, IDC_DESTINATION, m_destination);
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
	Campus = GetMapFromJSON();
	for (int i = 0; i < Campus.getVertexCnt(); i++)
	{
		m_location.AddString(Campus.getVertex(i).getName());
		m_start.AddString(Campus.getVertex(i).getName());
		m_destination.AddString(Campus.getVertex(i).getName());
	}
	for (int i = 0; i < Campus.getTypeCnt(); i++)
	{
		m_category.AddString(CString(Campus.getType(i).c_str()));
	}
	m_location.SetCurSel(0);
	m_start.SetCurSel(0);
	m_destination.SetCurSel(0);
	m_category.SetCurSel(0);
	GetDlgItem(IDC_CHANGEMAP)->EnableWindow(false);
	SetDlgItemText(IDC_NAME, "Guest");
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
	GetDlgItem(IDC_NAME)->GetWindowText(Username);
	GetDlgItem(IDC_PSW)->GetWindowText(Password);
	if (Username.MakeLower() == CString("admin") && Password.MakeLower() == CString("admin"))
	{
		AfxMessageBox("管理员登录成功");
		GetDlgItem(IDC_CHANGEMAP)->EnableWindow(true);
	}
	else
	{
		AfxMessageBox("账号密码错误");
	}
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
	WinExec("Notepad.exe D:\\VS\\CampusGuide\\CampusData.json", SW_SHOW);
	OnInitDialog();
	SetDlgItemText(IDC_NAME, Username);
	SetDlgItemText(IDC_PSW, Password);
	GetDlgItem(IDC_CHANGEMAP)->EnableWindow(true);
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
	int s = Campus.getScale();
	for (int i = 0; i < Campus.getVertexCnt(); i++)
	{
		CVertex V = Campus.getVertex(i);
		pDC->SetTextAlign(TA_BASELINE | TA_CENTER);
		CSize sz = pDC->GetTextExtent(V.getName());
		pDC->Rectangle((int)(V.getX() * s + m_x1) - sz.cx / 2 - 5, (int)(V.getY() * s + m_y1) - sz.cy / 2 - 10, (int)(V.getX() * s + m_x1) + sz.cx / 2 + 5, (int)(V.getY() * s + m_y1) + sz.cy / 2);
		pDC->TextOut((int)(V.getX() * s + m_x1), (int)(V.getY() * s + m_y1), V.getName());
	}
	for (int i = 0; i < Campus.getEdgeCnt(); i++)
	{
		CEdge E = Campus.getEdge(i);
		CVertex V1 = Campus.getVertex(E.getFrom()), V2 = Campus.getVertex(E.getTo());
		CSize sz1 = pDC->GetTextExtent(V1.getName()), sz2 = pDC->GetTextExtent(V2.getName());
		int x_1 = V1.getX() * s + m_x1, y_1 = V1.getY() * s + m_y1;
		int x_2 = V2.getX() * s + m_x1, y_2 = V2.getY() * s + m_y1;
		if (y_1 > y_2)
		{
			std::swap(y_1, y_2);
			std::swap(x_1, x_2);
		}
		pDC->MoveTo(x_1, y_1 + sz1.cy / 2);
		pDC->LineTo(x_2, y_2 - sz2.cy / 2);
	}
}

CCampusMap CCampusGuideDlg::GetMapFromJSON()
{
	rapidjson::Document document;
	char ReadBuffer[65536];
	FILE* fp;
	if (fopen_s(&fp, "D:\\VS\\CampusGuide\\CampusData.json", "rb") != 0)
	{
		// TODO: Exception Handle
		AfxMessageBox("文件打开失败");
		PostQuitMessage(0);
	}
	rapidjson::FileReadStream is(fp, ReadBuffer, sizeof(ReadBuffer));
	fclose(fp);
	document.ParseStream(is);
	return CCampusMap(document);
}
