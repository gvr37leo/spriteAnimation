#pragma once
#include "ChiliWin.h"
#include "Colors.h"
#include <fstream>
#include <string>


class Surface {
public:
	Color* image;
	int width;
	int height;

	Surface() = default;

	Surface(int width, int height) {
		image = new Color[width * height];
		this->width = width;
		this->height = height;
	}

	//Surface(Surface&) {

	//}
	//Surface& operator=(Surface&) {

	//}

	Surface(std::string filename) {
		std::ifstream file(filename, std::ios::binary);
		BITMAPFILEHEADER fheader;
		BITMAPINFOHEADER infoheader;

		file.read((char*)(&fheader), sizeof(fheader));
		file.read((char*)(&infoheader), sizeof(infoheader));

		width = infoheader.biWidth;
		height = infoheader.biHeight;

		image = new Color[width * height];

		file.seekg(fheader.bfOffBits);
		
		int colorSize = 3;
		if (infoheader.biBitCount == 32) {
			colorSize = 4;
		}
		int padding = ((4 - width * colorSize) % 4) % 4;

		int ystart = height - 1;//bottom to top
		int yend = -1;
		int ychange = -1;
		if (height < 0) {//top to bottom
			height = -height;
			ystart = 0;
			yend = height;
			ychange = 1;
		}
		
		for (int y = ystart; y != yend; y += ychange) {
			for (int x = 0; x < width; x++) {
				if (infoheader.biBitCount == 32) {
					putPixel(x, y, Color(file.get(),file.get(), file.get(), file.get()));
				}
				else {
					putPixel(x, y, Color(file.get(), file.get(), file.get()));
				}
			}
			if (infoheader.biBitCount == 24) {
				file.seekg(padding, std::ios::cur);
			}
		}


	}

	~Surface() {
		delete image;
	}

	Color getPixel(int x, int y) {
		return image[y * width + x];
	};


	void putPixel(int x, int y, Color c) {
		image[y * width + x] = c;
	};
};
