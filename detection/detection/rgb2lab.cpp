#include "stdafx.h"
//#include <math.h>
//#include "rgb2lab.h"
//
//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
////https://blog.csdn.net/grafx/article/details/59482320
//
//const float param_13 = 1.0f / 3.0f;
//const float param_16116 = 16.0f / 116.0f;
//const float Xn = 0.950456f;
//const float Yn = 1.0f;
//const float Zn = 1.088754f;
//
////void XYZ2RGB(float X, float Y, float Z, float *R, float *G, float *B)
////{
////	float RR, GG, BB;
////	RR = 3.240479f * X - 1.537150f * Y - 0.498535f * Z;
////	GG = -0.969256f * X + 1.875992f * Y + 0.041556f * Z;
////	BB = 0.055648f * X - 0.204043f * Y + 1.057311f * Z;
////
////	*R = (float)CLAMP0255_XY(RR, 1.0f);
////	*G = (float)CLAMP0255_XY(GG, 1.0f);
////	*B = (float)CLAMP0255_XY(BB, 1.0f);
////}
////
////void Lab2XYZ(float L, float a, float b, float *X, float *Y, float *Z)
////{
////	float fX, fY, fZ;
////
////	fY = (L + 16.0f) / 116.0f;
////	if (fY > 0.206893f)
////		*Y = fY * fY * fY;
////	else
////		*Y = (fY - param_16116) / 7.787f;
////
////	fX = a / 500.0f + fY;
////	if (fX > 0.206893f)
////		*X = fX * fX * fX;
////	else
////		*X = (fX - param_16116) / 7.787f;
////
////	fZ = fY - b / 200.0f;
////	if (fZ > 0.206893f)
////		*Z = fZ * fZ * fZ;
////	else
////		*Z = (fZ - param_16116) / 7.787f;
////
////	(*X) *= Xn;
////	(*Y) *= Yn;
////	(*Z) *= Zn;
////}
//
////void Lab2RGB(float L, float a, float b, float *R, float *G, float *B)
////{
////	float X = 0.0f, Y = 0.0f, Z = 0.0f;
////	Lab2XYZ(L, a, b, &X, &Y, &Z);
////	XYZ2RGB(X, Y, Z, R, G, B);
////}
//
//
//inline float gamma(float x)
//{
//	return x>0.04045 ? pow((x + 0.055f) / 1.055f, 2.4f) : x / 12.92;
//};
//
//void RGB2XYZ(float R, float G, float B, float *X, float *Y, float *Z)
//{
//	*X = 0.412453f * R + 0.357580f * G + 0.180423f * B;
//	*Y = 0.212671f * R + 0.715160f * G + 0.072169f * B;
//	*Z = 0.019334f * R + 0.119193f * G + 0.950227f * B;
//}
//
//void XYZ2Lab(float X, float Y, float Z, float *L, float *a, float *b)
//{
//	float fX, fY, fZ;
//
//	X /= Xn;
//	Y /= Yn;
//	Z /= Zn;
//
//	if (Y > 0.008856f)
//		fY = pow(Y, param_13);
//	else
//		fY = 7.787f * Y + param_16116;
//
//	*L = 116.0f * fY - 16.0f;
//	*L = *L > 0.0f ? *L : 0.0f;
//
//	if (X > 0.008856f)
//		fX = pow(X, param_13);
//	else
//		fX = 7.787f * X + param_16116;
//
//	if (Z > 0.008856)
//		fZ = pow(Z, param_13);
//	else
//		fZ = 7.787f * Z + param_16116;
//
//	*a = 500.0f * (fX - fY);
//	*b = 200.0f * (fY - fZ);
//}
//
//void RGB2Lab(float R, float G, float B, float *L, float *a, float *b)
//{
//	float X = 0.0f, Y = 0.0f, Z = 0.0f;
//	RGB2XYZ(R, G, B, &X, &Y, &Z);
//	XYZ2Lab(X, Y, Z, L, a, b);
//}
//
//
//
//	
//	/*for (int i = 0; i < pic.rows; i++) {
//		Vec3b *p_rgb = pic.ptr<Vec3b>(i);
//		Vec3b *p_lab = Lab.ptr<Vec3b>(i);
//		for (int j = 0; j < pic.cols; j++) {
//			Vec3b &pix_rgb = *p_rgb++;
//			Vec3b &pix_lab = *p_lab++;
//			RGB2Lab(pix_rgb[0], pix_rgb[1], pix_rgb[2], pix_lab[0], pix_lab[1], pix_lab[2]);
//		}
//	}*/
//	
//
