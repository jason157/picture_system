#include "stdafx.h"
#include "GrayTrans.h"
#include "math.h"

/***********************************************************************
* �������ƣ�
* GrayTrans()
*
*˵�����޲����Ĺ��캯�����Գ�Ա�������г�ʼ��
***********************************************************************/
GrayTrans::GrayTrans()
{
	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}

/***********************************************************************
* �������ƣ�
* GrayTrans()
*
*����������
*  CSize size -ͼ���С�����ߣ�
*  int nBitCount  -ÿ���ر�����
*  LPRGBQUAD lpColorTable  -��ɫ��ָ��
*  unsigned char *pImgData  -λͼ����ָ��
*
*����ֵ��
*   ��
*
*˵����������Ϊ�������Ĺ��캯��������λͼ�Ĵ�С��ÿ����λ������ɫ��
*      ��λͼ���ݣ�����ImgCenterDib()�Ի����Ա��ʼ������Ϊ����ͼ������
*      ��ص����ݳ�Ա,����ʼ�����ͼ����ص����ݳ�Ա
***********************************************************************/
GrayTrans::GrayTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
					 unsigned char *pImgData):
ImgCenterDib(size, nBitCount, lpColorTable, pImgData)
{

    m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��

	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
	
	m_nColorTableLengthOut=0;//���ͼ����ɫ����Ϊ0

    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0

	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0

	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
}


/***********************************************************************
* �������ƣ�
*   ~GrayTrans()

*
*˵���������������ͷ���Դ
***********************************************************************/
GrayTrans::~GrayTrans()
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

/***********************************************************************
* �������ƣ�
* GetDimensions()
*
*����������
*  ��
*
*����ֵ��
*   ͼ��ĳߴ磬��CSize���ͱ��
*
*˵�����������ͼ��Ŀ�͸�
***********************************************************************/
CSize GrayTrans::GetDimensions()
{	
	if(m_pImgDataOut == NULL) return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}





void GrayTrans::ColorToGray()//��ֵ��
{
	//���Ҷ�ͼ��,�򷵻�
	if(m_nBitCount==8) return;

	//�ͷžɵ����ͼ�����ݼ���ɫ������
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
		m_pImgDataOut=NULL;
	}
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//��ֵ����,ÿ����λ��Ϊ8����
	m_nBitCountOut=8;

	//��ɫ����
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);

	//������ɫ������,���ɻҶ�ͼ�����ɫ��
	if(m_nColorTableLengthOut!=0){
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		for(int i=0; i<m_nColorTableLengthOut;i++){
			m_lpColorTableOut[i].rgbBlue=i;
			m_lpColorTableOut[i].rgbGreen=i;
			m_lpColorTableOut[i].rgbRed=i;
			m_lpColorTableOut[i].rgbReserved=0;
		}
	}

	//����ͼ��ÿ�����ֽ���,��ɫͼ��Ϊ3�ֽ�/����
	int pixelByteIn=3;
	
	//����ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteIn=(m_imgWidth*pixelByteIn+3)/4*4;

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//���ͼ��ÿ��������ռ�ֽ���,������4�ı���
	int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

	//�������ͼ��λͼ���ݻ�����
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];

	//ѭ������,ͼ�������
	int i,j;

	//���ݻ�ֵ����ʽΪ���ͼ��ֵ
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++)
			*(m_pImgDataOut+i*lineByteOut+j)=0.11**(m_pImgData+i*lineByteIn+j*pixelByteIn+0)
		        	+0.59**(m_pImgData+i*lineByteIn+j*pixelByteIn+1)
		        	+0.30**(m_pImgData+i*lineByteIn+j*pixelByteIn+2)+0.5;
	}

}


void GrayTrans::Binary(int threshold)
{
	//���ڻҶ�ͼ��
	if(m_nBitCount==8){
		//�ͷžɵ����ͼ�����ݼ���ɫ������
		if(m_pImgDataOut!=NULL){
			delete []m_pImgDataOut;
			m_pImgDataOut=NULL;
		}
		if(m_lpColorTableOut!=NULL){
			delete []m_lpColorTableOut;
			m_lpColorTableOut=NULL;
		}
		//���ͼ���ÿ����λ������ɫ����
		m_nBitCountOut=m_nBitCount;
		m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
		
		//�������ͼ����ɫ����������������ͼ����ɫ���������ͼ����ɫ����
		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
		
		//���ͼ��Ŀ��,������ͼ�����
		m_imgWidthOut=m_imgWidth;
		m_imgHeightOut=m_imgHeight;
		
		
		//ͼ��ÿ��������ռ�ֽ���������ͼ�������ͼ��ÿ��������ռ�ֽ������
		int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;

		//�������ͼ��λͼ���ݻ�����
		m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];

		//ѭ��������ͼ�������
		int i,j;

		//��ֵ��
		for(i=0;i<m_imgHeight;i++){
			for(j=0;j<m_imgWidth;j++){
				if(*(m_pImgData+i*lineByte+j)<threshold)
    				*(m_pImgDataOut+i*lineByte+j)=0;
				else
					*(m_pImgDataOut+i*lineByte+j)=255;
			}
		}
	}
	else{

		//���ǲ�ɫͼ��,�ȱ�ɻҶȸ�ʽ���任��m_pImgDataOut�Ѿ��������ڴ棬
        //������˻Ҷ�ͼ������
		ColorToGray();

		//���ͼ��ÿ��������ռ�ֽ���������ͼ�������ͼ��ÿ��������ռ�ֽ�������
		int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

		//ѭ��������ͼ�������
		int i,j;

		//��ֵ��
		for(i=0;i<m_imgHeight;i++){
			for(j=0;j<m_imgWidth;j++)
				if(*(m_pImgDataOut+i*lineByteOut+j)<threshold)
					*(m_pImgDataOut+i*lineByteOut+j)=0;
				else
					*(m_pImgDataOut+i*lineByteOut+j)=255;
		}
	}
	
}


void GrayTrans::GrayToColor()//�Ҷ�ͼ���ɲ�ɫ��ʽ
{
	//���ǲ�ɫ��ʽ���򷵻�
	if(m_nBitCount==24) return;

	//�ͷžɵ����ͼ�����ݼ���ɫ������
	if(m_pImgDataOut!=NULL){
		delete []m_pImgDataOut;
		m_pImgDataOut=NULL;
	}
	if(m_lpColorTableOut!=NULL){
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}

	//���ͼ��ÿ����λ��Ϊ24����
	m_nBitCountOut=24;

	//��ɫͼ����ɫ����Ϊ0��������ɫ��
	m_nColorTableLengthOut=0;

	//����ĻҶ�ͼ��ÿ��������ռ�ֽ���������Ϊ4�ı���
	int lineByteIn=(m_imgWidth+3)/4*4;

	//���ͼ��Ŀ��,������ͼ�����
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;

	//����Ĳ�ɫͼ��ÿ��������ռ�ֽ���������Ϊ4�ı���
	int lineByteOut=(m_imgWidth*m_nBitCountOut/8+3)/4*4;

	//�������ͼ��λͼ���ݻ�����
	m_pImgDataOut=new unsigned char[lineByteOut*m_imgHeight];

	//i,jΪͼ������ѭ��������kΪ��ɫͼ������ͨ����ѭ������
	int i,j,k;

	//�Ҷȱ��ɫ
	for(i=0;i<m_imgHeight;i++){
		for(j=0;j<m_imgWidth;j++){
			//�����ػҶ�ֵΪ��ɫ��ʽ��ÿ��ͨ����ֵ������ͨ����ֵ���
			for(k=0;k<3;k++)
			  *(m_pImgDataOut+i*lineByteOut+j*3+k)=*(m_pImgData+i*lineByteIn+j);
		}
	}
}


