#include "stdafx.h"
#include "GrayTrans.h"
#include "math.h"

/***********************************************************************
* 函数名称：
* GrayTrans()
*
*说明：无参数的构造函数，对成员变量进行初始化
***********************************************************************/
GrayTrans::GrayTrans()
{
	m_pImgDataOut=NULL;//输出图像位图数据指针为空

	m_lpColorTableOut=NULL;//输出图像颜色表指针为空
	
	m_nColorTableLengthOut=0;//输出图像颜色表长度为0

    m_nBitCountOut=0;//输出图像每像素位数为0	

	m_imgWidthOut=0;//输出图像的宽为0

	m_imgHeightOut=0;//输出图像的高为0
}

/***********************************************************************
* 函数名称：
* GrayTrans()
*
*函数参数：
*  CSize size -图像大小（宽、高）
*  int nBitCount  -每像素比特数
*  LPRGBQUAD lpColorTable  -颜色表指针
*  unsigned char *pImgData  -位图数据指针
*
*返回值：
*   无
*
*说明：本函数为带参数的构造函数，给定位图的大小、每像素位数、颜色表
*      及位图数据，调用ImgCenterDib()对基类成员初始化，作为输入图像数据
*      相关的数据成员,并初始化输出图像相关的数据成员
***********************************************************************/
GrayTrans::GrayTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
					 unsigned char *pImgData):
ImgCenterDib(size, nBitCount, lpColorTable, pImgData)
{

    m_pImgDataOut=NULL;//输出图像位图数据指针为空

	m_lpColorTableOut=NULL;//输出图像颜色表指针为空
	
	m_nColorTableLengthOut=0;//输出图像颜色表长度为0

    m_nBitCountOut=0;//输出图像每像素位数为0

	m_imgWidthOut=0;//输出图像的宽为0

	m_imgHeightOut=0;//输出图像的高为0
}


/***********************************************************************
* 函数名称：
*   ~GrayTrans()

*
*说明：析构函数，释放资源
***********************************************************************/
GrayTrans::~GrayTrans()
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

/***********************************************************************
* 函数名称：
* GetDimensions()
*
*函数参数：
*  无
*
*返回值：
*   图像的尺寸，用CSize类型表达
*
*说明：返回输出图像的宽和高
***********************************************************************/
CSize GrayTrans::GetDimensions()
{	
	if(m_pImgDataOut == NULL) return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}





void GrayTrans::ColorToGray()//灰值化
{
	//若灰度图像,则返回
	if(m_nBitCount==8) return;

	//释放旧的输出图像数据及颜色表缓冲区
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
		m_pImgDataOut=NULL;
	}
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//灰值化后,每像素位数为8比特
	m_nBitCountOut=8;

	//颜色表长度
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//申请颜色表缓冲区,生成灰度图像的颜色表
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		for(int i=0; i<m_nColorTableLengthOut;i++){
			m_lpColorTableOut[i].rgbBlue=i;
			m_lpColorTableOut[i].rgbGreen=i;
			m_lpColorTableOut[i].rgbRed=i;
			m_lpColorTableOut[i].rgbReserved=0;
		}
	}

	//输入图像每像素字节数,彩色图像为3字节/像素
	int pixelByteIn=3;
	
	//输入图像每行像素所占字节数,必须是4的倍数
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;

	//输出图像的宽高,与输入图像相等
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//输出图像每行像素所占字节数,必须是4的倍数
	int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

	//申请输出图像位图数据缓冲区
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];

	//循环变量,图像的坐标
	int i,j;

	//根据灰值化公式为输出图像赋值
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++)
			*(m_pImgDataOut+i*lineByteOut+j)=0.11**(m_pImgData+i*lineByteIn+j*pixelByteIn+0)
		        	+0.59**(m_pImgData+i*lineByteIn+j*pixelByteIn+1)
		        	+0.30**(m_pImgData+i*lineByteIn+j*pixelByteIn+2)+0.5;
	}

}


void GrayTrans::Binary(int threshold)
{
	//对于灰度图像
	if(m_nBitCount==8){
		//释放旧的输出图像数据及颜色表缓冲区
		if(m_pImgDataOut!=NULL){
			delete []m_pImgDataOut;
			m_pImgDataOut=NULL;
		}
		if(m_lpColorTableOut!=NULL){
			delete []m_lpColorTableOut;
			m_lpColorTableOut=NULL;
		}
		//输出图像的每像素位数、颜色表长度
		m_nBitCountOut=m_nBitCount;
		m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
		
		//申请输出图像颜色表缓冲区，并将输入图像颜色表拷贝至输出图像颜色表中
		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
		
		//输出图像的宽高,与输入图像相等
		m_imgWidthOut=m_imgWidth;
		m_imgHeightOut=m_imgHeight;
		
		
		//图像每行像素所占字节数，输入图像与输出图像每行像素所占字节数相等
		int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

		//申请输出图像位图数据缓冲区
		m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

		//循环变量，图像的坐标
		int i,j;

		//二值化
		for(i=0;i<m_imgHeight;i++){
			for(j=0;j<m_imgWidth;j++){
				if(*(m_pImgData+i*lineByte+j)<threshold)
    				*(m_pImgDataOut+i*lineByte+j)=0;
				else
					*(m_pImgDataOut+i*lineByte+j)=255;
			}
		}
	}
	else{

		//若是彩色图像,先变成灰度格式，变换后m_pImgDataOut已经申请了内存，
        //并存放了灰度图像数据
		ColorToGray();

		//输出图像每行像素所占字节数，输入图像与输出图像每行像素所占字节数不等
		int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

		//循环变量，图像的坐标
		int i,j;

		//二值化
		for(i=0;i<m_imgHeight;i++){
			for(j=0;j<m_imgWidth;j++)
				if(*(m_pImgDataOut+i*lineByteOut+j)<threshold)
					*(m_pImgDataOut+i*lineByteOut+j)=0;
				else
					*(m_pImgDataOut+i*lineByteOut+j)=255;
		}
	}
	
}


void GrayTrans::GrayToColor()//灰度图像变成彩色格式
{
	//若是彩色格式，则返回
	if(m_nBitCount==24) return;

	//释放旧的输出图像数据及颜色表缓冲区
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
		m_pImgDataOut=NULL;
	}
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//输出图像每像素位数为24比特
	m_nBitCountOut=24;

	//彩色图像颜色表长度为0，即无颜色表
	m_nColorTableLengthOut=0;

	//输入的灰度图像每行像素所占字节数，必须为4的倍数
	int lineByteIn=(m_imgWidth+3)/4*4;

	//输出图像的宽高,与输入图像相等
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//输出的彩色图像每行像素所占字节数，必须为4的倍数
	int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

	//申请输出图像位图数据缓冲区
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];

	//i,j为图像坐标循环变量，k为彩色图像三个通道的循环变量
	int i,j,k;

	//灰度变彩色
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			//用像素灰度值为彩色格式中每个通道赋值，三个通道数值相等
			for(k=0;k<3;k++)
			  *(m_pImgDataOut+i*lineByteOut+j*3+k)=*(m_pImgData+i*lineByteIn+j);
		}
	}
}


