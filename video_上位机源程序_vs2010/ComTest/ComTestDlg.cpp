
// ComTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ComTest.h"
#include "ComTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CComTestDlg �Ի���




CComTestDlg::CComTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CComTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_get = _T("");
	m_send = _T("");
	flag=0;
	camera_switch=0;
}

void CComTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GET, m_get);
	DDX_Text(pDX, IDC_SEND, m_send);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_PIC, m_pic);
}

BEGIN_MESSAGE_MAP(CComTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CComTestDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CLOSE, &CComTestDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_SEND_BTN, &CComTestDlg::OnBnClickedSendBtn)
	ON_MESSAGE(WM_COMM_RXCHAR,OnCom)
//	ON_BN_CLICKED(IDC_BUTTON1, &CComTestDlg::OnBnClickedButton1)
	ON_WM_TIMER()
//	ON_BN_CLICKED(IDC_BUTTON2, &CComTestDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON1, &CComTestDlg::OnBnClickedButton1)
ON_STN_CLICKED(IDC_PIC, &CComTestDlg::OnStnClickedPic)
ON_BN_CLICKED(IDC_BUTTON_TIME_SEND_START, &CComTestDlg::OnBnClickedButtonTimeSendStart)
ON_BN_CLICKED(IDC_BUTTON_TIME_SEND_STOP, &CComTestDlg::OnBnClickedButtonTimeSendStop)
ON_WM_ERASEBKGND()
ON_WM_DESTROY()
END_MESSAGE_MAP()


// CComTestDlg ��Ϣ�������
int is_start=0;
int close_flag=0;
int ComPos=0;


struct pic_hwnd{
  HWND m_hwnd;
  int ms_delay;
};
int cameraWidth=0;
int cameraHeight=0;
int threshold=200;
int isfind=0;
CPoint target_pos=0;
unsigned char pic[200*200]={255};

struct ViewParameter{
     HWND hwnd;

	 
};
BOOL CComTestDlg::OnInitDialog()
{

	
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_START)->SetWindowText("����״̬:δ����������");
	pt.Hkey2ComboBox(m_combo);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CComTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CComTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	CDC *pDC=m_pic.GetDC();
	CBrush br(RGB(255,255,255));
	pDC->SelectObject(&br);
	CRect re;
	m_pic.GetClientRect(&re);
	pDC->Rectangle(re);

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CComTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void TargetFind()
{
	int x1=0,x2=0,y1=0,y2=0,x=0,y=0;
	int flag=0;
	for(int i=0;i<64;i++)
	{	for(int j=1;j<128;j++)
		{   
		    if(*(pic+i*128+j)>threshold)
			
			{
			  x1=j;
			  y1=i;
			  isfind=1;
			  break;
			}
			else
			{
			  x1=0;
			  y1=0;
			  isfind=0;
			}
		}
	   if(isfind)
		    break;

	}
	if(isfind)
	 {
	    for(int i=x1;i<128;i++)
		    if(*(pic+y1*128+i)<threshold)
		     {
		       x2=i;
			   break;
		     }
		    else
			   x2=128;
	  target_pos.x=(long)0.5*(x1+x2);

	    for(int j=y1;j<64;j++)
		    if(*(pic+j*128+x1)<threshold)
		   {
		     y2=j;
		     break;
		   }
		 else
			 y2=64;
	 target_pos.y=(long)0.5*(y1+y2);
	   
	}
	else 
		return;
}


DWORD WINAPI freshView(LPVOID param)
{
   ViewParameter *p=(ViewParameter*)param;
   HDC hdc=GetDC(p->hwnd);
   while(is_start)
   {
      
	  	CDC *pDC=CDC::FromHandle(hdc);//
	//	CDC *pDC=NULL;
	//	pDC->Attach(hdc);
	    CDC MemDC;
        CBitmap MemBitmap;
        MemDC.CreateCompatibleDC(NULL);
        MemBitmap.CreateCompatibleBitmap(pDC,128,64);      
	    MemDC.SelectObject(&MemBitmap);
		CPen pen1(1,2,RGB(255,0,0));
		MemDC.SelectObject(&pen1);
        MemDC.FillSolidRect(0,0,128,64,pDC->GetBkColor());	
      for(int i=0;i<64;i++)
         for(int j=0;j<128;j++)
	          MemDC.SetPixel(j,i,RGB(*(pic+i*128+j),*(pic+i*128+j),*(pic+i*128+j)));
		

	  MemDC.MoveTo(target_pos.x-2,target_pos.y);
	  MemDC.LineTo(target_pos.x+2,target_pos.y);
	  MemDC.MoveTo(target_pos.x,target_pos.y-2);
	  MemDC.LineTo(target_pos.x,target_pos.y+2);
		   pDC->BitBlt(0,0,128,64,&MemDC,0,0,SRCCOPY);
           MemBitmap.DeleteObject();
           MemDC.DeleteDC();
       


	   Sleep(500);
   }
  
   return 0;
}

void CComTestDlg::OnBnClickedOpen()
{    if(!close_flag)
	{
		ComPos=m_combo.GetCurSel();
     }

	if(pt.InitPort(this,m_nComArray[ComPos],115200,'N',8,1,EV_RXFLAG|EV_RXCHAR,1024))
	{
		pt.StartMonitoring();
		flag=1;
	
	}
	else
	{ flag=0;
	  MessageBox(_T("open error!"));
	  return;
	
	}
	is_start=1;
     ViewParameter *p=new ViewParameter;
	 p->hwnd=m_pic.GetSafeHwnd();
	 HANDLE hThread=CreateThread(NULL,0,freshView,(LPVOID)p,0,NULL);
     CloseHandle(hThread);
	
	GetDlgItem(IDC_OPEN)->EnableWindow(0);
	GetDlgItem(IDC_CLOSE)->EnableWindow(1);

	




	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CComTestDlg::OnBnClickedClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pt.ClosePort();
		GetDlgItem(IDC_OPEN)->EnableWindow(1);
	 GetDlgItem(IDC_CLOSE)->EnableWindow(0);
	 flag=0;
	 is_start=0;
	 close_flag=0;
}


void CComTestDlg::OnBnClickedSendBtn()
{
	if(!flag)
		return;
	UpdateData(1);

	pt.WriteToPort((LPCTSTR)m_send);
	m_send.Empty();
	//Sleep(200);
	//pt.SendData(m_send,strlen(m_send));
	//close_flag=1;

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
long cnt=0;
long is_col=0;
LRESULT CComTestDlg::OnCom(WPARAM ch,LPARAM lparam)
{  
	

	if(ch==115)
	    is_col=1;
		if(is_col)
		{
		  GetDlgItem(IDC_START)->SetWindowText("����״̬:������������...");
		 *(pic+cnt++)=(unsigned char)ch;
         if(cnt==(128*64-1))
	     cnt=0;
		}

   UpdateData(0);
 
	return 0;

}

//void CComTestDlg::OnBnClickedButton1()
//{
//	SetTimer(1,500,NULL);
//	//MessageBox(_T("aa"));
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


void CComTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(isfind)
  //  CString str;
      m_send.Format("%d,%d",target_pos.x,target_pos.y);
	else
		m_send="target miss";
	//str.Format("%d, %d",target_pos.x,target_pos.y);
 	pt.WriteToPort(m_send);
	m_send.Empty();
	CDialogEx::OnTimer(nIDEvent);
}


//void CComTestDlg::OnBnClickedButton2()
//{
//	KillTimer(1);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


void CComTestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDC *pDC=m_pic.GetDC();
	CBrush br(RGB(0,0,0));
	pDC->SelectObject(&br);
	CRect re;
	m_pic.GetClientRect(&re);
	pDC->Rectangle(re);


}


void CComTestDlg::OnStnClickedPic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CComTestDlg::OnBnClickedButtonTimeSendStart()
{
	SetTimer(1,300,NULL);
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CComTestDlg::OnBnClickedButtonTimeSendStop()
{
	KillTimer(1);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CComTestDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	return CDialogEx::OnEraseBkgnd(pDC);
}


void CComTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	is_start=0;
	// TODO: �ڴ˴������Ϣ����������
}
