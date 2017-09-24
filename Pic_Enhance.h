#ifndef _INSIDE_VISUAL_CPP_Pic_Enhance
#define _INSIDE_VISUAL_CPP_Pic_Enhance
#include "ImgCenterDib.h"

//����ͼ����ǿ��
class Pic_Enhance:public ImgCenterDib  
{
public:
    int m_nBitCountOut;
	unsigned char * m_pImgDataOut;
	LPRGBQUAD m_lpColorTableOut;
	int m_nColorTableLengthOut;
public:
	//���캯��
	Pic_Enhance();
	Pic_Enhance(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);
    ~Pic_Enhance();
	
	//��ӽ�������
	//void AddPepperSaltNoise();
	
	//��Ӹ�˹����
	//void AddRandomNoise();
    
	//���þ�ֵģ�����ͼ��ƽ��
	//void AvgTemplate(int TempH, int TempW, int TempCX, int TempCY, float *fpTempArray, float fCoef);
	
	//��ֵ�˲�
	//BYTE FindMedianValue(unsigned char* lpbArray,int iArrayLen);
	//void MedianFilter(int iFilterH, int iFilterW, int iFilterCX, int iFilterCY);
	
	//������˹�� ת��Ϊģ������
	//void LapTemplate(int TempH, int TempW, int TempCX, int TempCY, float *fpTempArray, float fCoef);
	
	//�ݶ���
	void GradSharp(BYTE bThre);
	
	//ѡ����ģƽ��
//	void ChooseMask();
	
	//ͼ�������SNR
//	CString SNR(unsigned char* m_pImgSrcData);
	
	//ͼ���ֵ�����
	//CString PSNR(unsigned char* m_pImgSrcData);
	
};

#endif // _INSIDE_VISUAL_CPP_Pic_Enhance