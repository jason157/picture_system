#ifndef _INSIDE_VISUAL_CPP_GeometryTrans
#define _INSIDE_VISUAL_CPP_GeometryTrans
#include "ImgCenterDib.h"

//几何变换类
class GeometryTrans:public ImgCenterDib
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
	
	GeometryTrans();

	//带参数的构造函数
	GeometryTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);

	//析构函数
	~GeometryTrans();

	//以像素为单位返回输出图像的宽和高
	CSize GetDimensions();

	//平移
	void Move(int offsetX, int offsetY);

	//水平镜像
	void MirrorHori();

	//垂直镜像
	void MirrorVerti();
	
	//顺时针旋转90度
	void Clockwise90();

	//逆时针旋转90度
	void Anticlockwise90();

	//旋转180
	void Rotate180();

	
};
#endif // _INSIDE_VISUAL_CPP_GeometryTrans