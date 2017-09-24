// picture_sysView.cpp : implementation of the CPicture_sysView class
//

#include "stdafx.h"
#include "picture_sys.h"
#include "Csplash.h"
#include "Cbtmap.h"
#include "ImgCenterDib.h"//dib��ͷ�ļ�
#include "SpecialEffectShow.h"//��Ч��ʾ��
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
	//��ȡ�ĵ���ָ��
	CPicture_sysDoc* pDoc = GetDocument();

	//����m_dib��ָ��
	ImgCenterDib *pDib=pDoc->GetPDib();

	//��ȡDIB�ĳߴ�
	CSize sizeFileDib = pDib->GetDimensions();

	//��ʾDIB
	pDib->Draw(pDC, CPoint(0, 0), sizeFileDib);
	
	

}

/////////////////////////////////////////////////////////////////////////////
// CPicture_sysView printing
void CPicture_sysView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	//��ȡ�ĵ���ָ��
	CPicture_sysDoc* pDoc = GetDocument();

	//��ȡDIB��ָ��
	ImgCenterDib *pDib=pDoc->GetPDib();

	//����DIB�ߴ������Ӵ���С
	if(pDib!=NULL)
    	SetScrollSizes(MM_TEXT, pDib->GetDimensions());
	else{
		//���m_dibΪ�գ�������һ���̶��ĳߴ�
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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();

	//ֻ�����ɫͼ���Ҷ�ͼ��
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
	  return ;
	}

	//����SpecialEffectShow��Ķ���SpShow���õ�ǰDIB����Ϊ���ʼ��
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	//����豸��������
	CClientDC aDC(this);

	//����ɨ����򣬴����豸����ָ��
	SpShow.Scan(&aDC);
	
}

void CPicture_sysView::Onslide() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
	  return ;
	}
	//����SpecialEffectShow��Ķ���SpShow���õ�ǰDIB����Ϊ���ʼ��
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	CClientDC aDC(this);//����豸��������
	SpShow.Slide(&aDC);//���û�����ʾ���򣬴����豸����ָ��
	
}

void CPicture_sysView::OnFadein() 
{
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
	  return ;
	}

	//����SpecialEffectShow��Ķ���SpShow���õ�ǰDIB����Ϊ���ʼ��
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	CClientDC aDC(this);//����豸��������
	SpShow.FadeIn(&aDC);//���ý�����ʾ���򣬴����豸����ָ��
	
}

void CPicture_sysView::OnTogray() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ���ָ��
	CPicture_sysDoc *pDoc=GetDocument();
	//��ȡImgCenterDib�����m_dib��ָ�룬���ʵ�ǰDIB����
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ�����ɫͼ��
	if(pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ�����ɫͼ��",MB_OK,0);
		return ;
	}
	
	//��pDib�е�ͼ��������Ϊ�������ݣ����ô������Ĺ��캯����
	//����GrayTrans��Ķ���graytrans
	GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//��ɫ��Ҷȸ�ʽ
	graytrans.ColorToGray();
	
	//����һ������ͼ����ʾ�ָ���
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	
	//�����½��ļ�����Ϣ������һ���µ��ĵ�-��ͼ
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	
	//��ȡ�½���ͼָ��
	CPicture_sysView* pView=(CPicture_sysView*)pFrame->MDIGetActive()->GetActiveView();
	
	//��ȡ��������µ��ĵ���ָ��
	CPicture_sysDoc* pDocNew=pView->GetDocument();

	//��ȡ���ĵ��е�ImgCenterDib�����ָ��
	ImgCenterDib *dibNew=pDocNew->GetPDib();

	//���任������ͼ����Ϊ�½��ĵ���DIB������ʾ
	dibNew->ReplaceDib(graytrans.GetDimensions(),graytrans.m_nBitCountOut,graytrans.m_lpColorTableOut, graytrans.m_pImgDataOut);
	
	//���ù�������
	pView->OnInitialUpdate();


	//�ĵ��������࣬��ʾ������Ϣ
	pDocNew->SetModifiedFlag(TRUE);

	//����ͼˢ����ʾ
	pDocNew->UpdateAllViews(pView);
	
}

void CPicture_sysView::OnGraytocolor() 
{
	// TODO: Add your command handler code here
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//��pDib�е�ͼ��������Ϊ�������ݣ����ô������Ĺ��캯����
	//����GrayTrans��Ķ���graytrans
	GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//�Ҷȱ��ɫ��ʽ
	graytrans.GrayToColor();
	
	//����һ������ͼ����ʾ�ָ���
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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//�쳣�ж�
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
		return ;
	}
	
	//��pDib�е�ͼ��������Ϊ�������ݣ����ô������Ĺ��캯����
	//����GrayTrans��Ķ���graytrans
	GrayTrans graytrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//����Binary()��ͼ����ж�ֵ����ȱʡ״̬����ֵΪ
	graytrans.Binary();
	
	//����һ������ͼ����ʾ�ָ���
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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//��ת180��
	geoTrans.Rotate180();
	
	//�½���ͼ���ڣ���ʾ�任���
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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//˳ʱ��90��
	geoTrans.Clockwise90();
	
	//�½���ͼ���ڣ���ʾ�任���
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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//ˮƽ����
	geoTrans.MirrorHori();
	
	//�½���ͼ���ڣ���ʾ�任���
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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//��ֱ����
	geoTrans.MirrorVerti();
	
	//�½���ͼ���ڣ���ʾ�任���
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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����GeometryTrans��Ķ���geoTrans���õ�ǰDIB�����ʼ��
	GeometryTrans geoTrans(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//��ʱ��90��
	geoTrans.Anticlockwise90();
	
	//�½���ͼ���ڣ���ʾ�任���
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



void CPicture_sysView::OnRuihua()  //ͼ���ݶ���
{
	// TODO: Add your command handler code here
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
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
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж��Ƿ��ֵͼ��
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//���ͼ����������ػҶ�ֵ�Ȳ�Ϊ0Ҳ��Ϊ255,��Ƕ�ֵͼ��
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//�Ƕ�ֵͼ��
	if(!flag){
		::MessageBox(0,"��Ҫ�����ֵͼ��",MB_OK,0);
		return ;
	}


	//������̬ѧ��Ķ���morph�����õ�ǰDIBΪ���ʼ��
	Pic_Shape morph(size,pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);

	//��̬ѧ�ṹԪ��ѡ��Ի���
	MaskDefineDlg dlgPara;

	//ȱʡ�ĽṹԪ��ģ��
	dlgPara.m_defineMask[7]=1;
	dlgPara.m_defineMask[11]=1;
	dlgPara.m_defineMask[12]=1;
	dlgPara.m_defineMask[13]=1;
	dlgPara.m_defineMask[17]=1;
	if(dlgPara.DoModal()==IDOK){
		//��֤�ṹԪ�ص���Ч��
		if(ValidBinaryMorphMask(dlgPara.m_defineMask,5,5)==0){
			::MessageBox(0,"�ṹԪ����������ֻ����0��1��������������һ�����ϵ�1��",MB_OK,0);
			return;
		}

		//����ṹԪ��
		morph.InputMask(dlgPara.m_defineMask,5,5);

		//��ֵ��
		morph.BinaryClose();

		//�½���ͼ����ʾ������
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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	Picture_syDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж��Ƿ��ֵͼ��
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//���ͼ����������ػҶ�ֵ�Ȳ�Ϊ0Ҳ��Ϊ255,��Ƕ�ֵͼ��
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//�Ƕ�ֵͼ��
	if(!flag){
		::MessageBox(0,"��Ҫ�����ֵͼ��",MB_OK,0);
		return ;
	}


	//������̬ѧ��Ķ���morph�����õ�ǰDIBΪ���ʼ��
	Pic_Shape morph(size,pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);

	//��̬ѧ�ṹԪ��ѡ��Ի���
	MaskDefineDlg dlgPara;

	//ȱʡ�ĽṹԪ��ģ��
	dlgPara.m_defineMask[7]=1;
	dlgPara.m_defineMask[11]=1;
	dlgPara.m_defineMask[12]=1;
	dlgPara.m_defineMask[13]=1;
	dlgPara.m_defineMask[17]=1;
	if(dlgPara.DoModal()==IDOK){
		//��֤�ṹԪ�ص���Ч��
		if(ValidBinaryMorphMask(dlgPara.m_defineMask,5,5)==0){
			::MessageBox(0,"�ṹԪ����������ֻ����0��1��������������һ�����ϵ�1��",MB_OK,0);
			return;
		}

		//����ṹԪ��
		morph.InputMask(dlgPara.m_defineMask,5,5);

		//��ֵ��
		morph.BinaryOpen();

		//�½���ͼ����ʾ������
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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ����Ҷ�
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�",MB_OK,0);
		return ;
	}
	
	//�ж��Ƿ��ֵͼ����ͼ���лҶ�ֵ�Ȳ�Ϊ0Ҳ��Ϊ255������,��Ƕ�ֵͼ
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

	//�Ƕ�ֵͼ��
	if(!flag){
		::MessageBox(0,"��Ҫ�����ֵͼ��",MB_OK,0);
		return ;
	}

	//����ͼ��ָ������segment���õ�ǰDIB�����ʼ��
	Pic_Segment segment(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);

	//������ȡ
	segment.ContourExtract();
	
	//�½���ͼ����ʾ�������
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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ����ҶȺͲ�ɫͼ��
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24){
		::MessageBox(0,"ֻ����ҶȺͲ�ɫͼ��",MB_OK,0);
		return ;
	}
	
	//����ָ������segment�����õ�ǰDIB���ݳ�ʼ��
	Pic_Segment segment(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	
	//Roberts����
	segment.Roberts();
	
	//�½���ͼ����ʾ�ָ���

	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
    //���ʹ������ļ�����

	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	//�½��Ĵ����ö�

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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж��Ƿ��ֵͼ��
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//���ͼ����������ػҶ�ֵ�Ȳ�Ϊ0Ҳ��Ϊ255,��Ƕ�ֵͼ��
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//�Ƕ�ֵͼ��
	if(!flag){
		::MessageBox(0,"��Ҫ�����ֵͼ��",MB_OK,0);
		return ;
	}


	//������̬ѧ��Ķ���morph�����õ�ǰDIBΪ���ʼ��
	Pic_Shape morph(size,pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);

	//��̬ѧ�ṹԪ��ѡ��Ի���
	MaskDefineDlg dlgPara;

	//ȱʡ�ĽṹԪ��ģ��
	dlgPara.m_defineMask[7]=1;
	dlgPara.m_defineMask[11]=1;
	dlgPara.m_defineMask[12]=1;
	dlgPara.m_defineMask[13]=1;
	dlgPara.m_defineMask[17]=1;
	if(dlgPara.DoModal()==IDOK){
		//��֤�ṹԪ�ص���Ч��
		if(ValidBinaryMorphMask(dlgPara.m_defineMask,5,5)==0){
			::MessageBox(0,"�ṹԪ����������ֻ����0��1��������������һ�����ϵ�1��",MB_OK,0);
			return;
		}

		//����ṹԪ��
		morph.InputMask(dlgPara.m_defineMask,5,5);

		//��ֵ����
		morph.BinaryDilation();

		//�½���ͼ����ʾ������
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
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CPicture_sysDoc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//ֻ����Ҷ�ͼ��
	if(pDib->m_nBitCount!=8){
		::MessageBox(0,"ֻ����Ҷ�ͼ��",MB_OK,0);
		return ;
	}
	
	//�ж��Ƿ��ֵͼ��
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++){
		for(j=0; j<size.cx;j++){
			//���ͼ����������ػҶ�ֵ�Ȳ�Ϊ0Ҳ��Ϊ255,��Ƕ�ֵͼ��
			if(*(pDib->m_pImgData+i*lineByte+j)!=0
				&&*(pDib->m_pImgData+i*lineByte+j)!=255){
				flag=0;
				break;
			}
		}
	}
	//�Ƕ�ֵͼ��
	if(!flag){
		::MessageBox(0,"��Ҫ�����ֵͼ��",MB_OK,0);
		return ;
	}


	//������̬ѧ��Ķ���morph�����õ�ǰDIBΪ���ʼ��
	Morphology morph(size,pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);

	//��̬ѧ�ṹԪ��ѡ��Ի���
	MaskDefineDlg dlgPara;

	//ȱʡ�ĽṹԪ��ģ��
	dlgPara.m_defineMask[7]=1;
	dlgPara.m_defineMask[11]=1;
	dlgPara.m_defineMask[12]=1;
	dlgPara.m_defineMask[13]=1;
	dlgPara.m_defineMask[17]=1;
	if(dlgPara.DoModal()==IDOK){
		//��֤�ṹԪ�ص���Ч��
		if(ValidBinaryMorphMask(dlgPara.m_defineMask,5,5)==0){
			::MessageBox(0,"�ṹԪ����������ֻ����0��1��������������һ�����ϵ�1��",MB_OK,0);
			return;
		}

		//����ṹԪ��
		morph.InputMask(dlgPara.m_defineMask,5,5);

		//��ֵ��ʴ
		morph.BinaryErosion();

		//�½���ͼ����ʾ������
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
