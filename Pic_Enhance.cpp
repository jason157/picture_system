
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
* 函数名称：
* FindMedianValue(unsigned char* pbArray,int ArrayLen)
*
* 参数：
* unsigned char* pbArray	指向模板数组首地址的指针
* int ArrayLen             模板数组的长度
*
* 返回值：
* unsigned char
*
* 说明：
* /中值滤波中查找模版中像素中值的算法_利用冒泡排序
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
* 函数名称：
* MedianFilter(int FilterH, int FilterW, int FilterCX, int FilterCY)
*
* 参数：
* int FilterH     模板的高度        
* int FilterW     模板的宽度
* int FilterCX    模板的中心元素X坐标 ( < FilterW - 1)
* int FilterCY    模板的中心元素Y坐标 ( < FilterH - 1)
*
* 返回值：
* void
*
* 说明：
* 中值滤波的算法
*
**********************************************************************/

/*void Pic_Enhance::MedianFilter(int FilterH, int FilterW, int FilterCX, int FilterCY)
{
	unsigned char*	pSrc;
    unsigned char*	pDst;
    int		i,j,k,l;
	unsigned char*	value;         //指向滤波器数组的指针
	
	if(m_pImgDataOut != NULL)
	{
		delete []m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	//计算图像每行的字节数
   	int lineByte = (m_imgWidth * m_nBitCount / 8 + 3) / 4 * 4;
	
	if(m_nBitCount != 8)
	{
		AfxMessageBox("只能处理8位灰度图像!");
		return ;
	}
	//分配内存，以保存新图像
	m_nBitCountOut = m_nBitCount;
    int lineByteOut = (m_imgWidth * m_nBitCountOut / 8 + 3) / 4 * 4;
	if (!m_pImgDataOut)
	{
		//为处理后的图像分配内存空间
		m_pImgDataOut = new unsigned char[lineByteOut * m_imgHeight];
	}
	int pixelByte = m_nBitCountOut / 8;
	for(i =  0; i < m_imgHeight; i++){
		for(j = 0; j < m_imgWidth * pixelByte; j++)
			*(m_pImgDataOut + i * lineByteOut +j) = *(m_pImgData + i * lineByteOut + j);
	}
	//暂时分配内存，以保存滤波器数组
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
* 函数名称：
*   GradSharp()
* 参数:
*   BYTE  bThre		- 阈值
* 返回值:
*   BOOL            - 成功返回TRUE，否则返回FALSE。
* 说明:
*   该函数用来对图像进行梯度锐化,设定梯度锐化的阈值为30
/************************************************************************/
void Pic_Enhance::GradSharp(unsigned char Thre)
{
   	unsigned char*	pSrc;       // 指向源图像的指针
	unsigned char*	pDst; 	
	unsigned char*	pSrc1;
	unsigned char*	pSrc2;	
	LONG	i,j;				// 循环变量
	int	bTemp;
	if(m_pImgDataOut != NULL)
	{
		delete []m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
   	int lineByte = (m_imgWidth * m_nBitCount / 8 + 3) / 4 * 4;
	
	if(m_nBitCount != 8)
	{
		AfxMessageBox("只能处理8位灰度图像!");
		return ;
	}
	//创建要复制的图像区域
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
	
	for(i = 0; i < m_imgHeight; i++)		// 每行
	{		
		for(j = 0; j < m_imgWidth; j++)		// 每列
		{
			//指向新DIB第i行第j列的像素的指针
			pDst = m_pImgDataOut + lineByte * (m_imgHeight -1 - i) + j;
			
			// 进行梯度运算
			// 指向DIB第i行，第j个象素的指针
			pSrc  = (unsigned char*)m_pImgData + lineByte * (m_imgHeight - 1 - i) + j;			
			// 指向DIB第i+1行，第j个象素的指针
			pSrc1 = (unsigned char*)m_pImgData + lineByte * (m_imgHeight - 2 - i) + j;			
			// 指向DIB第i行，第j+1个象素的指针
			pSrc2 = (unsigned char*)m_pImgData + lineByte * (m_imgHeight - 1 - i) 
				+ j + 1;
			
			bTemp = abs((*pSrc)-(*pSrc1)) + abs((*pSrc)-(*pSrc2));
			
			// 判断是否小于阈值
			if ((bTemp+120) < 255)
			{
				// 判断是否大于阈值，对于小于情况，灰度值不变。
				if (bTemp >= Thre)
				{
					*pSrc = bTemp + 120;
				}
			}
			else
			{
				*pSrc = 255;
			}
			//生成新的DIB像素值
			*pDst = *pSrc;
		}
	}
	
}
