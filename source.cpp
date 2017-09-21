#include <iostream>
#include "Windows.h";
#include <fstream>
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



	f1 = fopen("n.bmp", "r+b");
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

	for (int i = 0; i< 1; i++)
	{
		
		while (!feof(f1))
		{
			//coding
			for (int i = 0; i < strlen(hide); i++) 
			{
				DecimalToBinary(hide[i],word);
				for (int j = 0; j < 7; j++)
				{
					fread(&rgb_l, sizeof(rgb_l), 1, f1);
					if (word[j] == 1) 
					{
						if (rgb_l.rgbtBlue % 2 != 1) 
						{
							rgb_l.rgbtBlue++;
						}
					}
					else
					{
						if (rgb_l.rgbtBlue % 2 != 0)
						{
							rgb_l.rgbtBlue--;
						}
					}
						fwrite(&rgb_l, sizeof(rgb_l), 1, f2);
					}
				}

				fread(&rgb_l, sizeof(rgb_l), 1, f1);
				fwrite(&rgb_l, sizeof(rgb_l), 1, f2);
				if (padding != 0)
				{
					fread(&rgb_l, padding, 1, f1);
					fwrite(&rgb_l, padding, 1, f2);
				}
			}	
	}
	fclose(f1);
	fclose(f2);
	f2 = fopen("4.bmp", "r");
	fread(&bfh_l, sizeof(bfh_l), 1, f2);
	fread(&bih_l, sizeof(bih_l), 1, f2);
	//decoding
	for (int i = 0; i < strlen(hide) * 7; i++)
	{
		fread(&rgb_l, sizeof(rgb_l), 1, f1);
		if (rgb_l.rgbtBlue % 2 == 0)
		{
			word[i % 7] = 0;
		}
		else 
		{ 
			word[i % 7] = 1; 
		}
		if (i % 7 == 6) 
		{
			cout << BinaryToChar(word);
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
	int n = 0;
	for (int i = 0; i < 7; i++)
	{
		n += word[i] * pow(2, 6 - i);
	}
	return n;
}
