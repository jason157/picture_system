#include "stdafx.h"
#include "Pic_Segment.h"
#include "math.h"


Pic_Segment::Pic_Segment() //�޲����Ĺ��캯�����Գ�Ա�������г�ʼ��
{
	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}


Pic_Segment::Pic_Segment(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData):
ImgCenterDib(size, nBitCount, lpColorTable, pImgData)//�������Ĺ��캯��������λͼ�Ĵ�С��ÿ����λ������ɫ��λͼ����
{
	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}

Pic_Segment::~Pic_Segment()
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


//�������ͼ��Ŀ�͸�
CSize Pic_Segment::GetDimensions()
{	
	if(m_pImgDataOut == NULL) return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}



void Pic_Segment::Roberts()//Roberts��Ե���,�����ڻҶȺͲ�ɫͼ��
{
	//�ͷ�m_pImgDataOutָ���ͼ�����ݿռ�
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}
	//�ͷ���ɫ��ռ�
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//���ͼ��������ͼ��Ϊͬһ����
	m_nBitCountOut=m_nBitCount;

	//���ͼ����ɫ����
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//���ͼ����ɫ��������ͼ����ͬ
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//ÿ��������ռ�ֽ��������ͼ��������ͼ����ͬ
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//�������ͼ�񻺳���
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];


	//ѭ��������ͼ�������
	int i,j;

	//ÿ����ռ�ֽ��������ͼ��������ͼ����ͬ
	int pixelByte=m_nBitCount/8;

	//ѭ������,�������ص�ÿ��ͨ��,�����ɫͼ����������
	int k;

	//�м����
	int x, y, t;

	//Roberts����
	for(i=1;i<m_imgHeight-1;i++){
		for(j=1;j<m_imgWidth-1;j++){
			for(k=0;k<pixelByte;k++){
				//x�����ݶ�
				x=*(m_pImgData+i*lineByte+j*pixelByte+k)
					-*(m_pImgData+(i+1)*lineByte+j*pixelByte+k);

				//y�����ݶ�
				y=*(m_pImgData+i*lineByte+j*pixelByte+k)
					-*(m_pImgData+i*lineByte+(j+1)*pixelByte+k);

				t=sqrt(x*x+y*y)+0.5;
				if(t>255)
				   t=255;
				//��t��ֵ�Ž�ͼ�ξ������
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)=t;
			}
		}
	}
}


void Pic_Segment::ContourExtract()
{
	//ֻ����Ҷ�ͼ��
	if(m_nBitCount!=8)
		return;

	//�ͷ�m_pImgDataOutָ���ͼ�����ݿռ�
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}
	//�ͷ���ɫ��ռ�
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//���ͼ��������ͼ��Ϊͬһ����
	m_nBitCountOut=m_nBitCount;

	//���ͼ����ɫ����
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//���ͼ����ɫ��������ͼ����ͬ
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//ÿ��������ռ�ֽ��������ͼ��������ͼ����ͬ
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

	//�������ͼ�񻺳���
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

	//������������ȡ����

	//������ͼ�����ݿ��������ͼ�񻺳���
	memcpy(m_pImgDataOut,m_pImgData,lineByte*m_imgHeight);

	//��źڵ�����8��������ػҶ�ֵ
	int array[8];

	//�������
	int sum;

	//ѭ������
	int i, j, k;

	//����ͼ���еĺڵ㣬�����Ǳ߽��ϵĵ�
	for(i=1;i<m_imgHeight-1;i++){
		for(j=1;j<m_imgWidth-1;j++){
			//�ҵ�һ���ڵ�
			if(*(m_pImgData+i*lineByte+j)==0){
				//������Χ8�������ؽ�array����
		    	array[0]=*(m_pImgData+i*lineByte+j+1);
				array[1]=*(m_pImgData+(i+1)*lineByte+j+1);
				array[2]=*(m_pImgData+(i+1)*lineByte+j);
				array[3]=*(m_pImgData+(i+1)*lineByte+j-1);
				array[4]=*(m_pImgData+i*lineByte+j-1);
				array[5]=*(m_pImgData+(i-1)*lineByte+j-1);
				array[6]=*(m_pImgData+(i-1)*lineByte+j);
				array[7]=*(m_pImgData+(i-1)*lineByte+j+1);
				
				//���������
				sum=0;
				for(k=0;k<8;k++)
					sum += array[k];

				//��Χ8�����Ϊ�ڵ㣬�����ͼ���Ӧ�����ð�ɫ
				if(sum==0)
				   *(m_pImgDataOut+i*lineByte+j)=255;
				
			}
		}
	}

}

