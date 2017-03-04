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
	CFileDialog dlg(TRUE,_T("BMP"),_T("*.BMP"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|"));	
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





/*例如 程序中定义
     unsigned char camera_data[150*50]={**} ;//存灰度值图像；
	 int gray_threshold=200; 为灰度阈值=200;
	 int isfind,target_x,target_y;自定义三个变量;由于存储目标是否发现，目标x\y坐标 isfind=1 发现目标，isfind=0没发现目标

  调用函数形式为:
  target_find(camera_data,50,150,gray_threshold,&isfind,&target_x,&target_y);


在任何需要判断有没有找到目标时候，只要if(isfind)
                                        {发现目标，
										 target_x :x坐标；
										 target_y :y坐标;
										  
											.....}
									  else
										{....}

也就是target_x ，target_y存储的是你最近一次找到目标的坐标位置
    
 

*/                     

// 图像灰度二维数组 camera_data, 宽：data_width, 高:data_height.  二值化判断阈值:gray_threshold,
// 目标是否被发现: is_find , 目标坐标：target_x,target_y;
void target_find(unsigned char *camera_data,int data_height,int data_width,int gray_threshold,
	               int *is_find,int *target_x,int *target_y)
  {
      int x1,x2,y1,y2;                   //看示意图：x1,x2,y1,y2位置 
/*二维数组从左到右，从上到下扫描，首先找到亮点区，先粗略定位，一旦找到亮点区后即目标发现，可以肯定两点
	  1.有目标存在：可以执行以下目标详细坐标查找函数，否则直接跳出来，节省时间。
	  2：目标详细坐标肯定在该粗目标附近。
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
/*   发现目标后，由于对数组从上到下，从左到右扫描，那么最开始发现目标的位置处（），肯定是目标边缘最上面一点y1
	  那么从该点开始，从上向下扫描，找到由亮点变暗的一点，肯定是目标边缘下面一点y2，那么这两点坐标的中点的y坐标
	  一定是详细目标的中点y坐标0.5*(y1+y2)。
	  详细目标中点 x坐标一样;
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
	str.Format("%d,%d  目标位置:%d,%d",point.x,point.y,target_x,target_y);
	AfxGetMainWnd()->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowText(str);

	CScrollView::OnMouseMove(nFlags, point);
}


