#include "Functions.h"

using namespace std;

//tga file is read backwards
void read(char* path, Image& image)
{
	ifstream file(path, ios_base::binary);
	if (file.is_open())
	{
		//read header data first, 18 bytes
		file.read((char*)&image.header.idLength, sizeof(image.header.idLength));
		file.read((char*)&image.header.colorMapType, sizeof(image.header.colorMapType));
		file.read((char*)&image.header.dataTypeCode, sizeof(image.header.dataTypeCode));
		file.read((char*)&image.header.colorMapOrigin, sizeof(image.header.colorMapOrigin));
		file.read((char*)&image.header.colorMapLength, sizeof(image.header.colorMapLength));
		file.read((char*)&image.header.colorMapDepth, sizeof(image.header.colorMapDepth));
		file.read((char*)&image.header.xOrigin, sizeof(image.header.xOrigin));
		file.read((char*)&image.header.yOrigin, sizeof(image.header.yOrigin));
		file.read((char*)&image.header.width, sizeof(image.header.width));
		file.read((char*)&image.header.height, sizeof(image.header.height));
		file.read((char*)&image.header.bitsPerPixel, sizeof(image.header.bitsPerPixel));
		file.read((char*)&image.header.imageDescriptor, sizeof(image.header.imageDescriptor));

		//read in all the pixels, number is equal to width*height of image
		for (int i = 0; i < (image.header.width * image.header.height); i++)  //usually 512 * 512
		{
			//make pixel object, read the 3 bytes of data into the object
			Image::Pixel tempPixel;
			file.read((char*)&tempPixel.blue, sizeof(tempPixel.blue));
			file.read((char*)&tempPixel.green, sizeof(tempPixel.green));
			file.read((char*)&tempPixel.red, sizeof(tempPixel.red));

			//push Pixel back into vector
			image.pixels.push_back(tempPixel);
		}
	}
}

void write(char* path, Image& image)
{
	ofstream file(path, ios_base::binary);

	//write the header data into the file
	file.write((char*)&image.header.idLength, sizeof(image.header.idLength));
	file.write((char*)&image.header.colorMapType, sizeof(image.header.colorMapType));
	file.write((char*)&image.header.dataTypeCode, sizeof(image.header.dataTypeCode));
	file.write((char*)&image.header.colorMapOrigin, sizeof(image.header.colorMapOrigin));
	file.write((char*)&image.header.colorMapLength, sizeof(image.header.colorMapLength));
	file.write((char*)&image.header.colorMapDepth, sizeof(image.header.colorMapDepth));
	file.write((char*)&image.header.xOrigin, sizeof(image.header.xOrigin));
	file.write((char*)&image.header.yOrigin, sizeof(image.header.yOrigin));
	file.write((char*)&image.header.width, sizeof(image.header.width));
	file.write((char*)&image.header.height, sizeof(image.header.height));
	file.write((char*)&image.header.bitsPerPixel, sizeof(image.header.bitsPerPixel));
	file.write((char*)&image.header.imageDescriptor, sizeof(image.header.imageDescriptor));

	//write all of the pixel data to the new file
	for (int i = 0; i < (image.header.width * image.header.height); i++)
	{
		//get Pixel object at index
		Image::Pixel currentPixel = image.pixels.at(i);

		//write color data (blue, green, red)
		file.write((char*)&currentPixel.blue, sizeof(currentPixel.blue));
		file.write((char*)&currentPixel.green, sizeof(currentPixel.green));
		file.write((char*)&currentPixel.red, sizeof(currentPixel.red));
	}
}

void Multiply(Image& image1, Image& image2, Image& image3)
{
	//images need to be same size

	//clamp values at 255 and 0
	for (unsigned int i = 0; i < image1.pixels.size(); i++)
	{
		Image::Pixel tempPixel;

		//normalize all rgb values for image1 pixel at i
		float image1NormalizedRed = image1.pixels.at(i).red / 255.0f;
		float image1NormalizedGreen = image1.pixels.at(i).green / 255.0f;
		float image1NormalizedBlue = image1.pixels.at(i).blue / 255.0f;

		float image2NormalizedRed = image2.pixels.at(i).red / 255.0f;
		float image2NormalizedGreen = image2.pixels.at(i).green / 255.0f;
		float image2NormalizedBlue = image2.pixels.at(i).blue / 255.0f;

		//assign multiplied values
		tempPixel.red = (unsigned char)(((image1NormalizedRed * image2NormalizedRed) * 255) + 0.5f);
		tempPixel.green = (unsigned char)(((image1NormalizedGreen * image2NormalizedGreen) * 255) + 0.5f);
		tempPixel.blue = (unsigned char)(((image1NormalizedBlue * image2NormalizedBlue) * 255) + 0.5f);

		image3.pixels.push_back(tempPixel);
	}
}

void Subtract(Image& image1, Image& image2, Image& image3)
{
	//subtract top layer from bottom layer

	for (unsigned int i = 0; i < image1.pixels.size(); i++)
	{
		Image::Pixel tempPixel;

		//Calculate difference in int variable to prevent underflow
		int redDifference = (int)image2.pixels.at(i).red - (int)image1.pixels.at(i).red;
		int blueDifference = (int)image2.pixels.at(i).blue - (int)image1.pixels.at(i).blue;
		int greenDifference = (int)image2.pixels.at(i).green - (int)image1.pixels.at(i).green;

		//clamp values if they are less than 0 or greater than 255
		redDifference = ((redDifference < 0) ? 0 : redDifference);
		redDifference = ((redDifference > 255) ? 255 : redDifference);
		blueDifference = ((blueDifference < 0) ? 0 : blueDifference);
		blueDifference = ((blueDifference > 255) ? 255 : blueDifference);
		greenDifference = ((greenDifference < 0) ? 0 : greenDifference);
		greenDifference = ((greenDifference > 255) ? 255 : greenDifference);

		//set new values to values in tempPixel and then push back
		tempPixel.red = redDifference;
		tempPixel.green = greenDifference;
		tempPixel.blue = blueDifference;

		image3.pixels.push_back(tempPixel);
	}
}

void Screen(Image& image1, Image& image2, Image& image3)
{
	// c = 1-(1-a)*(1-b)

	for (unsigned int i = 0; i < image1.pixels.size(); i++)
	{
		Image::Pixel tempPixel;

		//normalize all rgb values for image1 pixel at i
		float image1NormalizedRed = image1.pixels.at(i).red / 255.0f;
		float image1NormalizedGreen = image1.pixels.at(i).green / 255.0f;
		float image1NormalizedBlue = image1.pixels.at(i).blue / 255.0f;

		float image2NormalizedRed = image2.pixels.at(i).red / 255.0f;
		float image2NormalizedGreen = image2.pixels.at(i).green / 255.0f;
		float image2NormalizedBlue = image2.pixels.at(i).blue / 255.0f;

		//Take inverse of values and then multiply them
		float screenedRed = 1 - ((1 - image1NormalizedRed) * (1 - image2NormalizedRed));
		float screenedBlue = 1 - ((1 - image1NormalizedBlue) * (1 - image2NormalizedBlue));
		float screenedGreen = 1 - ((1 - image1NormalizedGreen) * (1 - image2NormalizedGreen));

		//assign multiplied values
		tempPixel.red = (unsigned char)((screenedRed * 255) + 0.5f);
		tempPixel.green = (unsigned char)((screenedGreen * 255) + 0.5f);
		tempPixel.blue = (unsigned char)((screenedBlue * 255) + 0.5f);

		image3.pixels.push_back(tempPixel);
	}
}

void Overlay(Image& image1, Image& image2, Image& image3)
{
	for (unsigned int i = 0; i < image1.pixels.size(); i++)
	{
		float tonalVal = image2.pixels.at(i).red / 255.0f;
		Image::Pixel tempPixel;
		
		if (tonalVal <= 0.5f)
		{
			float image1NormalizedRed = image1.pixels.at(i).red / 255.0f;
			float image1NormalizedGreen = image1.pixels.at(i).green / 255.0f;
			float image1NormalizedBlue = image1.pixels.at(i).blue / 255.0f;

			float image2NormalizedRed = image2.pixels.at(i).red / 255.0f;
			float image2NormalizedGreen = image2.pixels.at(i).green / 255.0f;
			float image2NormalizedBlue = image2.pixels.at(i).blue / 255.0f;

			//assign multiplied values
			tempPixel.red = (unsigned char)(((2 * image1NormalizedRed * image2NormalizedRed) * 255) + 0.5f);
			tempPixel.green = (unsigned char)(((2 * image1NormalizedGreen * image2NormalizedGreen) * 255) + 0.5f);
			tempPixel.blue = (unsigned char)(((2 * image1NormalizedBlue * image2NormalizedBlue) * 255) + 0.5f);
		}
		else
		{
			//normalize all rgb values for image1 pixel at i
			float image1NormalizedRed = image1.pixels.at(i).red / 255.0f;
			float image1NormalizedGreen = image1.pixels.at(i).green / 255.0f;
			float image1NormalizedBlue = image1.pixels.at(i).blue / 255.0f;

			float image2NormalizedRed = image2.pixels.at(i).red / 255.0f;
			float image2NormalizedGreen = image2.pixels.at(i).green / 255.0f;
			float image2NormalizedBlue = image2.pixels.at(i).blue / 255.0f;

			//Take inverse of values and then multiply them
			float screenedRed = 1 - (2 * (1 - image1NormalizedRed) * (1 - image2NormalizedRed));
			float screenedBlue = 1 - (2 * (1 - image1NormalizedBlue) * (1 - image2NormalizedBlue));
			float screenedGreen = 1 - (2 * (1 - image1NormalizedGreen) * (1 - image2NormalizedGreen));

			//assign multiplied values
			tempPixel.red = (unsigned char)((screenedRed * 255) + 0.5f);
			tempPixel.green = (unsigned char)((screenedGreen * 255) + 0.5f);
			tempPixel.blue = (unsigned char)((screenedBlue * 255) + 0.5f);
		}

		image3.pixels.push_back(tempPixel);
	}
}