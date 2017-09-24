
#include "stdafx.h"
#include "Pic_Shape.h"



////////////////////////
Pic_Shape::Pic_Shape()//�޲����Ĺ��캯�����Գ�Ա�������г�ʼ��
{

	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0

	m_maskBuf=NULL;//�ṹԪ��ָ��Ϊ��

	m_maskW=0;//�ṹԪ�ؿ�Ϊ0

	m_maskH=0;//�ṹԪ�ظ�Ϊ0
}


Pic_Shape::Pic_Shape(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
					   unsigned char *pImgData):
ImgCenterDib(size, nBitCount, lpColorTable, pImgData) //�����Ĺ��캯�����Գ�Ա�������г�ʼ��
{

	//���ͼ���ʽ������ͼ����ͬ���˴�ֱ���ڹ��캯���з������ͼ��
	//����Ҫ�Ļ�����������д���ͼ�����Ϣ
    m_nBitCountOut=m_nBitCount;

	//���ͼ����ɫ����
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

	//�������ͼ������Ҫ�Ļ�����
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	m_maskBuf=NULL;//�ṹԪ��ָ��Ϊ��

	m_maskW=0;//�ṹԪ�ؿ�Ϊ0

	m_maskH=0;//�ṹԪ�ظ�Ϊ0

}


Pic_Shape::~Pic_Shape()
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

	//�ͷŽṹԪ�ػ�����
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
* �������ƣ�
* InputMask()
*
*����������
*  int *mask   -�ṹԪ�ػ�����ָ��
*  int maskW   -�ṹԪ�ؿ�
*  int maskH   -�ṹԪ�ظ�
*
*����ֵ��
*   ��
*
*˵�����ṹԪ�����뺯�����ڵ�����������ǰ�����ȵ��ô˺���
***********************************************************************/
void Pic_Shape::InputMask(int *mask,int maskW, int maskH)
{
	if(m_maskBuf){
		delete []m_maskBuf;
		m_maskBuf=NULL;
	}

	//������ĽṹԪ�ؿ�����m_maskBuf��������
	m_maskBuf=new int[maskW*maskH];
	int i, j;
	for(i=0;i<maskH;i++){
		for(j=0;j<maskW;j++){
			m_maskBuf[i*maskW+j]=mask[i*maskW+j];
		}
	}

	//Ϊ�ṹԪ�ؿ�͸߸�ֵ
	m_maskW=maskW;
	m_maskH=maskH;
}

void Pic_Shape::BasicErosionForBinary(unsigned char *imgBufIn, 
					 unsigned char *imgBufOut,int imgWidth,int imgHeight,
					 int *maskBuf, int maskW, int maskH)//��ֵ��ʴ��������
{
	//ÿ��ͼ�����ݵ��ֽ���Ϊ4�ı���
	int lineByte=(imgWidth+3)/4*4;

	//������ͼ�񻺳����Ŀ��������ͼ�񻺳���
	memcpy(imgBufOut,imgBufIn,lineByte*imgHeight);
	
	//�������
	int i,j,k,l;

	//��־����
	int judge;

	//���ͼ����ÿһ������λ�ã��ж��Ƿ�ṹԪ��������Ŀ���ڲ�
	for(i=maskH/2;i<imgHeight-maskH/2;i++)
	{
		for(j=maskW/2;j<imgWidth-maskW/2;j++)
		{			
			//�жϽṹԪ���Ƿ�����ڵ�ǰ������Ŀ���ڲ�,1Ϊ����,0Ϊ������
			judge=1;
			for(k=-maskH/2;k<=maskH/2;k++)
			{
				for(l=-maskW/2;l<=maskW/2;l++)
				{
					//�����ǰ�ṹԪ��λ��Ϊ1,�ж����Ӧͼ���ϵ����ص��Ƿ�Ϊ��0
					if(maskBuf[(k+maskH/2)*maskW+l+maskW/2])
					{
						//���ͼ��ǰ����Ϊ0,��û�л��иõ�,���Ǹ�ʴ�����
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
					 int *maskBuf, int maskW, int maskH)//��ֵ���͵Ļ�������
{
	//ÿ��ͼ�����ݵ��ֽ���Ϊ4�ı���
	int lineByte=(imgWidth+3)/4*4;

	//ѭ������
	int i,j,k,l;

	//�����Ƕ�ͼ����Ŀ�겹���ĸ�ʴ�������������ͼ�����ݵĲ���
	for(i=0;i<imgHeight;i++){
		for(j=0;j<imgWidth;j++){
			*(imgBufIn+i*lineByte+j)=255-*(imgBufIn+i*lineByte+j);
		}
	}

	//�����ǽṹԪ�صĶԳƼ��Բ����ĸ�ʴ,�˴�tempMask���m_mask�ĶԳƼ�
	int *tempMask=new int[maskW*maskH];
	for(k=0;k<maskH;k++){
		for(l=0;l<maskW;l++){
			tempMask[k*maskW+l]=maskBuf[(maskH-1-k)*maskW+maskW-1-l];
		}
	}

	//��־����
	int judge;

	//���ͼ����ÿһ������λ�ã��ж��Ƿ�ṹԪ��������Ŀ���ڲ�
	for(i=maskH/2;i<imgHeight-maskH/2;i++)
	{
		for(j=maskW/2;j<imgWidth-maskW/2;j++)
		{			
			//�жϽṹԪ���Ƿ�����ڵ�ǰ������Ŀ���ڲ�,1Ϊ����,0Ϊ������
			judge=1;
			for(k=-maskH/2;k<=maskH/2;k++)
			{
				for(l=-maskW/2;l<=maskW/2;l++)
				{
					//�����ǰ�ṹԪ��λ��Ϊ1,�ж����Ӧͼ���ϵ����ص��Ƿ�Ϊ��0
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

	//�ýṹԪ�ضԳƼ���Ŀ�겹����ʴ��,��Ҫ�Խ������һ�β���,�������ͽ�����
	for(i=0;i<imgHeight;i++){
		for(j=0;j<imgWidth;j++){
			*(imgBufOut+i*lineByte+j)=255-*(imgBufOut+i*lineByte+j);
		}
	}

	//�ָ�ԭʼ����
	for(i=0;i<imgHeight;i++){
		for(j=0;j<imgWidth;j++){
			*(imgBufIn+i*lineByte+j)=255-*(imgBufIn+i*lineByte+j);
		}
	}
	
	delete []tempMask;
}


void Pic_Shape::BinaryErosion()
{
	//���û�нṹԪ�����룬�򷵻�
	if(m_maskBuf==NULL)
		return;

	//��ֵ��ʴ
	BasicErosionForBinary(m_pImgData, m_pImgDataOut,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);

}


void Pic_Shape::BinaryDilation()
{
	//���û�нṹԪ�����룬�򷵻�
	if(m_maskBuf==NULL)
		return;

	//��ֵ����
	BasicDilationForBinary(m_pImgData, m_pImgDataOut,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);
}



void Pic_Shape::BinaryOpen() //��ֵ������
{
	//���û�нṹԪ�����룬�򷵻�
	if(m_maskBuf==NULL)
		return;

	//�Ҷ�ͼ��ÿ��������ռ�ֽ���
	int lineByte=(m_imgWidth+3)/4*4;

	//�м�������������,������Ÿ�ʴ����м���
	unsigned char *buf=new unsigned char[lineByte*m_imgHeight];

	//�ȸ�ʴ
	BasicErosionForBinary(m_pImgData, buf,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);

	//������
	BasicDilationForBinary(buf, m_pImgDataOut,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);

	//�ͷŻ�����
	delete []buf;

}




void Pic_Shape::BinaryClose()//��ֵ������
{
	//���û�нṹԪ�����룬�򷵻�
	if(m_maskBuf==NULL)
		return;

	//�Ҷ�ͼ��ÿ��������ռ�ֽ���
	int lineByte=(m_imgWidth+3)/4*4;

	//�м�������������,������Ÿ�ʴ����м���
	unsigned char *buf=new unsigned char[lineByte*m_imgHeight];

	//������
	BasicDilationForBinary(m_pImgData, buf,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);

	//��ʴ
	BasicErosionForBinary(buf, m_pImgDataOut,m_imgWidth,m_imgHeight,
		m_maskBuf, m_maskW, m_maskH);

	//�ͷŻ�����
	delete []buf;
}

