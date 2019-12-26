#include "Tests.h"

bool Test(Image& output, Image& example)
{
	for (unsigned int i = 0; i < output.pixels.size(); i++)
	{
		Image::Pixel outputPixel = output.pixels.at(i);
		Image::Pixel examplePixel = example.pixels.at(i);

		if ((outputPixel.red != examplePixel.red) || (outputPixel.blue != examplePixel.blue) || (outputPixel.green != examplePixel.green))
		{
			return false;
		}
	}

	return true;
}

void Test1()
{
	Image image1;
	Image image2;
	Image image3;
	Image output;
	Image example;

	read((char*)"input/layer1.tga", image1);
	read((char*)"input/pattern1.tga", image2);
	Multiply(image1, image2, image3);
	image3.header = image1.header;
	write((char*)"output/part1.tga", image3);

	read((char*)"output/part1.tga", output);
	read((char*)"examples/EXAMPLE_part1.tga", example);
	cout << "Test 1 ........ ";
	if (Test(output, example))
	{
		cout << "PASSED\n";
	}
	else
	{
		cout << "FAILED\n";
	}
}

void Test2()
{
	Image image1;
	Image image2;
	Image image3;
	Image output;
	Image example;

	read((char*)"input/layer2.tga", image1);
	read((char*)"input/car.tga", image2);
	Subtract(image1, image2, image3);
	image3.header = image1.header;
	write((char*)"output/part2.tga", image3);

	read((char*)"output/part2.tga", output);
	read((char*)"examples/EXAMPLE_part2.tga", example);
	cout << "Test 2 ........ ";
	if (Test(output, example))
	{
		cout << "PASSED\n";
	}
	else
	{
		cout << "FAILED\n";
	}
}

void Test3()
{
	Image image1;
	Image image2;
	Image image3;
	Image image4;
	Image image5;
	Image output;
	Image example;

	read((char*)"input/layer1.tga", image1);
	read((char*)"input/pattern2.tga", image2);
	Multiply(image1, image2, image3);
	image3.header = image1.header;

	read((char*)"input/text.tga", image4);
	Screen(image4, image3, image5);
	image5.header = image4.header;
	write((char*)"output/part3.tga", image5);

	read((char*)"output/part3.tga", output);
	read((char*)"examples/EXAMPLE_part3.tga", example);
	cout << "Test 3 ........ ";
	if (Test(output, example))
	{
		cout << "PASSED\n";
	}
	else
	{
		cout << "FAILED\n";
	}
}

void Test4()
{
	Image image1;
	Image image2;
	Image image3;
	Image image4;
	Image image5;
	Image output;
	Image example;

	read((char*)"input/layer2.tga", image1);
	read((char*)"input/circles.tga", image2);
	Multiply(image1, image2, image3);
	image3.header = image1.header;

	read((char*)"input/pattern2.tga", image4);
	Subtract(image4, image3, image5);
	image5.header = image4.header;
	write((char*)"output/part4.tga", image5);

	read((char*)"output/part4.tga", output);
	read((char*)"examples/EXAMPLE_part4.tga", example);
	cout << "Test 4 ........ ";
	if (Test(output, example))
	{
		cout << "PASSED\n";
	}
	else
	{
		cout << "FAILED\n";
	}
}

void Test5()
{
	Image image1;
	Image image2;
	Image image3;
	Image output;
	Image example;

	read((char*)"input/layer1.tga", image1);
	read((char*)"input/pattern1.tga", image2);
	image3.header = image1.header;
	Overlay(image1, image2, image3);

	write((char*)"output/part5.tga", image3);

	read((char*)"output/part5.tga", output);
	read((char*)"examples/EXAMPLE_part5.tga", example);
	cout << "Test 5 ........ ";
	if (Test(output, example))
	{
		cout << "PASSED\n";
	}
	else
	{
		cout << "FAILED\n";
	}

}

void Test6()
{
	Image image1;
	Image output;
	Image example;


	read((char*)"input/car.tga", image1);

	for (unsigned int i = 0; i < image1.pixels.size(); i++)
	{
		if (image1.pixels.at(i).green > 55)
		{
			image1.pixels.at(i).green = 255;
		}
		else
		{
			image1.pixels.at(i).green += 200;
		}
	}
	write((char*)"output/part6.tga", image1);

	read((char*)"output/part6.tga", output);
	read((char*)"examples/EXAMPLE_part6.tga", example);
	cout << "Test 6 ........ ";
	if (Test(output, example))
	{
		cout << "PASSED\n";
	}
	else
	{
		cout << "FAILED\n";
	}
}

void Test7()
{
	Image image1;
	Image output;
	Image example;


	read((char*)"input/car.tga", image1);

	for (unsigned int i = 0; i < image1.pixels.size(); i++)
	{
		image1.pixels.at(i).blue = 0;

		int scaledRed = ((int)image1.pixels.at(i).red) * 4;
		if (scaledRed > 255)
		{
			image1.pixels.at(i).red = 255;
		}
		else
		{
			image1.pixels.at(i).red = scaledRed;
		}
	}
	write((char*)"output/part7.tga", image1);

	read((char*)"output/part7.tga", output);
	read((char*)"examples/EXAMPLE_part7.tga", example);
	cout << "Test 7 ........ ";
	if (Test(output, example))
	{
		cout << "PASSED\n";
	}
	else
	{
		cout << "FAILED\n";
	}
}

void Test8()
{
	Image image1;
	Image outputr;
	Image outputb;
	Image outputg;
	Image exampler;
	Image exampleb;
	Image exampleg;

	read((char*)"input/car.tga", image1);
	outputr.header = image1.header;
	outputb.header = image1.header;
	outputg.header = image1.header;

	for (unsigned int i = 0; i < image1.pixels.size(); i++)
	{
		Image::Pixel redPixel;
		Image::Pixel greenPixel;
		Image::Pixel bluePixel;

		redPixel.red = image1.pixels.at(i).red;
		redPixel.blue = image1.pixels.at(i).red;
		redPixel.green = image1.pixels.at(i).red;

		bluePixel.red = image1.pixels.at(i).blue;
		bluePixel.blue = image1.pixels.at(i).blue;
		bluePixel.green = image1.pixels.at(i).blue;

		greenPixel.red = image1.pixels.at(i).green;
		greenPixel.blue = image1.pixels.at(i).green;
		greenPixel.green = image1.pixels.at(i).green;

		outputr.pixels.push_back(redPixel);
		outputb.pixels.push_back(bluePixel);
		outputg.pixels.push_back(greenPixel);
	}

	bool part1 = false;
	bool part2 = false;
	bool part3 = false;

	read((char*)"examples/EXAMPLE_part8_r.tga", exampler);
	read((char*)"examples/EXAMPLE_part8_b.tga", exampleb);
	read((char*)"examples/EXAMPLE_part8_g.tga", exampleg);

	cout << "Test 8 ........";
	if (Test(outputr, exampler))
	{
		part1 = true;
	}
	else
	{
		cout << "FAILED (R)" << endl;
	}
	if (Test(outputb, exampleb))
	{
		part2 = true;
	}
	else
	{
		cout << "FAILED (B)" << endl;
	}
	if (Test(outputg, exampleg))
	{
		part3 = true;
	}
	else
	{
		cout << "FAILED (G)" << endl;
	}

	if (part1 && part2 && part3)
	{
		cout << "PASSED" << endl;
	}

	write((char*)"output/part8_r.tga", outputr);
	write((char*)"output/part8_b.tga", outputb);
	write((char*)"output/part8_g.tga", outputg);

}

void Test9()
{
	Image image1;
	Image image2;
	Image image3;
	Image image4;
	Image output;
	Image example;

	read((char*)"input/layer_red.tga", image1);
	read((char*)"input/layer_green.tga", image2);
	read((char*)"input/layer_blue.tga", image3);

	image4.header = image1.header;

	for (unsigned int i = 0; i < image1.pixels.size(); i++)
	{
		Image::Pixel tempPixel;

		tempPixel.red = image1.pixels.at(i).red;
		tempPixel.green = image2.pixels.at(i).green;
		tempPixel.blue = image3.pixels.at(i).blue;

		image4.pixels.push_back(tempPixel);
	}

	write((char*)"output/part9.tga", image4);

	cout << "Test 9 ........";

	read((char*)"output/part9.tga", output);
	read((char*)"examples/EXAMPLE_part9.tga", example);

	if (Test(output, example))
	{
		cout << "PASSED" << endl;
	}
	else
	{
		cout << "FAILED" << endl;
	}
}

void Test10()
{
	Image image1;
	Image image2;
	Image output;
	Image example;

	read((char*)"input/text2.tga", image1);
	image2.header = image1.header;

	for (unsigned int i = image1.pixels.size(); i > 0; i--)
	{
		int index = i - 1;
		Image::Pixel tempPixel = image1.pixels.at(index);
		image2.pixels.push_back(tempPixel);
	}
	write((char*)"output/part10.tga", image2);

	read((char*)"output/part10.tga", output);
	read((char*)"examples/EXAMPLE_part10.tga", example);
	cout << "Test 10 ........";
	if (Test(output, example))
	{
		cout << "PASSED" << endl;
	}
	else
	{
		cout << "FAILED" << endl;
	}
}