
// CampusGuideDlg.h: 头文件
//

#pragma once


// CCampusGuideDlg 对话框
class CCampusGuideDlg : public CDialogEx
{
// 构造
public:
	CCampusGuideDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMPUSGUIDE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedView();
	afx_msg void OnEnChangeName();
	afx_msg void OnEnChangePsw();
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedShortest();
	afx_msg void OnBnClickedAllpath();
	afx_msg void OnBnClickedHamilton();
	afx_msg void OnBnClickedSamecategory();
	afx_msg void OnBnClickedNearby();
	afx_msg void OnBnClickedChangemap();
	afx_msg void OnCbnSelchangeLocation();
	afx_msg void OnCbnSelchangeCategory();
	afx_msg void OnCbnSelchangeStart();
	afx_msg void OnCbnSelchangeDestination();
	afx_msg void OnEnChangeOutput();
};
