
// ComTestDlg.h : 头文件
//

#pragma once

#include "SerialPort.h"
// CComTestDlg 对话框
class CComTestDlg : public CDialogEx
{
// 构造
public:
	CComTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COMTEST_DIALOG };

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
	CString m_get;
	CString m_send;
	
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedSendBtn();
	afx_msg LRESULT OnCom(WPARAM ch,LPARAM lparam);
	CSerialPort pt;
	CComboBox m_combo;
	int flag;
	int camera_switch;
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnBnClickedButton2();
	CStatic m_pic;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedPic();
	afx_msg void OnBnClickedButtonTimeSendStart();
	afx_msg void OnBnClickedButtonTimeSendStop();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
};
