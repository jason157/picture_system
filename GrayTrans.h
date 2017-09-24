#ifndef _INSIDE_VISUAL_CPP_GRAYTRANS
#define _INSIDE_VISUAL_CPP_GRAYTRANS
#include "ImgCenterDib.h"

//灰度变换类
class GrayTrans:public ImgCenterDib
{
public:
	//输出图像每像素位数
	int m_nBitCountOut;

	//输出图像位图数据指针
	unsigned char * m_pImgDataOut;

	//输出图像颜色表
	LPRGBQUAD m_lpColorTableOut;

private:
	//输出图像的宽，像素为单位
	int m_imgWidthOut;

	//输出图像的高，像素为单位
	int m_imgHeightOut;

	//输出图像颜色表长度
	int m_nColorTableLengthOut;

public:
	//不带参数的构造函数
	GrayTrans();

	//带参数的构造函数
	GrayTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);

	//析构函数
	~GrayTrans();
	
	//以像素为单位返回输出图像的宽和高
	CSize GetDimensions();



	//彩色变灰度格式
	void ColorToGray();

	//灰度变彩色格式
	void GrayToColor();

	//二值化
	void Binary(int threshold=128);

};
#endif // _INSIDE_VISUAL_CPP_GRAYTRANS

