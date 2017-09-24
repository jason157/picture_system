#include "stdafx.h"
#include "GeometryTrans.h"
#include "math.h"

#define max(a,b) (a>b?a:b)

GeometryTrans::GeometryTrans() //�޲����Ĺ��캯�����Գ�Ա�������г�ʼ��
{

	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0	
}


GeometryTrans::GeometryTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
							 unsigned char *pImgData):
ImgCenterDib(size, nBitCount, lpColorTable, pImgData)
{	
	//���ͼ��ÿ����λ��������ͼ����ͬ
    m_nBitCountOut=m_nBitCount;

	//���ͼ����ɫ����
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//���ͼ����ɫ��������ͼ����ͬ
	if(m_nColorTableLengthOut){
		//������ɫ��������������ɫ����
		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	else// ��ɫͼ��û����ɫ��
		 m_lpColorTableOut=NULL;

	//���ͼ��ָ��Ϊ��
	m_pImgDataOut=NULL;

	//���ͼ���͸���0
	m_imgWidthOut=0;
	m_imgHeightOut=0;
}


GeometryTrans::~GeometryTrans()//��������
{
	//�ͷ����ͼ��λͼ���ݻ�����
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//�ͷ����ͼ����ɫ��
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}
}




CSize GeometryTrans::GetDimensions()//���ؿ�͸�
{
	return CSize(m_imgWidthOut, m_imgHeightOut);
}




void GeometryTrans::MirrorHori() //ͼ��ˮƽ����
{
    //�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//���ͼ��Ŀ�͸�
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//ÿ�������ֽ��������ͼ��������ͼ�����
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//ѭ��������ͼ������
	int i,j;

	//ѭ������,���ص�ÿ��ͨ��
	int k;

	//ÿ�����ֽ��������ͼ��������ͼ�����
	int pixelByte=m_nBitCountOut/8;

	//ˮƽ����
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)
				=*(m_pImgData+i*lineByte+(m_imgWidth-1-j)*pixelByte+k);
		}
	}
}


void GeometryTrans::MirrorVerti() //ͼ��ֱ����
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//���ͼ��Ŀ�͸�
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//ÿ�������ֽ��������ͼ��������ͼ�����
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//ѭ��������ͼ������
	int i,j;

	//ѭ������,���ص�ÿ��ͨ��
	int k;

	//ÿ�����ֽ��������ͼ��������ͼ�����
	int pixelByte=m_nBitCountOut/8;

	//��ֱ����
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)
				=*(m_pImgData+(m_imgHeight-1-i)*lineByte+j*pixelByte+k);
		}
	}
}


void GeometryTrans::Clockwise90() //ͼ��˳ʱ����ת90��
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//����ͼ��ÿ�������ֽ���
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//���ͼ��Ŀ�͸�
	m_imgWidthOut=m_imgHeight;
	m_imgHeightOut=m_imgWidth;

	//���ͼ��ÿ�������ֽ���
	int lineByteOut=(m_imgWidthOut*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeightOut];

	//ѭ��������ͼ������
	int i,j;

	//ѭ������,���ص�ÿ��ͨ��
	int k;

	//ÿ�����ֽ��������ͼ��������ͼ�����
	int pixelByte=m_nBitCountOut/8;

	//˳ʱ��90��
	for(i=0;i<m_imgHeightOut;i++){
		for(j=0;j<m_imgWidthOut;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByteOut+j*pixelByte+k)
				=*(m_pImgData+j*lineByte+(m_imgWidth-1-i)*pixelByte+k);
		}
	}
}



void GeometryTrans::Anticlockwise90() //ͼ����ʱ����ת90��
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//����ͼ��ÿ�������ֽ���
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//���ͼ��Ŀ�͸�
	m_imgWidthOut=m_imgHeight;
	m_imgHeightOut=m_imgWidth;

	//���ͼ��ÿ�������ֽ���
	int lineByteOut=(m_imgWidthOut*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeightOut];

	//ѭ��������ͼ������
	int i,j;

	//ѭ������,���ص�ÿ��ͨ��
	int k;

	//ÿ�����ֽ��������ͼ��������ͼ�����
	int pixelByte=m_nBitCountOut/8;

	//��ʱ��90��
	for(i=0;i<m_imgHeightOut;i++){
		for(j=0;j<m_imgWidthOut;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByteOut+j*pixelByte+k)
				=*(m_pImgData+(m_imgHeight-1-j)*lineByte+i*pixelByte+k);
		}
	}
}


void GeometryTrans::Rotate180() //ͼ����ת180��
{
	//�ͷžɵ����ͼ�񻺳���
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}

	//���ͼ��Ŀ�͸�
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//ÿ�������ֽ��������ͼ��������ͼ�����
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//���뻺���������������
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//ѭ��������ͼ������
	int i,j;

	//ѭ������,���ص�ÿ��ͨ��
	int k;

	//ÿ�����ֽ��������ͼ��������ͼ�����
	int pixelByte=m_nBitCountOut/8;

	//��ת180��
	for(i=0;i<m_imgHeightOut;i++){
		for(j=0;j<m_imgWidthOut;j++){
			for(k=0;k<pixelByte;k++)
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)
				=*(m_pImgData+(m_imgHeight-1-i)*lineByte+(m_imgWidth-1-j)*pixelByte+k);
		}
	}
}

