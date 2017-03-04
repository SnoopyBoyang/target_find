
// ComTestDlg.h : ͷ�ļ�
//

#pragma once

#include "SerialPort.h"
// CComTestDlg �Ի���
class CComTestDlg : public CDialogEx
{
// ����
public:
	CComTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COMTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
