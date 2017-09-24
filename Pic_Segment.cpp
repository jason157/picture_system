#include "stdafx.h"
#include "Pic_Segment.h"
#include "math.h"


Pic_Segment::Pic_Segment() //无参数的构造函数，对成员变量进行初始化
{
	m_pImgDataOut=NULL;//输出图像位图数据指针为空

	m_lpColorTableOut=NULL;//输出图像颜色表指针为空
	
	m_nColorTableLengthOut=0;//输出图像颜色表长度为0

    m_nBitCountOut=0;//输出图像每像素位数为0	

	m_imgWidthOut=0;//输出图像的宽为0

	m_imgHeightOut=0;//输出图像的高为0
}


Pic_Segment::Pic_Segment(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData):
ImgCenterDib(size, nBitCount, lpColorTable, pImgData)//带参数的构造函数，给定位图的大小、每像素位数、颜色表及位图数据
{
	m_pImgDataOut=NULL;//输出图像位图数据指针为空

	m_lpColorTableOut=NULL;//输出图像颜色表指针为空
	
	m_nColorTableLengthOut=0;//输出图像颜色表长度为0

    m_nBitCountOut=0;//输出图像每像素位数为0

	m_imgWidthOut=0;//输出图像的宽为0

	m_imgHeightOut=0;//输出图像的高为0
}

Pic_Segment::~Pic_Segment()
{
	//释放输出图像位图数据缓冲区
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//释放输出图像颜色表
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}
}


//返回输出图像的宽和高
CSize Pic_Segment::GetDimensions()
{	
	if(m_pImgDataOut == NULL) return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}



void Pic_Segment::Roberts()//Roberts边缘检测,适用于灰度和彩色图像
{
	//释放m_pImgDataOut指向的图像数据空间
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}
	//释放颜色表空间
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//输出图像与输入图像为同一类型
	m_nBitCountOut=m_nBitCount;

	//输出图像颜色表长度
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//输出图像颜色表，与输入图像相同
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//输出图像的宽高,与输入图像相等
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//每行像素所占字节数，输出图像与输入图像相同
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//申请输出图像缓冲区
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];


	//循环变量，图像的坐标
	int i,j;

	//每像素占字节数，输出图像与输入图像相同
	int pixelByte=m_nBitCount/8;

	//循环变量,遍历像素的每个通道,比如彩色图像三个分量
	int k;

	//中间变量
	int x, y, t;

	//Roberts算子
	for(i=1;i<m_imgHeight-1;i++){
		for(j=1;j<m_imgWidth-1;j++){
			for(k=0;k<pixelByte;k++){
				//x方向梯度
				x=*(m_pImgData+i*lineByte+j*pixelByte+k)
					-*(m_pImgData+(i+1)*lineByte+j*pixelByte+k);

				//y方向梯度
				y=*(m_pImgData+i*lineByte+j*pixelByte+k)
					-*(m_pImgData+i*lineByte+(j+1)*pixelByte+k);

				t=sqrt(x*x+y*y)+0.5;
				if(t>255)
				   t=255;
				//把t的值放进图形矩阵表中
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)=t;
			}
		}
	}
}


void Pic_Segment::ContourExtract()
{
	//只处理灰度图像
	if(m_nBitCount!=8)
		return;

	//释放m_pImgDataOut指向的图像数据空间
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}
	//释放颜色表空间
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//输出图像与输入图像为同一类型
	m_nBitCountOut=m_nBitCount;

	//输出图像颜色表长度
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//输出图像颜色表，与输入图像相同
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//输出图像的宽高,与输入图像相等
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//每行像素所占字节数，输出图像与输入图像相同
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//申请输出图像缓冲区
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//以下是轮廓提取代码

	//将输入图像数据拷贝置输出图像缓冲区
	memcpy(m_pImgDataOut,m_pImgData,lineByte*m_imgHeight);

	//存放黑点像素8邻域的像素灰度值
	int array[8];

	//数组求和
	int sum;

	//循环变量
	int i, j, k;

	//搜索图像中的黑点，不考虑边界上的点
	for(i=1;i<m_imgHeight-1;i++){
		for(j=1;j<m_imgWidth-1;j++){
			//找到一个黑点
			if(*(m_pImgData+i*lineByte+j)==0){
				//拷贝周围8邻域像素进array数组
		    	array[0]=*(m_pImgData+i*lineByte+j+1);
				array[1]=*(m_pImgData+(i+1)*lineByte+j+1);
				array[2]=*(m_pImgData+(i+1)*lineByte+j);
				array[3]=*(m_pImgData+(i+1)*lineByte+j-1);
				array[4]=*(m_pImgData+i*lineByte+j-1);
				array[5]=*(m_pImgData+(i-1)*lineByte+j-1);
				array[6]=*(m_pImgData+(i-1)*lineByte+j);
				array[7]=*(m_pImgData+(i-1)*lineByte+j+1);
				
				//对数组求和
				sum=0;
				for(k=0;k<8;k++)
					sum += array[k];

				//周围8邻域均为黑点，则输出图像对应像素置白色
				if(sum==0)
				   *(m_pImgDataOut+i*lineByte+j)=255;
				
			}
		}
	}

}

