// SpecialEffectShow.cpp: implementation of the SpecialEffectShow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpecialEffectShow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SpecialEffectShow::SpecialEffectShow(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
					   unsigned char *pImgData)
					   :ImgCenterDib(size, nBitCount, lpColorTable, pImgData)
{

}

SpecialEffectShow::~SpecialEffectShow()
{     }

void SpecialEffectShow::Scan(CDC *pDC) //扫描显示一幅图象
{
	int bitmapWidth=GetDimensions().cx;//获得源图象的宽度，以象素为单位
	int bitmapHeight=GetDimensions().cy;//获得源图象的高度，以象素为单位

	CRect rect(0,0,bitmapWidth,bitmapHeight);//以源图象的尺寸创建一个矩形
	CBrush brush(RGB(255,255,255));	//设置画刷为白色
	pDC->FillRect(&rect,&brush);//将已经显示出来的原图象重新设置成白色，达到刷新屏幕的效果

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//为适应StretchDIBits函数的需要，将图像信息头指针强制转换为LPBITMAPINFO类型

	for(int j=0;j<bitmapHeight;j++)//扫描特效显示的具体算法
	{
		::StretchDIBits(pDC->GetSafeHdc(),
			0, j, bitmapWidth, 1,
			0, bitmapHeight-j, bitmapWidth, 1,
			m_pImgData, pBitmapInfo,
			DIB_RGB_COLORS, SRCCOPY);
		Sleep(3);//设置延时时间
	}
}

void SpecialEffectShow::Slide(CDC *pDC)
{
	int bitmapWidth=GetDimensions().cx;//获得源图象的宽度，以象素为单位
	int bitmapHeight=GetDimensions().cy;//获得源图象的高度，以象素为单位

	CRect rect(0,0,bitmapWidth,bitmapHeight);//以源图象的尺寸创建一个矩形
	CBrush brush(RGB(255,255,255));	//设置画刷为白色
	pDC->FillRect(&rect,&brush);//将已经显示出来的原图象重新设置成白色，达到刷新屏幕的效果

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//为适应StretchDIBits函数的需要，将图像信息头指针强制转换为LPBITMAPINFO类型

	for(int i=0;i<=bitmapWidth;i++)//滑动特效显示的具体算法
	{
		for(int j=0;j<=bitmapHeight;j=j+8)
		{
			::StretchDIBits(pDC->GetSafeHdc(),
				0,  j-8 ,  i+1, 8,
				bitmapWidth-i, bitmapHeight-j, i+1, 8,
				m_pImgData, pBitmapInfo,
				DIB_RGB_COLORS, SRCCOPY);
		}
		Sleep(3);//设置延时时间
	}
}

void SpecialEffectShow::FadeIn(CDC *pDC)
{
	int bitmapWidth=GetDimensions().cx;//获得源图象的宽度，以象素为单位
	int bitmapHeight=GetDimensions().cy;//获得源图象的高度，以象素为单位

	CRect rect(0,0,bitmapWidth,bitmapHeight);//以源图象的尺寸创建一个矩形
	CBrush brush(RGB(0,0,0));	//设置画刷为黑色
	pDC->FillRect(&rect,&brush);//将已经显示出来的原图象重新设置成黑色，达到刷新屏幕的效果

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//为适应StretchDIBits函数的需要，将图像信息头指针强制转换为LPBITMAPINFO类型

		
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;//每行像素占字节数，必须为4的倍数
	LPBYTE temp =new BYTE[bitmapHeight*lineByte];//在堆上分配内存存储临时图象数据
	memset (temp,0,bitmapHeight*lineByte);//初始置零

	for(int m=0;m<256;m++)
	{
		for(int j = 0; j < bitmapHeight; j++)
		{
			for(int i = 0; i < lineByte; i ++)
				temp[j*lineByte+i]=m_pImgData[j*lineByte+i]*m/256;
		}
		::StretchDIBits(pDC->GetSafeHdc(),
			0, 0, bitmapWidth, bitmapHeight,
			0, 0, bitmapWidth, bitmapHeight,
			temp, pBitmapInfo,DIB_RGB_COLORS, SRCCOPY);
		Sleep(3);//设置延时时间
	}
	delete [] temp;//释放堆上分配的内存
}

