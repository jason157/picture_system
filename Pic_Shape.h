#ifndef _INSIDE_VISUAL_CPP_PIC_SHAPE
#define _INSIDE_VISUAL_CPP_PIC_SHAPE
#include "ImgCenterDib.h"

//结构元素对,该结构专门为击中击不中变换而定义
struct ElementPair
{
	int hitElement[9];
	int missElement[9];
};

//形态学处理类
class Pic_Shape:public ImgCenterDib
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

	//结构元素（模板）指针
	int *m_maskBuf;

	//结构元素宽
	int m_maskW;

	//结构元素高
	int m_maskH;

	//定义8个方向的击中击不中变换结构元素对
	ElementPair m_hitMissMask[8];
public:
	//不带参数的构造函数
	Pic_Shape();

	//带参数的构造函数
	Pic_Shape(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);

	//析构函数
	~Pic_Shape();

	//返回输出图像的尺寸
	CSize GetDimensions();

	//结构元素（模板）输入函数，在调用其它形态学处理函数前必须先调用此函数
	void InputMask(int *mask,int maskW, int maskH);

	//二值腐蚀
	void BinaryErosion();

	//二值膨胀
	void BinaryDilation();

	//二值开
	void BinaryOpen();

	//二值闭
	void BinaryClose();


	
private:
	//二值腐蚀基本运算,背景为黑色,目标为白色,二值开、闭、形态学梯度等操作都要调
	//用这个函数
	void BasicErosionForBinary(unsigned char *imgBufIn, unsigned char *imgBufOut,
		int imgWidth,int imgHeight,int *maskBuf, int maskW, int maskH);

	//二值膨胀基本运算,背景为黑色,目标为白色,二值开、闭、形态学梯度等操作都要调用
	//这个函数
	void BasicDilationForBinary(unsigned char *imgBufIn, unsigned char *imgBufOut,
		int imgWidth,int imgHeight,int *maskBuf, int maskW, int maskH);
					
					
};
#endif // _INSIDE_VISUAL_CPP_Pic_Shape
