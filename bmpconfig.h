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
	unsigned short int		bfType;         // 位图文件的类型，必须为 BM
	unsigned int			bfSize;       	// 文件大小，以字节为单位
	unsigned short int		bfReserverd1; 	// 位图文件保留字，必须为0
	unsigned short int		bfReserverd2; 	// 位图文件保留字，必须为0
	unsigned int 			bfbfOffBits;  	// 位图文件头到数据的偏移量，以字节为单位
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
	int 		biSize;					    // 该结构大小，字节为单位
	int 		biWidth;				    // 图形宽度以象素为单位
	int 		biHeight;				    // 图形高度以象素为单位
	short int 	biPlanes;				    // 目标设备的级别，必须为1
	short int 	biBitcount;				    // 颜色深度，每个象素所需要的位数
	int 		biCompression;			    // 位图的压缩类型
	int 		biSizeImage;			    // 位图的大小，以字节为单位
	int 		biXPelsPermeter;		    // 位图水平分辨率，每米像素数
	int 		biYPelsPermeter;		    // 位图垂直分辨率，每米像素数
	int 		biClrUsed;				    // 位图实际使用的颜色表中的颜色数
	int 		biClrImportant;			    // 位图显示过程中重要的颜色数
}BITMAPINFOHEADER;

typedef struct
{
	BITMAPFILEHEADER file;                  // 文件信息区
	BITMAPINFOHEADER info;                  // 图象信息区
	RGBQUAD *pColorTable;                   // 调色板
	unsigned char *imgBuf;					// 位图数据
}bmp;
/****************************************************************************/
/*                                                                          */
/*              函数声明                                                    */
/*                                                                          */
/****************************************************************************/
bmp ReadBmp(char *bmpName);				// 读取 bmp 图片
int SaveBmp(char *bmpName, bmp *m);		// 保存 bmp 图片
bmp LsbHide(bmp *m, const int *row, const int *col, const int *info);
void LsbGet(bmp *m, int *goaltext, const int *row, const int *col);
bmp Compare(bmp *input, bmp *output);
void randinterval(int *row, int *col, int mrow, int mcol, int count, int key);
char GetBit(char name, int indexof);				//读取字符的某一位
void SetBit(char *name, int indexof, int bl, int inof);		//写入字符的特定位

#define INFO_LEN 26*7

#endif
