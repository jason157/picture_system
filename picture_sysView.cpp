// picture_sysView.cpp : implementation of the CPicture_sysView class
//

#include "stdafx.h"
#include "picture_sys.h"
#include "Csplash.h"
#include "Cbtmap.h"
#include "ImgCenterDib.h"//dib类头文件
#include "SpecialEffectShow.h"//特效显示类
#include "picture_sysDoc.h"
#include "picture_sysView.h"
#include "GrayTrans.h"
#include "GeometryTrans.h"
#include "mainfrm.h"
#include "Pic_Enhance.h"
#include "Pic_Shape.h"
#include "Pic_Segment.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPicture_sysView

IMPLEMENT_DYNCREATE(CPicture_sysView, CScrollView)

BEGIN_MESSAGE_MAP(CPicture_sysView, CScrollView)
	//{{AFX_MSG_MAP(CPicture_sysView)
	ON_COMMAND(ID_scan, Onscan)
	ON_COMMAND(ID_slide, Onslide)
	ON_COMMAND(ID_Fadein, OnFadein)
	ON_COMMAND(ID_TOGRAY, OnTogray)
	ON_COMMAND(ID_Graytocolor, OnGraytocolor)
	ON_COMMAND(ID_BinTwo, OnBinTwo)
	ON_COMMAND(ID_Clock180, OnClock180)
	ON_COMMAND(ID_Clock90, OnClock90)
	ON_COMMAND(ID_Xmirror, OnXmirror)
	ON_COMMAND(ID_Ymirror, OnYmirror)
	ON_COMMAND(ID_AnticClock90, OnAnticClock90)
	ON_COMMAND(ID_Ruihua, OnRuihua)
	//ON_COMMAND(ID_CloseOperation, OnCloseOperation)
	//ON_COMMAND(ID_OpenOperation, OnOpenOperation)
	ON_COMMAND(ID_Outline, OnOutline)
	ON_COMMAND(ID_Roberts, OnRoberts)
//	ON_COMMAND(ID_TwoExpand, OnTwoExpand)
	//ON_COMMAND(ID_TwoRot, OnTwoRot)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicture_sysView construction/destruction

CPicture_sysView::CPicture_sysView()
{  Csplash wndSplash;
   wndSplash.Create(IDB_pstart);
   wndSplash.UpdateWindow(); //send WM_PAINT
   Sleep(2000);
   

	// TODO: add construction code here

}

CPicture_sysView::~CPicture_sysView()
{
}

BOOL CPicture_sysView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPicture_sysView drawing

void CPicture_sysView::OnDraw(CDC* pDC)
{
	//CPicture_sysDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//获取文档类指针
	CPicture_sysDoc* pDoc = GetDocument();

	//返回m_dib的指针
	ImgCenterDib *pDib=pDoc->GetPDib();

	//获取DIB的尺寸
	CSize sizeFileDib = pDib->GetDimensions();

	//显示DIB
	pDib->Draw(pDC, CPoint(0, 0), sizeFileDib);
	
	

}

/////////////////////////////////////////////////////////////////////////////
// CPicture_sysView printing
void CPicture_sysView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	//获取文档类指针
	CPicture_sysDoc* pDoc = GetDocument();

	//获取DIB的指针
	ImgCenterDib *pDib=pDoc->GetPDib();

	//根据DIB尺寸设置视窗大小
	if(pDib!=NULL)
    	SetScrollSizes(MM_TEXT, pDib->GetDimensions());
	else{
		//如果m_dib为空，则设置一个固定的尺寸
		CSize sizeTotal;
		sizeTotal.cx = sizeTotal.cy = 100;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}

}

BOOL CPicture_sysView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPicture_sysView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPicture_sysView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPicture_sysView diagnostics

#ifdef _DEBUG
void CPicture_sysView::AssertValid() const
{
	CView::AssertValid();
}

void CPicture_sysView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPicture_sysDoc* CPicture_sysView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPicture_sysDoc)));
	return (CPicture_sysDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPicture_sysView message handlers

void CPicture_sysView::Onscan() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();

	//只处理彩色图像或灰度图象
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"只处理彩色和灰度图像",MB_OK,0);
	  return ;
	}

	//定义SpecialEffectShow类的对象SpShow，用当前DIB数据为其初始化
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	//获得设备环境变量
	CClientDC aDC(this);

	//调用扫描程序，传递设备环境指针
	SpShow.Scan(&aDC);
	
}

void CPicture_sysView::Onslide() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"只处理彩色和灰度图像",MB_OK,0);
	  return ;
	}
	//定义SpecialEffectShow类的对象SpShow，用当前DIB数据为其初始化
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	CClientDC aDC(this);//获得设备环境变量
	SpShow.Slide(&aDC);//调用滑动显示程序，传递设备环境指针
	
}

void CPicture_sysView::OnFadein() 
{
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"只处理彩色和灰度图像",MB_OK,0);
	  return ;
	}

	//定义SpecialEffectShow类的对象SpShow，用当前DIB数据为其初始化
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	CClientDC aDC(this);//获得设备环境变量
	SpShow.FadeIn(&aDC);//调用渐进显示程序，传递设备环境指针
	
}

void CPicture_sysView::OnTogray() 
{
	// TODO: Add your command handler code here
	//获取文档类指针
	CPicture_sysDoc *pDoc=GetDocument();
	//获取ImgCenterDib类对象m_dib的指针，访问当前DIB数据
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理彩色图像
	if(pDib->m_nBitCount!=24){
		::MessageBox(0,"只处理彩色图像",MB_OK,0);
		return ;
	}
	
	//将pDib中的图像数据作为输入数据，调用带参数的构造函数，
	//定义GrayTrans类的对象graytrans
	GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//彩色变灰度格式
	graytrans.ColorToGray();
	
	//建立一个新视图，显示分割结果
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	
	//发送新建文件的消息，创建一个新的文档-视图
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	
	//获取新建视图指针
	CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	
	//获取相关联的新的文档类指针
	CPicture_sysDoc* pDocNew=pView->GetDocument();

	//获取新文档中的ImgCenterDib类对象指针
	ImgCenterDib *dibNew=pDocNew->GetPDib();

	//将变换后的输出图像作为新建文档的DIB进行显示
	dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
	
	//设置滚动窗口
	pView->OnInitialUpdate();


	//文档数据置脏，提示存盘信息
	pDocNew->SetModifiedFlag(TRUE);

	//各视图刷新显示
	pDocNew->UpdateAllViews(pView);
	
}

void CPicture_sysView::OnGraytocolor() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度图像
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"只处理灰度图像",MB_OK,0);
		return ;
	}
	
	//将pDib中的图像数据作为输入数据，调用带参数的构造函数，
	//定义GrayTrans类的对象graytrans
	GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//灰度变彩色格式
	graytrans.GrayToColor();
	
	//建立一个新视图，显示分割结果
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	CPicture_sysDoc* pDocNew=pView->GetDocument();
	ImgCenterDib *dibNew=pDocNew->GetPDib();
	dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
	pView->OnInitialUpdate();	
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	
}

void CPicture_sysView::OnBinTwo() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//异常判断
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
		::MessageBox(0,"只处理彩色和灰度图像",MB_OK,0);
		return ;
	}
	
	//将pDib中的图像数据作为输入数据，调用带参数的构造函数，
	//定义GrayTrans类的对象graytrans
	GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//调用Binary()对图像进行二值化，缺省状态下阈值为
	graytrans.Binary();
	
	//建立一个新视图，显示分割结果
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	CPicture_sysDoc* pDocNew=pView->GetDocument();
	ImgCenterDib *dibNew=pDocNew->GetPDib();
	dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
	pView->OnInitialUpdate();	
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	
}

void CPicture_sysView::OnClock180() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度和彩色图像
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	
	//定义GeometryTrans类的对象geoTrans，用当前DIB对其初始化
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//旋转180度
	geoTrans.Rotate180();
	
	//新建视图窗口，显示变换结果
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	CPicture_sysDoc* pDocNew=pView->GetDocument();
	ImgCenterDib *dibNew=pDocNew->GetPDib();
	dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,
		geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}

void CPicture_sysView::OnClock90() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度和彩色图像
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	
	//定义GeometryTrans类的对象geoTrans，用当前DIB对其初始化
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//顺时针90度
	geoTrans.Clockwise90();
	
	//新建视图窗口，显示变换结果
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	CPicture_sysDoc* pDocNew=pView->GetDocument();
	ImgCenterDib *dibNew=pDocNew->GetPDib();
	dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,
		geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}

void CPicture_sysView::OnXmirror() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度和彩色图像
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	
	//定义GeometryTrans类的对象geoTrans，用当前DIB对其初始化
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//水平镜像
	geoTrans.MirrorHori();
	
	//新建视图窗口，显示变换结果
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	CPicture_sysDoc* pDocNew=pView->GetDocument();
	ImgCenterDib *dibNew=pDocNew->GetPDib();
	dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,
		geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	
}

void CPicture_sysView::OnYmirror() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度和彩色图像
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	
	//定义GeometryTrans类的对象geoTrans，用当前DIB对其初始化
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//垂直镜像
	geoTrans.MirrorVerti();
	
	//新建视图窗口，显示变换结果
CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	CPicture_sysDoc* pDocNew=pView->GetDocument();
	ImgCenterDib *dibNew=pDocNew->GetPDib();
	dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,
		geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	
}

void CPicture_sysView::OnAnticClock90() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度和彩色图像
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	
	//定义GeometryTrans类的对象geoTrans，用当前DIB对其初始化
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//逆时针90度
	geoTrans.Anticlockwise90();
	
	//新建视图窗口，显示变换结果
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	CPicture_sysDoc* pDocNew=pView->GetDocument();
	ImgCenterDib *dibNew=pDocNew->GetPDib();
	dibNew->ReplaceDib(geoTrans.GetDimensions(),geoTrans.m_nBitCountOut,
		geoTrans.m_lpColorTable, geoTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	
}



void CPicture_sysView::OnRuihua()  //图像梯度锐化
{
	// TODO: Add your command handler code here
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"只处理灰度图像",MB_OK,0);
		return ;
	}
	
	Pic_Enhance imgnoise(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);

	unsigned char bThre=30;
	imgnoise.GradSharp(bThre);

	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	
	CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	CPicture_sysDoc* pDocNew=pView->GetDocument();
	ImgCenterDib *dibNew=pDocNew->GetPDib();
	
	dibNew->ReplaceDib(imgnoise.GetDimensions(),imgnoise.m_nBitCountOut,imgnoise.m_lpColorTable, imgnoise.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	
	Invalidate();	
	
}

/*void CPicture_sysView::OnCloseOperation() 
{
	// TODO: Add your command handler code here
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度图像
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"只处理灰度图像",MB_OK,0);
		return ;
	}
	
	//判断是否二值图像
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//如果图像的数据像素灰度值既不为0也不为255,则非二值图像
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//非二值图像
	if(!flag){
		::MessageBox(0,"需要输入二值图像",MB_OK,0);
		return ;
	}


	//定义形态学类的对象morph，并用当前DIB为其初始化
	Pic_Shape morph(size,pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);

	//形态学结构元素选择对话框
	MaskDefineDlg dlgPara;

	//缺省的结构元素模板
	dlgPara.m_defineMask[7]=1;
	dlgPara.m_defineMask[11]=1;
	dlgPara.m_defineMask[12]=1;
	dlgPara.m_defineMask[13]=1;
	dlgPara.m_defineMask[17]=1;
	if(dlgPara.DoModal()==IDOK){
		//验证结构元素的有效性
		if(ValidBinaryMorphMask(dlgPara.m_defineMask,5,5)==0){
			::MessageBox(0,"结构元素输入有误，只能是0和1的数，且至少有一个以上的1！",MB_OK,0);
			return;
		}

		//输入结构元素
		morph.InputMask(dlgPara.m_defineMask,5,5);

		//二值闭
		morph.BinaryClose();

		//新建视图，显示处理结果
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
		CPicture_sysDoc* pDocNew=pView->GetDocument();
		ImgCenterDib *dibNew=pDocNew->GetPDib();
		dibNew->ReplaceDib(morph.GetDimensions(),morph.m_nBitCountOut,morph.m_lpColorTableOut, morph.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);	
	}
	
	
}

void CPicture_sysView::OnOpenOperation() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	Picture_syDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度图像
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"只处理灰度图像",MB_OK,0);
		return ;
	}
	
	//判断是否二值图像
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//如果图像的数据像素灰度值既不为0也不为255,则非二值图像
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//非二值图像
	if(!flag){
		::MessageBox(0,"需要输入二值图像",MB_OK,0);
		return ;
	}


	//定义形态学类的对象morph，并用当前DIB为其初始化
	Pic_Shape morph(size,pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);

	//形态学结构元素选择对话框
	MaskDefineDlg dlgPara;

	//缺省的结构元素模板
	dlgPara.m_defineMask[7]=1;
	dlgPara.m_defineMask[11]=1;
	dlgPara.m_defineMask[12]=1;
	dlgPara.m_defineMask[13]=1;
	dlgPara.m_defineMask[17]=1;
	if(dlgPara.DoModal()==IDOK){
		//验证结构元素的有效性
		if(ValidBinaryMorphMask(dlgPara.m_defineMask,5,5)==0){
			::MessageBox(0,"结构元素输入有误，只能是0和1的数，且至少有一个以上的1！",MB_OK,0);
			return;
		}

		//输入结构元素
		morph.InputMask(dlgPara.m_defineMask,5,5);

		//二值开
		morph.BinaryOpen();

		//新建视图，显示处理结果
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CPicture_syView* pView=(CPicture_syView*)pFrame->MDIGetActive()->GetActiveView();
		CPicture_syDoc* pDocNew=pView->GetDocument();
		ImgCenterDib *dibNew=pDocNew->GetPDib();
		dibNew->ReplaceDib(morph.GetDimensions(),morph.m_nBitCountOut,morph.m_lpColorTableOut, morph.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);	
	}
	
}*/

void CPicture_sysView::OnOutline() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"只处理灰度",MB_OK,0);
		return ;
	}
	
	//判断是否二值图像，若图像有灰度值既不为0也不为255的像素,则非二值图
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255)
			{
				flag=0;
				break;
			}
		}
	}

	//非二值图像
	if(!flag){
		::MessageBox(0,"需要输入二值图像",MB_OK,0);
		return ;
	}

	//定义图像分割类对象segment，用当前DIB对其初始化
	Pic_Segment segment(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);

	//轮廓提取
	segment.ContourExtract();
	
	//新建视图，显示出力结果
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	CPicture_sysDoc* pDocNew=pView->GetDocument();
	ImgCenterDib *dibNew=pDocNew->GetPDib();	
	dibNew->ReplaceDib(segment.GetDimensions(),segment.m_nBitCountOut,
		           segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	
}

void CPicture_sysView::OnRoberts() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度和彩色图像
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	
	//定义分割类对象segment，并用当前DIB数据初始化
	Pic_Segment segment(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//Roberts算子
	segment.Roberts();
	
	//新建视图，显示分割结果

	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
    //发送创建新文件命令

	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	//新建的窗口置顶

	CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	CPicture_sysDoc* pDocNew=pView->GetDocument();
	ImgCenterDib *dibNew=pDocNew->GetPDib();
	dibNew->ReplaceDib(segment.GetDimensions(),segment.m_nBitCountOut,segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	
}

/*void CPicture_sysView::OnTwoExpand() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度图像
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"只处理灰度图像",MB_OK,0);
		return ;
	}
	
	//判断是否二值图像
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//如果图像的数据像素灰度值既不为0也不为255,则非二值图像
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//非二值图像
	if(!flag){
		::MessageBox(0,"需要输入二值图像",MB_OK,0);
		return ;
	}


	//定义形态学类的对象morph，并用当前DIB为其初始化
	Pic_Shape morph(size,pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);

	//形态学结构元素选择对话框
	MaskDefineDlg dlgPara;

	//缺省的结构元素模板
	dlgPara.m_defineMask[7]=1;
	dlgPara.m_defineMask[11]=1;
	dlgPara.m_defineMask[12]=1;
	dlgPara.m_defineMask[13]=1;
	dlgPara.m_defineMask[17]=1;
	if(dlgPara.DoModal()==IDOK){
		//验证结构元素的有效性
		if(ValidBinaryMorphMask(dlgPara.m_defineMask,5,5)==0){
			::MessageBox(0,"结构元素输入有误，只能是0和1的数，且至少有一个以上的1！",MB_OK,0);
			return;
		}

		//输入结构元素
		morph.InputMask(dlgPara.m_defineMask,5,5);

		//二值膨胀
		morph.BinaryDilation();

		//新建视图，显示处理结果
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
		CPicture_sysDoc* pDocNew=pView->GetDocument();
		ImgCenterDib *dibNew=pDocNew->GetPDib();
		dibNew->ReplaceDib(morph.GetDimensions(),morph.m_nBitCountOut,morph.m_lpColorTableOut, morph.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);	
	}
	
}

void CPicture_sysView::OnTwoRot() 
{
	// TODO: Add your command handler code here
	//获取文档类中m_dib的指针，访问当前DIB数据
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//只处理灰度图像
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"只处理灰度图像",MB_OK,0);
		return ;
	}
	
	//判断是否二值图像
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//如果图像的数据像素灰度值既不为0也不为255,则非二值图像
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//非二值图像
	if(!flag){
		::MessageBox(0,"需要输入二值图像",MB_OK,0);
		return ;
	}


	//定义形态学类的对象morph，并用当前DIB为其初始化
	Morphology morph(size,pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);

	//形态学结构元素选择对话框
	MaskDefineDlg dlgPara;

	//缺省的结构元素模板
	dlgPara.m_defineMask[7]=1;
	dlgPara.m_defineMask[11]=1;
	dlgPara.m_defineMask[12]=1;
	dlgPara.m_defineMask[13]=1;
	dlgPara.m_defineMask[17]=1;
	if(dlgPara.DoModal()==IDOK){
		//验证结构元素的有效性
		if(ValidBinaryMorphMask(dlgPara.m_defineMask,5,5)==0){
			::MessageBox(0,"结构元素输入有误，只能是0和1的数，且至少有一个以上的1！",MB_OK,0);
			return;
		}

		//输入结构元素
		morph.InputMask(dlgPara.m_defineMask,5,5);

		//二值腐蚀
		morph.BinaryErosion();

		//新建视图，显示处理结果
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
		CPicture_sysDoc* pDocNew=pView->GetDocument();
		ImgCenterDib *dibNew=pDocNew->GetPDib();
		dibNew->ReplaceDib(morph.GetDimensions(),morph.m_nBitCountOut,morph.m_lpColorTableOut, morph.m_pImgDataOut);
		pView->OnInitialUpdate();
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);	
	}

	
}*/
