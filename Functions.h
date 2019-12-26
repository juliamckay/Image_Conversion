#pragma once
#include "Image.h"
#include <string>
#include <fstream>
#include <iostream>

void read(char*, Image&);
void write(char* path, Image& image);
void Multiply(Image& image1, Image& image2, Image& image3);
void Subtract(Image& image1, Image& image2, Image& image3);
void Screen(Image& image1, Image& image2, Image& image3);
void Overlay(Image& image1, Image& image2, Image& image3);
