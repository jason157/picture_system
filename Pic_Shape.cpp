
#include "stdafx.h"
#include "Pic_Shape.h"



////////////////////////
Pic_Shape::Pic_Shape()//无参数的构造函数，对成员变量进行初始化
{

	m_pImgDataOut=NULL;//输出图像位图数据指针为空

	m_lpColorTableOut=NULL;//输出图像颜色表指针为空
	
    m_nBitCountOut=0;//输出图像每像素位数为0	

	m_imgWidthOut=0;//输出图像的宽为0

	m_imgHeightOut=0;//输出图像的高为0

	m_maskBuf=NULL;//结构元素指针为空

	m_maskW=0;//结构元素宽为0

	m_maskH=0;//结构元素高为0
}


Pic_Shape::Pic_Shape(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
					   unsigned char *pImgData):
ImgCenterDib(size, nBitCount, lpColorTable, pImgData) //参数的构造函数，对成员变量进行初始化
{

	//输出图像格式与输入图像相同，此处直接在构造函数中分配输出图像
	//所需要的缓冲区，并填写输出图像的信息
    m_nBitCountOut=m_nBitCount;

	//输出图像颜色表处理
	m_lpColorTableOut=NULL;
	int colorTableLength=ComputeColorTabalLength(m_nBitCountOut);
	if(colorTableLength!=0){
    	m_lpColorTableOut=new RGBQUAD[colorTableLength];
		memcpy(m_lpColorTableOut,m_lpColorTable,
			sizeof(RGBQUAD)*colorTableLength);
	}

	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//申请输出图像所需要的缓冲区
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	m_maskBuf=NULL;//结构元素指针为空

	m_maskW=0;//结构元素宽为0

	m_maskH=0;//结构元素高为0

}


Pic_Shape::~Pic_Shape()
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

	//释放结构元素缓冲区
	if(m_maskBuf){
		delete []m_maskBuf;
		m_maskBuf=NULL;
	}
}


CSize Pic_Shape::GetDimensions()
{	
	if(m_pImgDataOut == NULL) return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}


/***********************************************************************
* 函数名称：
* InputMask()
*
*函数参数：
*  int *mask   -结构元素缓冲区指针
*  int maskW   -结构元素宽
*  int maskH   -结构元素高
*
*返回值：
*   无
*
*说明：结构元素输入函数，在调用其它函数前必须先调用此函数
***********************************************************************/
void Pic_Shape::InputMask(int *mask,int maskW, int maskH)
{
	if(m_maskBuf){
		delete []m_maskBuf;
		m_maskBuf=NULL;
	}

	//将输入的结构元素拷贝到m_maskBuf缓冲区中
	m_maskBuf=new int[maskW*maskH];
	int i, j;
	for(i=0;i<maskH;i++){
		for(j=0;j<maskW;j++){
			m_maskBuf[i*maskW+j]=mask[i*maskW+j];
		}
	}

	//为结构元素宽和高赋值
	m_maskW=maskW;
	m_maskH=maskH;
}

void Pic_Shape::BasicErosionForBinary(unsigned char *imgBufIn, 
					 unsigned char *imgBufOut,int imgWidth,int imgHeight,
					 int *maskBuf, int maskW, int maskH)//二值腐蚀基本运算
{
	//每行图像数据的字节数为4的倍数
	int lineByte=(imgWidth+3)/4*4;

	//把输入图像缓冲区的拷贝到输出图像缓冲区
	memcpy(imgBufOut,imgBufIn,lineByte*imgHeight);
	
	//定义变量
	int i,j,k,l;

	//标志变量
	int judge;

	//针对图像中每一个像素位置，判断是否结构元素能填入目标内部
	for(i=maskH/2;i<imgHeight-maskH/2;i++)
	{
		for(j=maskW/2;j<imgWidth-maskW/2;j++)
		{			
			//判断结构元素是否可以在当前点填入目标内部,1为可以,0为不可以
			judge=1;
			for(k=-maskH/2;k<=maskH/2;k++)
			{
				for(l=-maskW/2;l<=maskW/2;l++)
				{
					//如果当前结构元素位置为1,判断与对应图像上的像素点是否为非0
					if(maskBuf[(k+maskH/2)*maskW+l+maskW/2])
					{
						//如果图像当前象素为0,则没有击中该点,不是腐蚀的输出
						if(!*(imgBufIn+(i+k)*lineByte+j+l))
							judge=0;	
					}
				}
			}


			if(judge)
				*(imgBufOut+i*lineByte+j)=255;
			else
				*(imgBufOut+i*lineByte+j)=0;
		}
	}
}

void Pic_Shape::BasicDilationForBinary(unsigned char *imgBufIn,
					unsigned char *imgBufOut,int imgWidth,int imgHeight,
					 int *maskBuf, int maskW, int maskH)//二值膨胀的基本运算
{
	//每行图像数据的字节数为4的倍数
	int lineByte=(imgWidth+3)/4*4;

	//循环变量
	int i,j,k,l;

	//膨胀是对图像中目标补集的腐蚀，因此先求输入图像数据的补集
	for(i=0;i<imgHeight;i++){
		for(j=0;j<imgWidth;j++){
			*(imgBufIn+i*lineByte+j)=255-*(imgBufIn+i*lineByte+j);
		}
	}

	//膨胀是结构元素的对称集对补集的腐蚀,此处tempMask存放m_mask的对称集
	int *tempMask=new int[maskW*maskH];
	for(k=0;k<maskH;k++){
		for(l=0;l<maskW;l++){
			tempMask[k*maskW+l]=maskBuf[(maskH-1-k)*maskW+maskW-1-l];
		}
	}

	//标志变量
	int judge;

	//针对图像中每一个像素位置，判断是否结构元素能填入目标内部
	for(i=maskH/2;i<imgHeight-maskH/2;i++)
	{
		for(j=maskW/2;j<imgWidth-maskW/2;j++)
		{			
			//判断结构元素是否可以在当前点填入目标内部,1为可以,0为不可以
			judge=1;
			for(k=-maskH/2;k<=maskH/2;k++)
			{
				for(l=-maskW/2;l<=maskW/2;l++)
				{
					//如果当前结构元素位置为1,判断与对应图像上的像素点是否为非0
					if(tempMask[(k+maskH/2)*maskW+l+maskW/2])
					{
						if(!*(imgBufIn+(i+k)*lineByte+j+l))
							judge=0;	
					}
				}
			}


			if(judge)
				*(imgBufOut+i*lineByte+j)=255;
			else
				*(imgBufOut+i*lineByte+j)=0;
		}
	}

	//用结构元素对称集对目标补集腐蚀后,还要对结果再求一次补集,才是膨胀结果输出
	for(i=0;i<imgHeight;i++){
		for(j=0;j<imgWidth;j++){
			*(imgBufOut+i*lineByte+j)=255-*(imgBufOut+i*lineByte+j);
		}
	}

	//恢复原始数据
	for(i=0;i<imgHeight;i++){
		for(j=0;j<imgWidth;j++){
			*(imgBufIn+i*lineByte+j)=255-*(imgBufIn+i*lineByte+j);
		}
	}
	
	delete []tempMask;
}


void Pic_Shape::BinaryErosion()
{
	//如果没有结构元素输入，则返回
	if(m_maskBuf==NULL)
		return;

	//二值腐蚀
	BasicErosionForBinary(m_pImgData, m_pImgDataOut,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);

}


void Pic_Shape::BinaryDilation()
{
	//如果没有结构元素输入，则返回
	if(m_maskBuf==NULL)
		return;

	//二值膨胀
	BasicDilationForBinary(m_pImgData, m_pImgDataOut,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);
}



void Pic_Shape::BinaryOpen() //二值开运算
{
	//如果没有结构元素输入，则返回
	if(m_maskBuf==NULL)
		return;

	//灰度图像每行像素所占字节数
	int lineByte=(m_imgWidth+3)/4*4;

	//中间结果缓冲区申请,用来存放腐蚀后的中间结果
	unsigned char *buf=new unsigned char[lineByte*m_imgHeight];

	//先腐蚀
	BasicErosionForBinary(m_pImgData, buf,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);

	//后膨胀
	BasicDilationForBinary(buf, m_pImgDataOut,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);

	//释放缓冲区
	delete []buf;

}




void Pic_Shape::BinaryClose()//二值闭运算
{
	//如果没有结构元素输入，则返回
	if(m_maskBuf==NULL)
		return;

	//灰度图像每行像素所占字节数
	int lineByte=(m_imgWidth+3)/4*4;

	//中间结果缓冲区申请,用来存放腐蚀后的中间结果
	unsigned char *buf=new unsigned char[lineByte*m_imgHeight];

	//先膨胀
	BasicDilationForBinary(m_pImgData, buf,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);

	//后腐蚀
	BasicErosionForBinary(buf, m_pImgDataOut,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);

	//释放缓冲区
	delete []buf;
}

