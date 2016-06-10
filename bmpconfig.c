#include "bmpconfig.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/****************************************************************************/
/*                                                                          */
/*              ȫ�ֱ���                                                    */
/*                                                                          */
/****************************************************************************/
unsigned char *newBmpBuf;
unsigned char newpColorTable[256*4];
unsigned char *newBmpBuf1;
unsigned char newpColorTable1[256*4];
/****************************************************************************/
/*                                                                          */
/*              ��ȡ bmp ͼƬ                                               */
/*                                                                          */
/****************************************************************************/
bmp ReadBmp(char *bmpName)
{
	bmp m;			// ����һ��λͼ�ṹ
	FILE *fp;
	unsigned char *BmpBuf;
	int i;
	int bmpWidth;	// ͼ��Ŀ�
	int bmpHeight;	// ͼ��ĸ�
	int biBitCount;	// ͼ�����ͣ�ÿ����λ��
	int lineByte;

	if((fp=fopen( bmpName, "rb"))==NULL)
	{
		printf( "can't open the bmp imgae.\n ");
		exit(0);
	}
	else
	{
		fread(&m.file.bfType, sizeof(char), 2, fp);				// ����
		fread(&m.file.bfSize, sizeof(int), 1, fp);				    // �ļ�����
		fread(&m.file.bfReserverd1, sizeof(short int), 1, fp);	// ������ 1
		fread(&m.file.bfReserverd2, sizeof(short int), 1, fp);	// ������ 2
		fread(&m.file.bfbfOffBits, sizeof(int), 1, fp);			// ƫ����
		fread(&m.info.biSize, sizeof(int), 1, fp);				    // �˽ṹ��С
		fread(&m.info.biWidth, sizeof(int), 1, fp);				// λͼ�Ŀ��
		fread(&m.info.biHeight, sizeof(int), 1, fp);			    // λͼ�ĸ߶�
		fread(&m.info.biPlanes, sizeof(short), 1, fp);			    // Ŀ���豸λͼ��
		fread(&m.info.biBitcount, sizeof(short) ,1, fp);		    // ��ɫ���
		fread(&m.info.biCompression, sizeof(int), 1, fp);		    // λͼѹ������
		fread(&m.info.biSizeImage, sizeof(int), 1, fp);			// λͼ��С
		fread(&m.info.biXPelsPermeter, sizeof(int), 1, fp);		// λͼˮƽ�ֱ���
		fread(&m.info.biYPelsPermeter, sizeof(int), 1, fp);		// λͼ��ֱ�ֱ���
		fread(&m.info.biClrUsed, sizeof(int), 1, fp);			    // λͼʵ��ʹ����ɫ��
		fread(&m.info.biClrImportant, sizeof(int), 1, fp);		    // λͼ��ʾ�бȽ���Ҫ��ɫ��
	}

	// ��ȡͼ����ߡ�ÿ������ռλ������Ϣ
	bmpWidth = m.info.biWidth;
	bmpHeight = m.info.biHeight;
	biBitCount = m.info.biBitcount;

	// �������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
	lineByte = (bmpWidth*biBitCount/8+3)/4*4;

	// �Ҷ�ͼ������ɫ������ɫ�����Ϊ256
	if(biBitCount == 8)
	{
		// �����ڴ�ռ�
		m.pColorTable = (RGBQUAD *)malloc(256*4);
		// ������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
		fread(m.pColorTable, sizeof(RGBQUAD), 256, fp);
	}

	// �����ڴ�ռ�
	m.imgBuf = (unsigned char *)malloc(m.info.biSizeImage);
	BmpBuf = (unsigned char *)malloc(m.info.biSizeImage);

	// ��λͼ����
	fread(BmpBuf, lineByte * bmpHeight, 1, fp);

	// �����������ݴ�ֱ����ת
	for(i = 0; i < bmpHeight; i++)
		memcpy((void *)(m.imgBuf + lineByte * i),
				(void *)(BmpBuf + lineByte * (bmpHeight - i - 1)), lineByte);
	// �ر��ļ�
	fclose(fp);

	return m;
}

/****************************************************************************/
/*                                                                          */
/*              ���� bmp ͼƬ                                               */
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

	// ���λͼ����ָ��Ϊ0����û�����ݴ��룬��������
	if(!m->imgBuf)
		return 0;

	// ���洢ͼ������ÿ���ֽ���Ϊ4�ı���
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	//�Զ�����д�ķ�ʽ���ļ�
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

	// ����Ҷ�ͼ������ɫ��д���ļ�
	if(biBitCount==8)
		fwrite(pColorTable, sizeof(RGBQUAD)*256, 1, fp);

	// �������ݻ���
	BmpBuf = (unsigned char *)malloc(m->info.biSizeImage);
	// ��λͼ���ݴ�ֱ����ת��д��
	for(i = 0; i < bmpHeight; i++)
		memcpy((void *)(BmpBuf + lineByte * i),
				(void *)(m->imgBuf + lineByte * (bmpHeight - i - 1)), lineByte);

	// дλͼ���ݽ��ļ�
	fwrite(BmpBuf, bmpHeight*lineByte, 1, fp);

	// �ر��ļ�
	fclose(fp);

	return 1;
}
/****************************************************************************/
/*                                                                          */
/*              ���Ҫλ��Ϣ����                                              */
/*                                                                          */
/****************************************************************************/
bmp LsbHide(bmp *m, const int *row, const int *col, const int *info)
{
        int i, j;
        bmp newm;
        int bmpWidth;                // ͼ��Ŀ�
        int bmpHeight;                // ͼ��ĸ�
        int biBitCount;                // ͼ�����ͣ�ÿ����λ��
        int lineByte;
        int newBmpWidth;         // ��ͼ��Ŀ�
        int newBmpHeight;         // ��ͼ��ĸ�
        int newLineByte;
        int temp;

        // ��ȡͼ����ߡ�ÿ������ռλ������Ϣ
        bmpWidth = m->info.biWidth;
        bmpHeight = m->info.biHeight;
        biBitCount = m->info.biBitcount;

        // �������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
        lineByte=(bmpWidth * biBitCount / 8 + 3) / 4 * 4;

        newBmpWidth = bmpWidth;
        newBmpHeight = bmpHeight;
        newLineByte = (newBmpWidth * biBitCount / 8 + 3) / 4 * 4;
        // ����λͼ������
        newBmpBuf = (unsigned char *)malloc(newLineByte * newBmpHeight);

        int t = 0;
        //��Ϣ����
        for(i = 0; i < newBmpHeight; i++)
        {
            for(j = 0; j < newBmpWidth; j++)
            {
                    temp = (*(unsigned char *)(m->imgBuf + i * lineByte + j));
                        *(unsigned char *)(newBmpBuf + i*newLineByte + j) = temp;
                }
        }
        //��λ����
        for(i = 0; i < 1; i++)
        {
                for(j = 0; j < INFO_LEN; j++)
                {
                        temp = (*(unsigned char *)(newBmpBuf + (row[j]) * newLineByte + col[j]));
                        *(unsigned char *)(newBmpBuf + (row[j])*newLineByte + col[j]) = temp - temp %2 +info[t];	//���LSB,������Ϣֵ
                        t ++;
                }
        }

        newm.file.bfType = 0x4d42;                                                        // ����
        newm.file.bfSize = 54 + 246 *4 +
                                                newLineByte * newBmpHeight;                // �ļ�����
        newm.file.bfReserverd1 = 0;                                                        // ������ 1
        newm.file.bfReserverd2 = 0;                                                        // ������ 2
        newm.file.bfbfOffBits = 54 + 256 * 4;                                // ƫ����
        newm.info.biSize = 40;                                                                // �˽ṹ��С
        newm.info.biWidth = newBmpWidth;                                        // λͼ�Ŀ��
        newm.info.biHeight = newBmpHeight;                                        // λͼ�ĸ߶�
        newm.info.biPlanes = 1;                                                                // Ŀ���豸λͼ��
        newm.info.biBitcount = 8;                                                        // ��ɫ���
        newm.info.biCompression = 0;                                                // λͼѹ������
        newm.info.biSizeImage = newLineByte * newBmpHeight;        // λͼ��С
        newm.info.biXPelsPermeter = 0;                      // λͼˮƽ�ֱ���
        newm.info.biYPelsPermeter = 0;                      // λͼ��ֱ�ֱ���
        newm.info.biClrUsed = 0;                            // λͼʵ��ʹ����ɫ��
        newm.info.biClrImportant = 0;                       // λͼ��ʾ�бȽ���Ҫ��ɫ��

        // д���ɫ��
        memcpy((void *)(newpColorTable), (void *)(m->pColorTable), 256 * 4);
        newm.pColorTable = (RGBQUAD*)newpColorTable;

        //д��λͼ����
        newm.imgBuf = newBmpBuf;

        return newm;
}

/****************************************************************************/
/*                                                                          */
/*              ���Ҫλ��Ϣ��ȡ                                                                                                                   */
/*                                                                          */
/****************************************************************************/
void LsbGet(bmp *m, int *goaltext, const int *row, const int *col)
{
        int i, j;
        int bmpWidth;                // ͼ��Ŀ�
        int bmpHeight;                // ͼ��ĸ�
        int biBitCount;                // ͼ�����ͣ�ÿ����λ��
        int lineByte;
        int temp;

        // ��ȡͼ����ߡ�ÿ������ռλ������Ϣ
        bmpWidth = m->info.biWidth;
        bmpHeight = m->info.biHeight;
        biBitCount = m->info.biBitcount;

        // �������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
        lineByte=(bmpWidth * biBitCount / 8 + 3) / 4 * 4;

        //��Ϣ��ȡ
        int t = 0;
        for(i = 0; i < 1; i++)
        {
            for(j = 0; j < bmpWidth; j++)
            {
                    temp = (*(unsigned char *)(m->imgBuf + (row[j]) * lineByte + col[j]));
                    int maxlen = j;
                        if(INFO_LEN >= maxlen )
                        {
                                goaltext[t] = temp & 1;//ȡ���λ
                                t ++;
                        }
                        else
                                return;
                }
        }
}

/****************************************************************************/
/*                                                                          */
/*              ͼƬ�Ƚ�                                                                                                                                            */
/*                                                                          */
/****************************************************************************/
bmp Compare(bmp *input, bmp *output)
{
	int i, j;
	bmp newm;
	int bmpWidth;		// ͼ��Ŀ�
	int bmpHeight;		// ͼ��ĸ�
	int biBitCount;		// ͼ�����ͣ�ÿ����λ��
	int lineByte;
	int newBmpWidth; 	// ��ͼ��Ŀ�
	int newBmpHeight; 	// ��ͼ��ĸ�
	int newLineByte;
	int tempi, tempo;

	// ��ȡͼ����ߡ�ÿ������ռλ������Ϣ
	bmpWidth = input->info.biWidth;
	bmpHeight = input->info.biHeight;
	biBitCount = input->info.biBitcount;

	// �������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
	lineByte=(bmpWidth * biBitCount / 8 + 3) / 4 * 4;

	newBmpWidth = bmpWidth;
	newBmpHeight = bmpHeight;
	newLineByte = (newBmpWidth * biBitCount / 8 + 3) / 4 * 4;
	// ����λͼ������
	newBmpBuf1 = (unsigned char *)malloc(newLineByte * newBmpHeight);

	for(i = 0; i < newBmpHeight; i++)
	{
		for(j = 0; j < newBmpWidth; j++)
		{
			tempi = (*(unsigned char *)(input->imgBuf + i * lineByte + j));
			tempo = (*(unsigned char *)(output->imgBuf + i * lineByte + j));
			*(unsigned char *)(newBmpBuf1 + i*newLineByte + j) = tempo - tempi;//�Ƚ��������
		}
	}

	newm.file.bfType = 0x4d42;							// ����
	newm.file.bfSize = 54 + 246 *4 + newLineByte * newBmpHeight;		// �ļ�����
	newm.file.bfReserverd1 = 0;							// ������ 1
	newm.file.bfReserverd2 = 0;							// ������ 2
	newm.file.bfbfOffBits = 54 + 256 * 4;				// ƫ����
	newm.info.biSize = 40;								// �˽ṹ��С
	newm.info.biWidth = newBmpWidth;					// λͼ�Ŀ��
	newm.info.biHeight = newBmpHeight;					// λͼ�ĸ߶�
	newm.info.biPlanes = 1;								// Ŀ���豸λͼ��
	newm.info.biBitcount = 8;							// ��ɫ���
	newm.info.biCompression = 0;						// λͼѹ������
	newm.info.biSizeImage = newLineByte * newBmpHeight;	// λͼ��С
	newm.info.biXPelsPermeter = 0;                      // λͼˮƽ�ֱ���
	newm.info.biYPelsPermeter = 0;                      // λͼ��ֱ�ֱ���
	newm.info.biClrUsed = 0;                            // λͼʵ��ʹ����ɫ��
	newm.info.biClrImportant = 0;                       // λͼ��ʾ�бȽ���Ҫ��ɫ��

	// д���ɫ��
	memcpy((void *)(newpColorTable1), (void *)(input->pColorTable), 256 * 4);
	newm.pColorTable = (RGBQUAD*)newpColorTable1;

	//д��λͼ����
	newm.imgBuf = newBmpBuf1;

	return newm;
}

/****************************************************************************/
/*                                                                          */
/*              ����������                                                                                                                                  */
/*                                                                          */
/****************************************************************************/
void randinterval(int *row, int *col, int mrow, int mcol, int count, int key)
{
	double *a = malloc(count * sizeof(double));					//������α������Ŀռ�
	int r = 1, c = 1, i;										//���建��
	int interval1, interval2;									//�������Ϊ����������������ֵ
	interval1 = mrow * mcol / count + 1;
	interval2 = interval1 - 2;
	if(interval2 <= 0)											//����������С��0,����ͼƬ������̶Ȳ���������Ϣ
	{
	    perror("����̫С���ܽ�������Ϣ���ؽ�ȥ!");
		exit(EXIT_FAILURE);
	}
	srand(key);													//α�������rand������ָ��ȷ���������������
	for(i = 0; i < count; i++)
	{
		a[i] = rand();											//rand��������0-32768�����������
		row[i] = 0;												//���г�ʼ��
		col[i] = 0;
	}
	row[1] = r;
	col[1] = c;

	//�ж�������Ƿ�����м�ֵ,����ȥ���һ��ֵ,������ȡ�������ֵ
	for(i = 1; i < count; i ++)
	{
	    if(a[i] >  16339)
	        c = c + interval1;
	    else
	        c = c + interval2;
	    if(c > mcol)						//����һ��������Ӧ�仯
	    {
	        r = r + c / mcol;
	        if(r > mrow)
	        {
	            perror("����̫С���ܽ�������Ϣ���ؽ�ȥ!");
	            exit(EXIT_FAILURE);
	        }
	        c = c % mcol;
	        if(c == 0)
	            c = 1;
	    }
	    row[i] = r;
	    col[i] = c;
	    //printf("row%d:%d  col%d:%d\n", i, r, i, c);			//��ӡ���ɵ���������
	}
	free(a);
}

/****************************************************************************/
/*                                                                          */
/*              �ַ���Ӧλ��ȡ                                                                                                                             */
/*                                                                          */
/****************************************************************************/
char GetBit(char name, int indexof)
{
	return ((name >> (indexof-1)) - (name >> indexof << 1));
}

/****************************************************************************/
/*                                                                          */
/*              �ַ�����Ӧλ��ֵ                                                                                                                       */
/*                                                                          */
/****************************************************************************/
void SetBit(char *name, int indexof, int bl, int inof)
{
	*(name + inof) &= (~(1 << (indexof - 1)));
	*(name + inof) += bl << (indexof - 1);
}
