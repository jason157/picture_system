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

void SpecialEffectShow::Scan(CDC *pDC) //ɨ����ʾһ��ͼ��
{
	int bitmapWidth=GetDimensions().cx;//���Դͼ��Ŀ�ȣ�������Ϊ��λ
	int bitmapHeight=GetDimensions().cy;//���Դͼ��ĸ߶ȣ�������Ϊ��λ

	CRect rect(0,0,bitmapWidth,bitmapHeight);//��Դͼ��ĳߴ紴��һ������
	CBrush brush(RGB(255,255,255));	//���û�ˢΪ��ɫ
	pDC->FillRect(&rect,&brush);//���Ѿ���ʾ������ԭͼ���������óɰ�ɫ���ﵽˢ����Ļ��Ч��

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//Ϊ��ӦStretchDIBits��������Ҫ����ͼ����Ϣͷָ��ǿ��ת��ΪLPBITMAPINFO����

	for(int j=0;j<bitmapHeight;j++)//ɨ����Ч��ʾ�ľ����㷨
	{
		::StretchDIBits(pDC->GetSafeHdc(),
			0, j, bitmapWidth, 1,
			0, bitmapHeight-j, bitmapWidth, 1,
			m_pImgData, pBitmapInfo,
			DIB_RGB_COLORS, SRCCOPY);
		Sleep(3);//������ʱʱ��
	}
}

void SpecialEffectShow::Slide(CDC *pDC)
{
	int bitmapWidth=GetDimensions().cx;//���Դͼ��Ŀ�ȣ�������Ϊ��λ
	int bitmapHeight=GetDimensions().cy;//���Դͼ��ĸ߶ȣ�������Ϊ��λ

	CRect rect(0,0,bitmapWidth,bitmapHeight);//��Դͼ��ĳߴ紴��һ������
	CBrush brush(RGB(255,255,255));	//���û�ˢΪ��ɫ
	pDC->FillRect(&rect,&brush);//���Ѿ���ʾ������ԭͼ���������óɰ�ɫ���ﵽˢ����Ļ��Ч��

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//Ϊ��ӦStretchDIBits��������Ҫ����ͼ����Ϣͷָ��ǿ��ת��ΪLPBITMAPINFO����

	for(int i=0;i<=bitmapWidth;i++)//������Ч��ʾ�ľ����㷨
	{
		for(int j=0;j<=bitmapHeight;j=j+8)
		{
			::StretchDIBits(pDC->GetSafeHdc(),
				0,  j-8 ,  i+1, 8,
				bitmapWidth-i, bitmapHeight-j, i+1, 8,
				m_pImgData, pBitmapInfo,
				DIB_RGB_COLORS, SRCCOPY);
		}
		Sleep(3);//������ʱʱ��
	}
}

void SpecialEffectShow::FadeIn(CDC *pDC)
{
	int bitmapWidth=GetDimensions().cx;//���Դͼ��Ŀ�ȣ�������Ϊ��λ
	int bitmapHeight=GetDimensions().cy;//���Դͼ��ĸ߶ȣ�������Ϊ��λ

	CRect rect(0,0,bitmapWidth,bitmapHeight);//��Դͼ��ĳߴ紴��һ������
	CBrush brush(RGB(0,0,0));	//���û�ˢΪ��ɫ
	pDC->FillRect(&rect,&brush);//���Ѿ���ʾ������ԭͼ���������óɺ�ɫ���ﵽˢ����Ļ��Ч��

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//Ϊ��ӦStretchDIBits��������Ҫ����ͼ����Ϣͷָ��ǿ��ת��ΪLPBITMAPINFO����

		
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;//ÿ������ռ�ֽ���������Ϊ4�ı���
	LPBYTE temp =new BYTE[bitmapHeight*lineByte];//�ڶ��Ϸ����ڴ�洢��ʱͼ������
	memset (temp,0,bitmapHeight*lineByte);//��ʼ����

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
		Sleep(3);//������ʱʱ��
	}
	delete [] temp;//�ͷŶ��Ϸ�����ڴ�
}

