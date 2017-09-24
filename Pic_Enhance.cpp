
#include "stdafx.h"
#include "Pic_Enhance.h"
#include <math.h>
Pic_Enhance::Pic_Enhance()
{
	
	m_nColorTableLengthOut=0;
    m_nBitCountOut=0;
	m_pImgDataOut=NULL;
	m_lpColorTableOut=NULL;
	
}

Pic_Enhance::Pic_Enhance(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData):
ImgCenterDib(size, nBitCount, lpColorTable, pImgData)
{
	
    m_nBitCountOut=0;
	m_pImgDataOut=NULL;
	m_lpColorTableOut=NULL;
	m_nColorTableLengthOut=0;
}

Pic_Enhance::~Pic_Enhance()
{
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
		m_pImgDataOut=NULL;
	}
	if(m_lpColorTableOut==NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}
}


/**********************************************************************
*
* �������ƣ�
* FindMedianValue(unsigned char* pbArray,int ArrayLen)
*
* ������
* unsigned char* pbArray	ָ��ģ�������׵�ַ��ָ��
* int ArrayLen             ģ������ĳ���
*
* ����ֵ��
* unsigned char
*
* ˵����
* /��ֵ�˲��в���ģ����������ֵ���㷨_����ð������
*
**********************************************************************/

/*unsigned char Pic_Enhance::FindMedianValue(unsigned char* pbArray,int ArrayLen)
{
	int i,j;
	unsigned char Temp;
	
	for(j =0; j<ArrayLen; j++)
	{
		for(i =0; i <ArrayLen-j-1; i++)
		{
			if(pbArray[i]>pbArray[i+1])
			{
				Temp=pbArray[i];
				pbArray[i]=pbArray[i+1];
				pbArray[i+1]=Temp;
			}
			
		}
	}
	if ((ArrayLen&1)>0)
	{
		Temp=pbArray[(ArrayLen+1)/2];
	}
	else
	{
		Temp=(pbArray[ArrayLen/2]+pbArray[ArrayLen/2+1])/2;
	}
	
	return Temp;
}
/**********************************************************************
*
* �������ƣ�
* MedianFilter(int FilterH, int FilterW, int FilterCX, int FilterCY)
*
* ������
* int FilterH     ģ��ĸ߶�        
* int FilterW     ģ��Ŀ��
* int FilterCX    ģ�������Ԫ��X���� ( < FilterW - 1)
* int FilterCY    ģ�������Ԫ��Y���� ( < FilterH - 1)
*
* ����ֵ��
* void
*
* ˵����
* ��ֵ�˲����㷨
*
**********************************************************************/

/*void Pic_Enhance::MedianFilter(int FilterH, int FilterW, int FilterCX, int FilterCY)
{
	unsigned char*	pSrc;
    unsigned char*	pDst;
    int		i,j,k,l;
	unsigned char*	value;         //ָ���˲��������ָ��
	
	if(m_pImgDataOut != NULL)
	{
		delete []m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	//����ͼ��ÿ�е��ֽ���
   	int lineByte = (m_imgWidth * m_nBitCount / 8 + 3) / 4 * 4;
	
	if(m_nBitCount != 8)
	{
		AfxMessageBox("ֻ�ܴ���8λ�Ҷ�ͼ��!");
		return ;
	}
	//�����ڴ棬�Ա�����ͼ��
	m_nBitCountOut = m_nBitCount;
    int lineByteOut = (m_imgWidth * m_nBitCountOut / 8 + 3) / 4 * 4;
	if (!m_pImgDataOut)
	{
		//Ϊ������ͼ������ڴ�ռ�
		m_pImgDataOut = new unsigned char[lineByteOut * m_imgHeight];
	}
	int pixelByte = m_nBitCountOut / 8;
	for(i =  0; i < m_imgHeight; i++){
		for(j = 0; j < m_imgWidth * pixelByte; j++)
			*(m_pImgDataOut + i * lineByteOut +j) = *(m_pImgData + i * lineByteOut + j);
	}
	//��ʱ�����ڴ棬�Ա����˲�������
	value = new unsigned char[FilterH * FilterW];
	for (i = FilterCY; i < m_imgHeight - FilterH ; i++)//+ FilterCY + 1
	{
		for (j = FilterCX; j < m_imgWidth - FilterW ; j++)//+ FilterCX + 1
		{
			
			pDst = m_pImgDataOut + lineByte * (m_imgHeight - 1 - i) + j;
			for (k = 0; k < FilterH; k++)
			{
				for (l = 0; l < FilterW; l++)
				{
					pSrc = m_pImgData + lineByte * (m_imgHeight - l - i 
						+ FilterCY - k) + j - FilterCX + l;
					value[k * FilterW + l] = *pSrc;
				}
			}
			*pDst = FindMedianValue(value,FilterW * FilterH);
		}
	}
}*/

/*************************************************************************
* �������ƣ�
*   GradSharp()
* ����:
*   BYTE  bThre		- ��ֵ
* ����ֵ:
*   BOOL            - �ɹ�����TRUE�����򷵻�FALSE��
* ˵��:
*   �ú���������ͼ������ݶ���,�趨�ݶ��񻯵���ֵΪ30
/************************************************************************/
void Pic_Enhance::GradSharp(unsigned char Thre)
{
   	unsigned char*	pSrc;       // ָ��Դͼ���ָ��
	unsigned char*	pDst; 	
	unsigned char*	pSrc1;
	unsigned char*	pSrc2;	
	LONG	i,j;				// ѭ������
	int	bTemp;
	if(m_pImgDataOut != NULL)
	{
		delete []m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
   	int lineByte = (m_imgWidth * m_nBitCount / 8 + 3) / 4 * 4;
	
	if(m_nBitCount != 8)
	{
		AfxMessageBox("ֻ�ܴ���8λ�Ҷ�ͼ��!");
		return ;
	}
	//����Ҫ���Ƶ�ͼ������
	m_nBitCountOut = m_nBitCount;
    int lineByteOut = (m_imgWidth * m_nBitCountOut / 8 + 3) / 4 * 4;
	if (!m_pImgDataOut)
	{
		m_pImgDataOut = new unsigned char[lineByteOut * m_imgHeight];
	}
	
	int pixelByte = m_nBitCountOut / 8;
	for(i = 0; i < m_imgHeight; i++){
		for(j = 0; j < m_imgWidth * pixelByte; j++)
			*(m_pImgDataOut + i * lineByteOut + j) = *(m_pImgData + i * lineByteOut + j);
	}
	
	for(i = 0; i < m_imgHeight; i++)		// ÿ��
	{		
		for(j = 0; j < m_imgWidth; j++)		// ÿ��
		{
			//ָ����DIB��i�е�j�е����ص�ָ��
			pDst = m_pImgDataOut + lineByte * (m_imgHeight -1 - i) + j;
			
			// �����ݶ�����
			// ָ��DIB��i�У���j�����ص�ָ��
			pSrc  = (unsigned char*)m_pImgData + lineByte * (m_imgHeight - 1 - i) + j;			
			// ָ��DIB��i+1�У���j�����ص�ָ��
			pSrc1 = (unsigned char*)m_pImgData + lineByte * (m_imgHeight - 2 - i) + j;			
			// ָ��DIB��i�У���j+1�����ص�ָ��
			pSrc2 = (unsigned char*)m_pImgData + lineByte * (m_imgHeight - 1 - i) 
				+ j + 1;
			
			bTemp = abs((*pSrc)-(*pSrc1)) + abs((*pSrc)-(*pSrc2));
			
			// �ж��Ƿ�С����ֵ
			if ((bTemp+120) < 255)
			{
				// �ж��Ƿ������ֵ������С��������Ҷ�ֵ���䡣
				if (bTemp >= Thre)
				{
					*pSrc = bTemp + 120;
				}
			}
			else
			{
				*pSrc = 255;
			}
			//�����µ�DIB����ֵ
			*pDst = *pSrc;
		}
	}
	
}
