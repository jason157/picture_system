#include "stdafx.h"
#include "GeometryTrans.h"
#include "math.h"

#define max(a,b) (a>b?a:b)

GeometryTrans::GeometryTrans() //无参数的构造函数，对成员变量进行初始化
{

	m_pImgDataOut=NULL;//输出图像位图数据指针为空

	m_lpColorTableOut=NULL;//输出图像颜色表指针为空
	
	m_nColorTableLengthOut=0;//输出图像颜色表长度为0

    m_nBitCountOut=0;//输出图像每像素位数为0	

	m_imgWidthOut=0;//输出图像的宽为0

	m_imgHeightOut=0;//输出图像的高为0	
}


GeometryTrans::GeometryTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
							 unsigned char *pImgData):
ImgCenterDib(size, nBitCount, lpColorTable, pImgData)
{	
	//输出图像每像素位数与输入图像相同
    m_nBitCountOut=m_nBitCount;

	//输出图像颜色表长度
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//输出图像颜色表与输入图像相同
	if(m_nColorTableLengthOut){
		//分配颜色表缓冲区，进行颜色表拷贝
		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	else// 彩色图像没有颜色表
		 m_lpColorTableOut=NULL;

	//输出图像指针为空
	m_pImgDataOut=NULL;

	//输出图像宽和高置0
	m_imgWidthOut=0;
	m_imgHeightOut=0;
}


GeometryTrans::~GeometryTrans()//析构函数
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




CSize GeometryTrans::GetDimensions()//返回款和高
{
	return CSize(m_imgWidthOut, m_imgHeightOut);
}




void GeometryTrans::MirrorHori() //图像水平镜像
{
    //释放旧的输出图像缓冲区
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//输出图像的宽和高
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//每行像素字节数，输出图像与输入图像相等
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//申请缓冲区，存放输出结果
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//循环变量，图像坐标
	int i,j;

	//循环变量,像素的每个通道
	int k;

	//每像素字节数，输出图像与输入图像相等
	int pixelByte=m_nBitCountOut/8;

	//水平镜像
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)
				=*(m_pImgData+i*lineByte+(m_imgWidth-1-j)*pixelByte+k);
		}
	}
}


void GeometryTrans::MirrorVerti() //图像垂直镜像
{
	//释放旧的输出图像缓冲区
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//输出图像的宽和高
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//每行像素字节数，输出图像与输入图像相等
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//申请缓冲区，存放输出结果
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//循环变量，图像坐标
	int i,j;

	//循环变量,像素的每个通道
	int k;

	//每像素字节数，输出图像与输入图像相等
	int pixelByte=m_nBitCountOut/8;

	//垂直镜像
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)
				=*(m_pImgData+(m_imgHeight-1-i)*lineByte+j*pixelByte+k);
		}
	}
}


void GeometryTrans::Clockwise90() //图像顺时针旋转90度
{
	//释放旧的输出图像缓冲区
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//输入图像每行像素字节数
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//输出图像的宽和高
	m_imgWidthOut=m_imgHeight;
	m_imgHeightOut=m_imgWidth;

	//输出图像每行像素字节数
	int lineByteOut=(m_imgWidthOut*m_nBitCount/8+3)/4*4;

	//申请缓冲区，存放输出结果
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeightOut];

	//循环变量，图像坐标
	int i,j;

	//循环变量,像素的每个通道
	int k;

	//每像素字节数，输出图像与输入图像相等
	int pixelByte=m_nBitCountOut/8;

	//顺时针90度
	for(i=0;i<m_imgHeightOut;i++){
		for(j=0;j<m_imgWidthOut;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByteOut+j*pixelByte+k)
				=*(m_pImgData+j*lineByte+(m_imgWidth-1-i)*pixelByte+k);
		}
	}
}



void GeometryTrans::Anticlockwise90() //图像逆时针旋转90度
{
	//释放旧的输出图像缓冲区
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//输入图像每行像素字节数
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//输出图像的宽和高
	m_imgWidthOut=m_imgHeight;
	m_imgHeightOut=m_imgWidth;

	//输出图像每行像素字节数
	int lineByteOut=(m_imgWidthOut*m_nBitCount/8+3)/4*4;

	//申请缓冲区，存放输出结果
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeightOut];

	//循环变量，图像坐标
	int i,j;

	//循环变量,像素的每个通道
	int k;

	//每像素字节数，输出图像与输入图像相等
	int pixelByte=m_nBitCountOut/8;

	//逆时针90度
	for(i=0;i<m_imgHeightOut;i++){
		for(j=0;j<m_imgWidthOut;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByteOut+j*pixelByte+k)
				=*(m_pImgData+(m_imgHeight-1-j)*lineByte+i*pixelByte+k);
		}
	}
}


void GeometryTrans::Rotate180() //图像旋转180度
{
	//释放旧的输出图像缓冲区
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//输出图像的宽和高
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//每行像素字节数，输出图像与输入图像相等
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//申请缓冲区，存放输出结果
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//循环变量，图像坐标
	int i,j;

	//循环变量,像素的每个通道
	int k;

	//每像素字节数，输出图像与输入图像相等
	int pixelByte=m_nBitCountOut/8;

	//旋转180度
	for(i=0;i<m_imgHeightOut;i++){
		for(j=0;j<m_imgWidthOut;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)
				=*(m_pImgData+(m_imgHeight-1-i)*lineByte+(m_imgWidth-1-j)*pixelByte+k);
		}
	}
}

