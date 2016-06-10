#include "bmpconfig.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/****************************************************************************/
/*                                                                          */
/*              全局变量                                                    */
/*                                                                          */
/****************************************************************************/
unsigned char *newBmpBuf;
unsigned char newpColorTable[256*4];
unsigned char *newBmpBuf1;
unsigned char newpColorTable1[256*4];
/****************************************************************************/
/*                                                                          */
/*              读取 bmp 图片                                               */
/*                                                                          */
/****************************************************************************/
bmp ReadBmp(char *bmpName)
{
	bmp m;			// 定义一个位图结构
	FILE *fp;
	unsigned char *BmpBuf;
	int i;
	int bmpWidth;	// 图像的宽
	int bmpHeight;	// 图像的高
	int biBitCount;	// 图像类型，每像素位数
	int lineByte;

	if((fp=fopen( bmpName, "rb"))==NULL)
	{
		printf( "can't open the bmp imgae.\n ");
		exit(0);
	}
	else
	{
		fread(&m.file.bfType, sizeof(char), 2, fp);				// 类型
		fread(&m.file.bfSize, sizeof(int), 1, fp);				    // 文件长度
		fread(&m.file.bfReserverd1, sizeof(short int), 1, fp);	// 保留字 1
		fread(&m.file.bfReserverd2, sizeof(short int), 1, fp);	// 保留字 2
		fread(&m.file.bfbfOffBits, sizeof(int), 1, fp);			// 偏移量
		fread(&m.info.biSize, sizeof(int), 1, fp);				    // 此结构大小
		fread(&m.info.biWidth, sizeof(int), 1, fp);				// 位图的宽度
		fread(&m.info.biHeight, sizeof(int), 1, fp);			    // 位图的高度
		fread(&m.info.biPlanes, sizeof(short), 1, fp);			    // 目标设备位图数
		fread(&m.info.biBitcount, sizeof(short) ,1, fp);		    // 颜色深度
		fread(&m.info.biCompression, sizeof(int), 1, fp);		    // 位图压缩类型
		fread(&m.info.biSizeImage, sizeof(int), 1, fp);			// 位图大小
		fread(&m.info.biXPelsPermeter, sizeof(int), 1, fp);		// 位图水平分辨率
		fread(&m.info.biYPelsPermeter, sizeof(int), 1, fp);		// 位图垂直分辨率
		fread(&m.info.biClrUsed, sizeof(int), 1, fp);			    // 位图实际使用颜色数
		fread(&m.info.biClrImportant, sizeof(int), 1, fp);		    // 位图显示中比较重要颜色数
	}

	// 获取图像宽、高、每像素所占位数等信息
	bmpWidth = m.info.biWidth;
	bmpHeight = m.info.biHeight;
	biBitCount = m.info.biBitcount;

	// 定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	lineByte = (bmpWidth*biBitCount/8+3)/4*4;

	// 灰度图像有颜色表，且颜色表表项为256
	if(biBitCount == 8)
	{
		// 分配内存空间
		m.pColorTable = (RGBQUAD *)malloc(256*4);
		// 申请颜色表所需要的空间，读颜色表进内存
		fread(m.pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	// 分配内存空间
	m.imgBuf = (unsigned char *)malloc(m.info.biSizeImage);
	BmpBuf = (unsigned char *)malloc(m.info.biSizeImage);

	// 读位图数据
	fread(BmpBuf, lineByte * bmpHeight, 1, fp);

	// 将读到的数据垂直镜像翻转
	for(i = 0; i < bmpHeight; i++)
		memcpy((void *)(m.imgBuf + lineByte * i),
				(void *)(BmpBuf + lineByte * (bmpHeight - i - 1)), lineByte);
	// 关闭文件
	fclose(fp);

	return m;
}

/****************************************************************************/
/*                                                                          */
/*              保存 bmp 图片                                               */
/*                                                                          */
/****************************************************************************/
int SaveBmp(char *bmpName, bmp *m)
{
	unsigned char *BmpBuf;
	int i;
	int bmpWidth;
	int bmpHeight;
	int biBitCount;
	RGBQUAD *pColorTable;

	bmpWidth = m->info.biWidth;
	bmpHeight = m->info.biHeight;
	biBitCount = m->info.biBitcount;
	pColorTable = m->pColorTable;

	// 如果位图数据指针为0，则没有数据传入，函数返回
	if(!m->imgBuf)
		return 0;

	// 待存储图像数据每行字节数为4的倍数
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	//以二进制写的方式打开文件
	FILE *fp = fopen(bmpName,"wb");
	if(fp == 0)
		return 0;

	fwrite(&m->file.bfType, sizeof(short), 1, fp);
	fwrite(&m->file.bfSize, sizeof(int), 1, fp);
	fwrite(&m->file.bfReserverd1, sizeof(short int), 1, fp);
	fwrite(&m->file.bfReserverd2, sizeof(short int), 1, fp);
	fwrite(&m->file.bfbfOffBits, sizeof(int), 1, fp);
	fwrite(&m->info.biSize, sizeof(int), 1, fp);
	fwrite(&m->info.biWidth, sizeof(int), 1, fp);
	fwrite(&m->info.biHeight, sizeof(int), 1, fp);
	fwrite(&m->info.biPlanes, sizeof(short), 1, fp);
	fwrite(&m->info.biBitcount, sizeof(short), 1, fp);
	fwrite(&m->info.biCompression, sizeof(int), 1, fp);
	fwrite(&m->info.biSizeImage, sizeof(int), 1, fp);
	fwrite(&m->info.biXPelsPermeter, sizeof(int), 1, fp);
	fwrite(&m->info.biYPelsPermeter, sizeof(int), 1, fp);
	fwrite(&m->info.biClrUsed, sizeof(int), 1, fp);
	fwrite(&m->info.biClrImportant, sizeof(int), 1, fp);

	// 如果灰度图像，有颜色表，写入文件
	if(biBitCount==8)
		fwrite(pColorTable, sizeof(RGBQUAD)*256, 1, fp);

	// 分配数据缓冲
	BmpBuf = (unsigned char *)malloc(m->info.biSizeImage);
	// 将位图数据垂直镜像翻转再写入
	for(i = 0; i < bmpHeight; i++)
		memcpy((void *)(BmpBuf + lineByte * i),
				(void *)(m->imgBuf + lineByte * (bmpHeight - i - 1)), lineByte);

	// 写位图数据进文件
	fwrite(BmpBuf, bmpHeight*lineByte, 1, fp);

	// 关闭文件
	fclose(fp);

	return 1;
}
/****************************************************************************/
/*                                                                          */
/*              最不重要位信息隐藏                                              */
/*                                                                          */
/****************************************************************************/
bmp LsbHide(bmp *m, const int *row, const int *col, const int *info)
{
        int i, j;
        bmp newm;
        int bmpWidth;                // 图像的宽
        int bmpHeight;                // 图像的高
        int biBitCount;                // 图像类型，每像素位数
        int lineByte;
        int newBmpWidth;         // 新图像的宽
        int newBmpHeight;         // 新图像的高
        int newLineByte;
        int temp;

        // 获取图像宽、高、每像素所占位数等信息
        bmpWidth = m->info.biWidth;
        bmpHeight = m->info.biHeight;
        biBitCount = m->info.biBitcount;

        // 定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
        lineByte=(bmpWidth * biBitCount / 8 + 3) / 4 * 4;

        newBmpWidth = bmpWidth;
        newBmpHeight = bmpHeight;
        newLineByte = (newBmpWidth * biBitCount / 8 + 3) / 4 * 4;
        // 申请位图数据区
        newBmpBuf = (unsigned char *)malloc(newLineByte * newBmpHeight);

        int t = 0;
        //信息复制
        for(i = 0; i < newBmpHeight; i++)
        {
            for(j = 0; j < newBmpWidth; j++)
            {
                    temp = (*(unsigned char *)(m->imgBuf + i * lineByte + j));
                        *(unsigned char *)(newBmpBuf + i*newLineByte + j) = temp;
                }
        }
        //低位隐藏
        for(i = 0; i < 1; i++)
        {
                for(j = 0; j < INFO_LEN; j++)
                {
                        temp = (*(unsigned char *)(newBmpBuf + (row[j]) * newLineByte + col[j]));
                        *(unsigned char *)(newBmpBuf + (row[j])*newLineByte + col[j]) = temp - temp %2 +info[t];	//清除LSB,赋予信息值
                        t ++;
                }
        }

        newm.file.bfType = 0x4d42;                                                        // 类型
        newm.file.bfSize = 54 + 246 *4 +
                                                newLineByte * newBmpHeight;                // 文件长度
        newm.file.bfReserverd1 = 0;                                                        // 保留字 1
        newm.file.bfReserverd2 = 0;                                                        // 保留字 2
        newm.file.bfbfOffBits = 54 + 256 * 4;                                // 偏移量
        newm.info.biSize = 40;                                                                // 此结构大小
        newm.info.biWidth = newBmpWidth;                                        // 位图的宽度
        newm.info.biHeight = newBmpHeight;                                        // 位图的高度
        newm.info.biPlanes = 1;                                                                // 目标设备位图数
        newm.info.biBitcount = 8;                                                        // 颜色深度
        newm.info.biCompression = 0;                                                // 位图压缩类型
        newm.info.biSizeImage = newLineByte * newBmpHeight;        // 位图大小
        newm.info.biXPelsPermeter = 0;                      // 位图水平分辨率
        newm.info.biYPelsPermeter = 0;                      // 位图垂直分辨率
        newm.info.biClrUsed = 0;                            // 位图实际使用颜色数
        newm.info.biClrImportant = 0;                       // 位图显示中比较重要颜色数

        // 写入调色板
        memcpy((void *)(newpColorTable), (void *)(m->pColorTable), 256 * 4);
        newm.pColorTable = (RGBQUAD*)newpColorTable;

        //写入位图数据
        newm.imgBuf = newBmpBuf;

        return newm;
}

/****************************************************************************/
/*                                                                          */
/*              最不重要位信息提取                                                                                                                   */
/*                                                                          */
/****************************************************************************/
void LsbGet(bmp *m, int *goaltext, const int *row, const int *col)
{
        int i, j;
        int bmpWidth;                // 图像的宽
        int bmpHeight;                // 图像的高
        int biBitCount;                // 图像类型，每像素位数
        int lineByte;
        int temp;

        // 获取图像宽、高、每像素所占位数等信息
        bmpWidth = m->info.biWidth;
        bmpHeight = m->info.biHeight;
        biBitCount = m->info.biBitcount;

        // 定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
        lineByte=(bmpWidth * biBitCount / 8 + 3) / 4 * 4;

        //信息提取
        int t = 0;
        for(i = 0; i < 1; i++)
        {
            for(j = 0; j < bmpWidth; j++)
            {
                    temp = (*(unsigned char *)(m->imgBuf + (row[j]) * lineByte + col[j]));
                    int maxlen = j;
                        if(INFO_LEN >= maxlen )
                        {
                                goaltext[t] = temp & 1;//取最低位
                                t ++;
                        }
                        else
                                return;
                }
        }
}

/****************************************************************************/
/*                                                                          */
/*              图片比较                                                                                                                                            */
/*                                                                          */
/****************************************************************************/
bmp Compare(bmp *input, bmp *output)
{
	int i, j;
	bmp newm;
	int bmpWidth;		// 图像的宽
	int bmpHeight;		// 图像的高
	int biBitCount;		// 图像类型，每像素位数
	int lineByte;
	int newBmpWidth; 	// 新图像的宽
	int newBmpHeight; 	// 新图像的高
	int newLineByte;
	int tempi, tempo;

	// 获取图像宽、高、每像素所占位数等信息
	bmpWidth = input->info.biWidth;
	bmpHeight = input->info.biHeight;
	biBitCount = input->info.biBitcount;

	// 定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	lineByte=(bmpWidth * biBitCount / 8 + 3) / 4 * 4;

	newBmpWidth = bmpWidth;
	newBmpHeight = bmpHeight;
	newLineByte = (newBmpWidth * biBitCount / 8 + 3) / 4 * 4;
	// 申请位图数据区
	newBmpBuf1 = (unsigned char *)malloc(newLineByte * newBmpHeight);

	for(i = 0; i < newBmpHeight; i++)
	{
		for(j = 0; j < newBmpWidth; j++)
		{
			tempi = (*(unsigned char *)(input->imgBuf + i * lineByte + j));
			tempo = (*(unsigned char *)(output->imgBuf + i * lineByte + j));
			*(unsigned char *)(newBmpBuf1 + i*newLineByte + j) = tempo - tempi;//比较输入输出
		}
	}

	newm.file.bfType = 0x4d42;							// 类型
	newm.file.bfSize = 54 + 246 *4 + newLineByte * newBmpHeight;		// 文件长度
	newm.file.bfReserverd1 = 0;							// 保留字 1
	newm.file.bfReserverd2 = 0;							// 保留字 2
	newm.file.bfbfOffBits = 54 + 256 * 4;				// 偏移量
	newm.info.biSize = 40;								// 此结构大小
	newm.info.biWidth = newBmpWidth;					// 位图的宽度
	newm.info.biHeight = newBmpHeight;					// 位图的高度
	newm.info.biPlanes = 1;								// 目标设备位图数
	newm.info.biBitcount = 8;							// 颜色深度
	newm.info.biCompression = 0;						// 位图压缩类型
	newm.info.biSizeImage = newLineByte * newBmpHeight;	// 位图大小
	newm.info.biXPelsPermeter = 0;                      // 位图水平分辨率
	newm.info.biYPelsPermeter = 0;                      // 位图垂直分辨率
	newm.info.biClrUsed = 0;                            // 位图实际使用颜色数
	newm.info.biClrImportant = 0;                       // 位图显示中比较重要颜色数

	// 写入调色板
	memcpy((void *)(newpColorTable1), (void *)(input->pColorTable), 256 * 4);
	newm.pColorTable = (RGBQUAD*)newpColorTable1;

	//写入位图数据
	newm.imgBuf = newBmpBuf1;

	return newm;
}

/****************************************************************************/
/*                                                                          */
/*              随机间隔生成                                                                                                                                  */
/*                                                                          */
/****************************************************************************/
void randinterval(int *row, int *col, int mrow, int mcol, int count, int key)
{
	double *a = malloc(count * sizeof(double));					//定义存放伪随机数的空间
	int r = 1, c = 1, i;										//定义缓冲
	int interval1, interval2;									//定义相差为避免的两个基本间隔值
	interval1 = mrow * mcol / count + 1;
	interval2 = interval1 - 2;
	if(interval2 <= 0)											//随机间隔若有小于0,表明图片的冗余程度不够插入信息
	{
	    perror("载体太小不能将秘密信息隐藏进去!");
		exit(EXIT_FAILURE);
	}
	srand(key);													//伪随机函数rand的种子指定确保生成随机数不变
	for(i = 0; i < count; i++)
	{
		a[i] = rand();											//rand产生的是0-32768的整数随机数
		row[i] = 0;												//行列初始化
		col[i] = 0;
	}
	row[1] = r;
	col[1] = c;

	//判断随机数是否大于中间值,大于去间隔一的值,不大于取间隔二的值
	for(i = 1; i < count; i ++)
	{
	    if(a[i] >  16339)
	        c = c + interval1;
	    else
	        c = c + interval2;
	    if(c > mcol)						//超过一行则列相应变化
	    {
	        r = r + c / mcol;
	        if(r > mrow)
	        {
	            perror("载体太小不能将秘密信息隐藏进去!");
	            exit(EXIT_FAILURE);
	        }
	        c = c % mcol;
	        if(c == 0)
	            c = 1;
	    }
	    row[i] = r;
	    col[i] = c;
	    //printf("row%d:%d  col%d:%d\n", i, r, i, c);			//打印生成的随机间隔表
	}
	free(a);
}

/****************************************************************************/
/*                                                                          */
/*              字符相应位提取                                                                                                                             */
/*                                                                          */
/****************************************************************************/
char GetBit(char name, int indexof)
{
	return ((name >> (indexof-1)) - (name >> indexof << 1));
}

/****************************************************************************/
/*                                                                          */
/*              字符号相应位赋值                                                                                                                       */
/*                                                                          */
/****************************************************************************/
void SetBit(char *name, int indexof, int bl, int inof)
{
	*(name + inof) &= (~(1 << (indexof - 1)));
	*(name + inof) += bl << (indexof - 1);
}
