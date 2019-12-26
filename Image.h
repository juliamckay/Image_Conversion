#pragma once
#include <vector>

using namespace std;

struct Image
{
	struct Header
	{
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
	};
	struct Pixel
	{
		unsigned char blue;
		unsigned char green;
		unsigned char red;
	};

	vector<Pixel> pixels;
	Header header;
};