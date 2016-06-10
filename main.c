/****************************************************************************/
/*                                                                          */
/*              ���ݴ������ӿƼ����޹�˾                                    */
/*                                                                          */
/*              Copyright (C) 2015 Tronlong Electronic Technology Co.,Ltd   */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*              �Ҷ�ͼ��LSB����	                                            */
/*                                                                          */
/*              2016��06��09��      		                                        */
/*                                                                          */
/****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "bmpconfig.h"

// ����ϵ�
#define SW_BREAKPOINT   asm(" SWBP 0 ");


static const int info[] = {
		1,0,1,0,1,0,0,
		1,1,1,0,0,1,0,
		1,1,0,1,1,1,1,
		1,1,0,1,1,1,0,
		1,1,0,0,1,1,1,
		1,1,0,1,1,0,0,
		1,1,0,1,1,1,1,
		1,1,0,1,1,1,0,
		1,1,0,0,1,1,1,
		0,1,0,1,1,0,1,
		1,1,1,0,1,0,0,
		1,1,1,0,0,1,0,
		1,1,1,1,0,0,1,
		0,1,0,1,1,1,0,
		1,1,0,0,1,0,1,
		1,1,0,1,1,0,0,
		1,1,0,0,1,0,1,
		1,1,0,0,0,1,1,
		1,1,0,0,1,1,0,
		1,1,0,0,0,0,1,
		1,1,0,1,1,1,0,
		1,1,1,0,0,1,1,
		0,1,0,1,1,1,0,
		1,1,0,0,0,1,1,
		1,1,0,1,1,1,1,
		1,1,0,1,1,0,1,
};		//��Ҫ���ص���Ϣ

/****************************************************************************/
/*                                                                          */
/*              ������                                                      */
/*                                                                          */
/****************************************************************************/
int main(void)
{
	bmp inImg;				                        // �����������
	bmp outImg;										// �����������
	bmp cmpImg;										// ����Ƚϱ���

	int i, j;

	int rows[INFO_LEN];
	int cols[INFO_LEN];

	int goalinfo[INFO_LEN];

	printf("\r\nImage Hide Application.\r\n");

	printf("Reading the image......\n");
	inImg = ReadBmp("../Image/gray.bmp");			// ��ȡһ��λͼ
	printf("Read successfully.\n");

	printf("Processing random number......\n");
	randinterval(rows, cols, inImg.info.biHeight, inImg.info.biWidth, INFO_LEN, 20160530);
	printf("Process successfully.\n");

	// ͼ��LSB����
	printf("LSB hiding......\n");
	outImg = LsbHide(&inImg, rows, cols, info);
	printf("Hiding LSB is completed.\n");

	// ���� bmp ͼƬ
	printf("Writing the image......\n");
	SaveBmp("../Image/Out.bmp", &outImg);
	printf("Write successfully.\n");

	// �Ƚ����������
//	printf("Comparing......\n");
//	cmpImg = Compare(&inImg, &outImg);
//	SaveBmp("../Image/Compare.bmp", &cmpImg);
//	printf("Compare successfully.\n");

	SW_BREAKPOINT;

	printf("LSB geting......\n");
	LsbGet(&outImg, goalinfo, rows, cols);
	printf("Get lsb successfully.\n");

	for(i = 0; i < 26; i ++)
	{
		for(j = 0; j < 7; j ++)
			printf("%d ", goalinfo[7*i + j]);
		printf("\n");
	}
	// ����ϵ�
	SW_BREAKPOINT;

	while(1);
}
