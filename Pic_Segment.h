#ifndef _INSIDE_VISUAL_CPP_PIC_SEGMENT
#define _INSIDE_VISUAL_CPP_PIC_SEGMENT
#include "ImgCenterDib.h"

//图像分割类
class Pic_Segment:public ImgCenterDib
{
public:
	//输出图像每像素位数
	int m_nBitCountOut;

	//输出图像位图数据指针
	unsigned char * m_pImgDataOut;

	//输出图像颜色表
	LPRGBQUAD m_lpColorTableOut;
private:
	//输出图像的宽
	int m_imgWidthOut;

	//输出图像的高
	int m_imgHeightOut;

	//输出图像颜色表长度
	int m_nColorTableLengthOut;
public:
	//不带参数的构造函数
	Pic_Segment();

	//带参数的构造函数
	Pic_Segment(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		        unsigned char *pImgData);

	//析构函数
	~Pic_Segment();

	//以像素为单位返回输出图像的尺寸
	CSize GetDimensions();

	//Roberts算子
	void Roberts();

	//轮廓提取
	void ContourExtract();

};
#endif // _INSIDE_VISUAL_CPP_IMGSEGMENT
