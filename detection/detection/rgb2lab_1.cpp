#include "stdafx.h"
#include <math.h>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const float param_13 = 1.0f / 3.0f;
const float param_16116 = 16.0f / 116.0f;
const float Xn = 0.950456f;
const float Yn = 1.0f;
const float Zn = 1.088754f;
float r, b, g, X, Y, Z, fx, fy, fz;

float gamma(float x) {
	if (x > 0.04045)
		return pow((x + 0.055f) / 1.055f, 2.4f);
	else
		return (x / 12.92);
}
float f(float x) {
	if (x > 0.008856f)
		return pow(x, param_13);
	else
		return 7.787f * x + param_16116;
}


void rgb2lab(Mat &img, Mat &lab) {
	for (int i = 0; i < img.rows; i++) {
		Vec3b *data = img.ptr<Vec3b>(i);
		Vec3b *data_lab = lab.ptr<Vec3b>(i);
		for (int j = 0; j < img.cols; j++) {
			Vec3b &pix = *data++;
			Vec3b &pix_lab = *data_lab++;
			r = pix[0] / 255.0f;
			g = pix[1] / 255.0f;
			b = pix[2] / 255.0f;
			r = gamma(r);
			g = gamma(g);
			b = gamma(b);
			X = 0.4125f*r + 0.3576f*g + 0.1804f*b;
			Y = 0.2126f*r + 0.7152f*g + 0.0722f*b;
			Z = 0.0193f*r + 0.1192f*g + 0.9502f*b;
			fx = f(X / Xn);
			fy = f(Y / Yn);
			fz = f(Z / Zn);
			if (Y / Yn > 0.008856f)
				pix_lab[0] = 116.0f * pow(Y / Yn, param_13) - 16.0f;
			else
				pix_lab[0] = 903.3f * (7.787f * Y / Yn + param_16116);
			//pix_lab[0] = 116.0f * fy - 16.0f;
			pix_lab[1] = 500.0f * (fx - fy);
			pix_lab[2] = 200.0f * (fy - fz);
		}
	}
}
