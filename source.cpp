#include <iostream>
#include "Windows.h";
#include <stdio.h>
using namespace std;

void DecimalToBinary(char c, int *word);
char BinaryToChar(int *word);



int main()
{
	// structures
	BITMAPFILEHEADER bfh_l;
	BITMAPINFOHEADER bih_l;
	RGBTRIPLE rgb_l;
	FILE * f1, *f2;

	char*hide = new char[100];
	int *word = new int[7];

	f1 = fopen("6.bmp", "r+b");
	f2 = fopen("4.bmp", "w+b");

	fread(&bfh_l, sizeof(bfh_l), 1, f1);               //BITMAPFILEHEADER
	fwrite(&bfh_l, sizeof(bfh_l), 1, f2);   //
	fread(&bih_l, sizeof(bih_l), 1, f1);               //BITMAPINFOHEADER
	fwrite(&bih_l, sizeof(bih_l), 1, f2);   //

	size_t padding = 0;
	if ((bih_l.biWidth * 3) % 4) 
	{
		padding = 4 - (bih_l.biWidth * 3) % 4;
	}

	cout << "Input your word to code" << endl;
	cin >> hide;
	
	//coding
	for (int i = 0; i < strlen(hide); i++)
	{
		DecimalToBinary(hide[i], word);
		for (int j = 0; j < 7; j++)
		{
			fread(&rgb_l, sizeof(rgb_l), 1, f1);
			if (word[j] == 1)
			{
				if (rgb_l.rgbtRed % 2 != 1)
				{
					rgb_l.rgbtRed++;
				}
			}
			else
			{
				if (rgb_l.rgbtRed % 2 != 0)
				{
					rgb_l.rgbtRed++;
				}
			}
			fwrite(&rgb_l, sizeof(rgb_l), 1, f2);
		}
	}

	while (!feof(f1))
	{	
		fread(&rgb_l, sizeof(rgb_l), 1, f1);
		fwrite(&rgb_l, sizeof(rgb_l), 1, f2);
		if (padding != 0)
			{
				fread(&rgb_l, padding, 1, f1);
				fwrite(&rgb_l, padding, 1, f2);
			}
	}	
	
	_fcloseall();
	f2 = fopen("4.bmp", "r");
	fread(&bfh_l, sizeof(bfh_l), 1, f2);
	fread(&bih_l, sizeof(bih_l), 1, f2);
	//decoding
	cout << "Decoding... decoding..." << endl;
	cout << "and the word was: ";
	
	for (int i = 0; i < strlen(hide) * 7; i++)
	{
		fread(&rgb_l, sizeof(rgb_l), 1, f2);
		if (rgb_l.rgbtRed % 2 == 1)
		{
			word[i % 7] = 1;
		}
		else 
		{
			word[i % 7] = 0;
		}
		if (i % 7 == 6) 
		{
			cout << BinaryToChar(word);
			for (int j = 0; j < 7; j++)
			{
				word[j] = 0;
			}
		}

	}
	cout << endl;
	fclose(f2);


	delete[] word; delete[] hide;
	system("pause");
	return 0;
}


void DecimalToBinary(char c, int *word)
{
	for (int j = 0; j < 7; j++) 
	{
		word[j] = 0;
	}
	int number = (int)c;
	int i = 6;
	while (number != 0)
	{
		word[i] = number % 2;
		number /= 2;
		i--;
	}
}
char BinaryToChar(int *word)
{
	char n = 0,mn=64;
	for (int i = 0; i < 7; i++)
	{
		n += word[i]*mn;
		mn /= 2;
	}
	return n;
}
