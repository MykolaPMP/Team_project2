#include <iostream>
#include "Windows.h";
#include <fstream>
using namespace std;
char BinaryToChar(int *word);


int main()
{

	BITMAPFILEHEADER bfh_l;
	BITMAPINFOHEADER bih_l;
	RGBTRIPLE rgb_l;
	FILE * f1, *f2;

	f1 = fopen("n.bmp", "r+b");
	f2 = fopen("4.bmp", "w+b");

	fread(&bfh_l, sizeof(bfh_l), 1, f1);               //Запихиваем файловый заголовок в структуру BITMAPFILEHEADER
	fwrite(&bfh_l, sizeof(bfh_l), 1, f2);   //
	fread(&bih_l, sizeof(bih_l), 1, f1);               //Запихиваем заголовок изображения в структуру BITMAPINFOHEADER
	fwrite(&bih_l, sizeof(bih_l), 1, f2);   //

	size_t padding = 0;
	if ((bih_l.biWidth * 3) % 4) 
	{
		padding = 4 - (bih_l.biWidth * 3) % 4;
	}

	for (int i = 0; i< 1; i++)
	{
		
		/*for (int j = 0; j < 10000; j++)
		{*/
			while (!feof(f1))
			{
				fread(&rgb_l, sizeof(rgb_l), 1, f1);

				//cout << (byte)rgb_l.rgbtBlue << ' ';
			/*	if (rgb_l.rgbtGreen < 255)
				{
					rgb_l.rgbtGreen=rgb_l.rgbtGreen+1;
				}*/
				//cout << (int)rgb_l.rgbtBlue << endl;

				fwrite(&rgb_l, sizeof(rgb_l), 1, f2);

				if (padding != 0)
				{
					fread(&rgb_l, padding, 1, f1);
					fwrite(&rgb_l, padding, 1, f2);
				}
			}
		/*}*/

		
	}
	fclose(f1);
	fclose(f2);

	/*f2 = fopen("4.bmp", "r");
	fread(&bfh_l, sizeof(bfh_l), 1, f2);
	fread(&bih_l, sizeof(bih_l), 1, f2);
	fclose(f2);*/



	system("pause");
	return 0;
}

char BinaryToChar(int *word) 
{
	int n = 0;
	for (int i = 0; i < 7; i++) 
	{
		n += word[i] * pow(2, 6-i);
	}
	
	return n;
}
