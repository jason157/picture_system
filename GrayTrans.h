#ifndef _INSIDE_VISUAL_CPP_GRAYTRANS
#define _INSIDE_VISUAL_CPP_GRAYTRANS
#include "ImgCenterDib.h"

//�Ҷȱ任��
class GrayTrans:public ImgCenterDib
{
public:
	//���ͼ��ÿ����λ��
	int m_nBitCountOut;

	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;

	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;

private:
	//���ͼ��Ŀ�����Ϊ��λ
	int m_imgWidthOut;

	//���ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeightOut;

	//���ͼ����ɫ����
	int m_nColorTableLengthOut;

public:
	//���������Ĺ��캯��
	GrayTrans();

	//�������Ĺ��캯��
	GrayTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);

	//��������
	~GrayTrans();
	
	//������Ϊ��λ�������ͼ��Ŀ�͸�
	CSize GetDimensions();



	//��ɫ��Ҷȸ�ʽ
	void ColorToGray();

	//�Ҷȱ��ɫ��ʽ
	void GrayToColor();

	//��ֵ��
	void Binary(int threshold=128);

};
#endif // _INSIDE_VISUAL_CPP_GRAYTRANS

