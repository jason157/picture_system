#ifndef _INSIDE_VISUAL_CPP_PIC_SEGMENT
#define _INSIDE_VISUAL_CPP_PIC_SEGMENT
#include "ImgCenterDib.h"

//ͼ��ָ���
class Pic_Segment:public ImgCenterDib
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
	//���������Ĺ��캯��
	Pic_Segment();

	//�������Ĺ��캯��
	Pic_Segment(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		        unsigned char *pImgData);

	//��������
	~Pic_Segment();

	//������Ϊ��λ�������ͼ��ĳߴ�
	CSize GetDimensions();

	//Roberts����
	void Roberts();

	//������ȡ
	void ContourExtract();

};
#endif // _INSIDE_VISUAL_CPP_IMGSEGMENT
