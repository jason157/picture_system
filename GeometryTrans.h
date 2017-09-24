#ifndef _INSIDE_VISUAL_CPP_GeometryTrans
#define _INSIDE_VISUAL_CPP_GeometryTrans
#include "ImgCenterDib.h"

//���α任��
class GeometryTrans:public ImgCenterDib
{
public:
    //���ͼ��ÿ����λ��
	int m_nBitCountOut;

	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;

	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;
private:
	//���ͼ��Ŀ�
	int m_imgWidthOut;

	//���ͼ��ĸ�
	int m_imgHeightOut;

	//���ͼ����ɫ����
	int m_nColorTableLengthOut;

public:
	
	GeometryTrans();

	//�������Ĺ��캯��
	GeometryTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);

	//��������
	~GeometryTrans();

	//������Ϊ��λ�������ͼ��Ŀ�͸�
	CSize GetDimensions();

	//ƽ��
	void Move(int offsetX, int offsetY);

	//ˮƽ����
	void MirrorHori();

	//��ֱ����
	void MirrorVerti();
	
	//˳ʱ����ת90��
	void Clockwise90();

	//��ʱ����ת90��
	void Anticlockwise90();

	//��ת180
	void Rotate180();

	
};
#endif // _INSIDE_VISUAL_CPP_GeometryTrans