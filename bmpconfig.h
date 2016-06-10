#ifndef BMPCONFIG
#define BMPCONFIG

typedef struct tagRGBQUAD
{
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
	unsigned char rgbReserved;
}RGBQUAD;

typedef struct tagBITMAPFILEHEADER
{
	unsigned short int		bfType;         // λͼ�ļ������ͣ�����Ϊ BM
	unsigned int			bfSize;       	// �ļ���С�����ֽ�Ϊ��λ
	unsigned short int		bfReserverd1; 	// λͼ�ļ������֣�����Ϊ0
	unsigned short int		bfReserverd2; 	// λͼ�ļ������֣�����Ϊ0
	unsigned int 			bfbfOffBits;  	// λͼ�ļ�ͷ�����ݵ�ƫ���������ֽ�Ϊ��λ
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
	int 		biSize;					    // �ýṹ��С���ֽ�Ϊ��λ
	int 		biWidth;				    // ͼ�ο��������Ϊ��λ
	int 		biHeight;				    // ͼ�θ߶�������Ϊ��λ
	short int 	biPlanes;				    // Ŀ���豸�ļ��𣬱���Ϊ1
	short int 	biBitcount;				    // ��ɫ��ȣ�ÿ����������Ҫ��λ��
	int 		biCompression;			    // λͼ��ѹ������
	int 		biSizeImage;			    // λͼ�Ĵ�С�����ֽ�Ϊ��λ
	int 		biXPelsPermeter;		    // λͼˮƽ�ֱ��ʣ�ÿ��������
	int 		biYPelsPermeter;		    // λͼ��ֱ�ֱ��ʣ�ÿ��������
	int 		biClrUsed;				    // λͼʵ��ʹ�õ���ɫ���е���ɫ��
	int 		biClrImportant;			    // λͼ��ʾ��������Ҫ����ɫ��
}BITMAPINFOHEADER;

typedef struct
{
	BITMAPFILEHEADER file;                  // �ļ���Ϣ��
	BITMAPINFOHEADER info;                  // ͼ����Ϣ��
	RGBQUAD *pColorTable;                   // ��ɫ��
	unsigned char *imgBuf;					// λͼ����
}bmp;
/****************************************************************************/
/*                                                                          */
/*              ��������                                                    */
/*                                                                          */
/****************************************************************************/
bmp ReadBmp(char *bmpName);				// ��ȡ bmp ͼƬ
int SaveBmp(char *bmpName, bmp *m);		// ���� bmp ͼƬ
bmp LsbHide(bmp *m, const int *row, const int *col, const int *info);
void LsbGet(bmp *m, int *goaltext, const int *row, const int *col);
bmp Compare(bmp *input, bmp *output);
void randinterval(int *row, int *col, int mrow, int mcol, int count, int key);
char GetBit(char name, int indexof);				//��ȡ�ַ���ĳһλ
void SetBit(char *name, int indexof, int bl, int inof);		//д���ַ����ض�λ

#define INFO_LEN 26*7

#endif
