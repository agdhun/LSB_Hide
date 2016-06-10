/****************************************************************************/
/*                                                                          */
/*              广州创龙电子科技有限公司                                    */
/*                                                                          */
/*              Copyright (C) 2015 Tronlong Electronic Technology Co.,Ltd   */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*              灰度图像LSB隐藏	                                            */
/*                                                                          */
/*              2016年06月09日      		                                        */
/*                                                                          */
/****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "bmpconfig.h"

// 软件断点
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
};		//需要隐藏的信息

/****************************************************************************/
/*                                                                          */
/*              主函数                                                      */
/*                                                                          */
/****************************************************************************/
int main(void)
{
	bmp inImg;				                        // 定义输入变量
	bmp outImg;										// 定义输出变量
	bmp cmpImg;										// 定义比较变量

	int i, j;

	int rows[INFO_LEN];
	int cols[INFO_LEN];

	int goalinfo[INFO_LEN];

	printf("\r\nImage Hide Application.\r\n");

	printf("Reading the image......\n");
	inImg = ReadBmp("../Image/gray.bmp");			// 读取一个位图
	printf("Read successfully.\n");

	printf("Processing random number......\n");
	randinterval(rows, cols, inImg.info.biHeight, inImg.info.biWidth, INFO_LEN, 20160530);
	printf("Process successfully.\n");

	// 图像LSB隐藏
	printf("LSB hiding......\n");
	outImg = LsbHide(&inImg, rows, cols, info);
	printf("Hiding LSB is completed.\n");

	// 保存 bmp 图片
	printf("Writing the image......\n");
	SaveBmp("../Image/Out.bmp", &outImg);
	printf("Write successfully.\n");

	// 比较输入与输出
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
	// 软件断点
	SW_BREAKPOINT;

	while(1);
}
