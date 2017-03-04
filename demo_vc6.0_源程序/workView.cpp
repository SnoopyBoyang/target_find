// workView.cpp : implementation of the CWorkView class
//

#include "stdafx.h"
#include "work.h"

#include "workDoc.h"
#include "workView.h"
#include "Cdib.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkView

IMPLEMENT_DYNCREATE(CWorkView, CScrollView)

BEGIN_MESSAGE_MAP(CWorkView, CScrollView)
	//{{AFX_MSG_MAP(CWorkView)
	ON_COMMAND(IDM_READ_PIC, OnReadPic)
	ON_COMMAND(IDM_TARGET, OnTarget)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkView construction/destruction

CWorkView::CWorkView()
{
	// TODO: add construction code here
  flag=0;
  target_iswork=0;
  target_pos=0;
}

CWorkView::~CWorkView()
{
}

BOOL CWorkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWorkView drawing
 int target_x;
   int target_y;
void CWorkView::OnDraw(CDC* pDC)
{
	CWorkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
    if(flag)
	{   
	   unsigned char b,g,r;
	   long length=0;
       length=Dib.m_pBitmapInfoHeader->biHeight*Dib.m_pBitmapInfoHeader->biWidth;
       long cnt=0;
       int remainder=0;

	  if(Dib.m_pBitmapInfoHeader->biWidth*3%4)
          remainder=4-Dib.m_pBitmapInfoHeader->biWidth*3%4;
	  else
		  remainder=0;

      unsigned char *p=new unsigned char[length+5];
      unsigned char *p1=new unsigned char[length+100];
	  int *p2=new int[length+100];

     for(int j=0;j<Dib.m_pBitmapInfoHeader->biHeight;j++)
     for(int i=0;i<Dib.m_pBitmapInfoHeader->biWidth;i++)
	 {
         b=*(Dib.m_pData+3*Dib.m_pBitmapInfoHeader->biWidth*j+remainder*j+3*i);
         g=*(Dib.m_pData+3*Dib.m_pBitmapInfoHeader->biWidth*j+remainder*j+3*i+1);
	     r=*(Dib.m_pData+3*Dib.m_pBitmapInfoHeader->biWidth*j+remainder*j+3*i+2);
		 *(p+cnt)=(unsigned char)(0.299*b+0.587*g+0.114*b);
   	     pDC->SetPixel(i,Dib.m_pBitmapInfoHeader->biHeight-j,RGB(*(p+cnt),*(p+cnt),*(p+cnt)));
		 cnt++;
	 }
    
    cnt=0;
     for(j=Dib.m_pBitmapInfoHeader->biHeight-1;j>=0;j--)
     for(int i=0;i<Dib.m_pBitmapInfoHeader->biWidth;i++)
	 {
	  *(p1+cnt++)=*(p+i+j*Dib.m_pBitmapInfoHeader->biWidth);
	 }

	int isfind=0;
  
   if(target_iswork)
   {

    target_find(p1,Dib.m_pBitmapInfoHeader->biHeight,Dib.m_pBitmapInfoHeader->biWidth,200,
	               &isfind,&target_x,&target_y);


      CPen pen(1,3,RGB(255,0,0));
	  pDC->SelectObject(&pen);
      
	  pDC->MoveTo(target_x-5,target_y);
	  pDC->LineTo(target_x+5,target_y);
     
      pDC->MoveTo(target_x,target_y-5);
	  pDC->LineTo(target_x,target_y+5);

	}
	   else
		    return ;
   }


}

     

	// TODO: add draw code for native data here


void CWorkView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, CSize(5000,5000),CSize(50,50),CSize(50,50));
	SetScrollPos(SB_VERT,0);
	SetScrollPos(SB_HORZ,0);
}

/////////////////////////////////////////////////////////////////////////////
// CWorkView printing

BOOL CWorkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWorkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWorkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWorkView diagnostics

#ifdef _DEBUG
void CWorkView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CWorkView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWorkDoc* CWorkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorkDoc)));
	return (CWorkDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkView message handlers

void CWorkView::OnReadPic() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE,_T("BMP"),_T("*.BMP"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("λͼ�ļ�(*.BMP)|*.BMP|"));	
    if(IDOK==dlg.DoModal ())
	{FileName.Format("%s",dlg.GetPathName());
	 flag=1;
	}
	else
		return;
	Dib.LoadFile(FileName);
	target_iswork=0;
   Invalidate();
	
}


void CWorkView::OnTarget() 
{
	// TODO: Add your command handler code here
  target_iswork=1;	
  Invalidate();
}





/*���� �����ж���
     unsigned char camera_data[150*50]={**} ;//��Ҷ�ֵͼ��
	 int gray_threshold=200; Ϊ�Ҷ���ֵ=200;
	 int isfind,target_x,target_y;�Զ�����������;���ڴ洢Ŀ���Ƿ��֣�Ŀ��x\y���� isfind=1 ����Ŀ�꣬isfind=0û����Ŀ��

  ���ú�����ʽΪ:
  target_find(camera_data,50,150,gray_threshold,&isfind,&target_x,&target_y);


���κ���Ҫ�ж���û���ҵ�Ŀ��ʱ��ֻҪif(isfind)
                                        {����Ŀ�꣬
										 target_x :x���ꣻ
										 target_y :y����;
										  
											.....}
									  else
										{....}

Ҳ����target_x ��target_y�洢���������һ���ҵ�Ŀ�������λ��
    
 

*/                     

// ͼ��Ҷȶ�ά���� camera_data, ��data_width, ��:data_height.  ��ֵ���ж���ֵ:gray_threshold,
// Ŀ���Ƿ񱻷���: is_find , Ŀ�����꣺target_x,target_y;
void target_find(unsigned char *camera_data,int data_height,int data_width,int gray_threshold,
	               int *is_find,int *target_x,int *target_y)
  {
      int x1,x2,y1,y2;                   //��ʾ��ͼ��x1,x2,y1,y2λ�� 
/*��ά��������ң����ϵ���ɨ�裬�����ҵ����������ȴ��Զ�λ��һ���ҵ���������Ŀ�귢�֣����Կ϶�����
	  1.��Ŀ����ڣ�����ִ������Ŀ����ϸ������Һ���������ֱ������������ʡʱ�䡣
	  2��Ŀ����ϸ����϶��ڸô�Ŀ�긽����
	  */
	  for(int i=0;i<data_height;i++)
	  {   for(int j=0;j<data_width;j++)
		 {
		    if(*(camera_data+i*data_width+j)>gray_threshold)
			{
			  x1=j;
			  y1=i;
			  *is_find=1;
			  break;
			}
		   else
		   {
		    x1=0;
		    y1=0;
			*is_find=0;
		   }	 
		 }
	 if(*is_find)
		 break;
     }
/*   ����Ŀ������ڶ�������ϵ��£�������ɨ�裬��ô�ʼ����Ŀ���λ�ô��������϶���Ŀ���Ե������һ��y1
	  ��ô�Ӹõ㿪ʼ����������ɨ�裬�ҵ�������䰵��һ�㣬�϶���Ŀ���Ե����һ��y2����ô������������е��y����
	  һ������ϸĿ����е�y����0.5*(y1+y2)��
	  ��ϸĿ���е� x����һ��;
	  */
     if(*is_find)
	 {
	   for(int i=x1;i<data_width;i++)
		  if(*(camera_data+y1*data_width+i)<gray_threshold)
		  {
		   x2=i;
		   break;
		  }
		  else
	       x2=data_width;
	  *target_x=(int)(0.5*(x1+x2));
	 

	 for(int j=y1;j<data_height;j++)
		 if(*(camera_data+x1+j*data_width)<gray_threshold)
		 {
		  y2=j;
		  break;
		 }
		else
		  y2=data_height;
      *target_y=(int)(0.5*(y1+y2));
	 }    

/////////////////////////////////////////

  }
void CWorkView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	str.Format("%d,%d  Ŀ��λ��:%d,%d",point.x,point.y,target_x,target_y);
	AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowText(str);

	CScrollView::OnMouseMove(nFlags, point);
}


