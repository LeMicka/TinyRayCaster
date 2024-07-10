#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cassert>

uint32_t packColor (const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255) {
	return((a << 24) + (b << 16) + (g << 8) + r);
}

void unpackColor (const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) {
	r = (color >> 0) & 255;
	g = (color >> 8) & 255;
	b = (color >> 16) & 255;
	a = (color >> 24) & 255;
}

void dropPpmImage (const std::string filename, const std::vector<uint32_t> &image, const size_t w, const size_t h){
	assert(image.size() == w*h);
	std::ofstream ofs(filename, std::ios::binary);
	ofs << "P6\n" << w << " " << h << "\n255\n";
	for(size_t i = 0; i < h*w; ++i){
		uint8_t r, g, b, a;
		unpackColor(image[i], r, g, b, a);
		ofs << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
	}
	ofs.close();
}


int main() {
	const size_t win_w = 512; // image width
	const size_t win_h = 512; // image height
	std::vector<uint32_t> framebuffer(win_w * win_h, 255); // The vector that contains the image with every pixels initialised to red
	
	for (size_t j = 0; j < win_h; j++) { // fill the screen with color gradients
		for (size_t i = 0; i < win_w; i++) {
			uint8_t r = 255*j/float(win_h);
			uint8_t g = 255*i/float(win_w);
			uint8_t b = 0;
			framebuffer[i + j * win_w] = packColor(r, g, b);
		}
	}

	dropPpmImage("./out.ppm", framebuffer, win_w, win_h);

	return (0);
}
