#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>
#include <windef.h>
#include <cmath>
using namespace std;
using namespace cv;

double sum(vector<double> Vnum, int n);
double MutilSum(vector<double> Vx, vector<double> Vy, int n);
double RelatePow(vector<double> Vx, int n, int ex);
double RelateMutiXY(vector<double> Vx, vector<double> Vy, int n, int ex);
void EMatrix(vector<double> Vx, vector<double> Vy, int n, int ex, double coefficient[]);
void CalEquation(int exp, double coefficient[]);
double F(double c[], int l, int m);
double Em[6][4];
void LineFitLeastSquares(float *data_x, float *data_y, int data_n, vector<float> &vResult, float &a, float &b);
void kuangtu(Mat Inimg_labels, Mat Inimg_imgstats, Mat Inimg_centriods, unsigned char *imagedata_gray, int m, int n);
//int FastBlanket(Mat &img, int epsilon)
//{
//
//	float Nr1[5], Nr2[5], Nr[5], log_x[5], log_y[5];
//	
//	for (int i = 0; i < img.rows; i++) {
//		uchar* data = img.ptr<uchar>(i);
//		int MAX_ = 0;//选取每行图像的最大值
//		int MIN_ = 300; //选取每行元素的最小值
//		for (int j = 0; j < img.cols; j++) {
//			if (MAX_ < data[j]) {
//				MAX_ = data[j];
//			}
//			if (MIN_ > data[j]) {
//				MIN_ = data[j];
//			}
//		}
//		for (int k = 1; k < 1 + epsilon; k++) {
//			Nr1[k - 1] = min((255 - MAX_) / k, MIN_ / k);
//			printf("Nr:%f", Nr1[k - 1]);
//		}
//	}
//	
//	for (int j = 0; j < img.cols; j++) {
//		int MAX_ = 0; int MIN_ = 300;
//		for (int i = 0; i < img.rows; i++) {
//			uchar* data = img.ptr<uchar>(i);
//			if (MAX_ < data[j]) {
//				MAX_ = data[j];
//			}
//			if (MIN_ > data[j]) {
//				MIN_ = data[j];
//			}
//		}
//		for (int k = 1; k < 1 + epsilon; k++) {
//			Nr2[k - 1] = min((255 - MAX_) / k, MIN_ / k);
//		}
//	}
//
//	for (int i = 0; i < epsilon; i++) {
//		Nr[i] = min(Nr1[i], Nr2[i]);
//	}
//
//	
//	
//
//	//拟合方程
//	printf("succes");
//	for (int i = 0; i < 5; i++)
//	{
//		printf("x=%f\n", log_x[i]);
//		printf("y=%f\n", log_y[i]);
//	}
//	double coefficient[5];
//	memset(coefficient, 0, sizeof(double) * 5);
//	vector<double> vx, vy;
//	for (int i = 0; i < 5; i++)
//	{
//		vx.push_back(log_x[i]);
//		vy.push_back(log_y[i]);
//	}
//	EMatrix(vx, vy, 5, 3, coefficient);
//	printf("拟合方程为：y = %lf + %lfx + %lfx^2 \n", coefficient[1], coefficient[2], coefficient[3]);
//	int D = coefficient[2] + 1 + coefficient[1] / 5;
//	/*for (int  i = 0; i < 5; i++)
//	{
//		E = E + abs(log)
//	}*/
//	return D;
//}

void Fractal(Mat dst, int epsilon, float &s, float &d, float &e);
void S_E_selection(unsigned char *Inimg, unsigned char *s, unsigned char *d, unsigned char *e, unsigned char *imagedata_gray,int height, int width);
int FastBlanket(unsigned char *Inimg, int height, int width, unsigned char *imagedata_gray)
{
	Mat mat(height, width,CV_8UC1, Inimg);
	

	Mat a(height, width, CV_8UC1, imagedata_gray), Inimg_labels, Inimg_stats, Inimg_centriods;
	imshow("asdfwe", a);
	int epsilon = 5;
	int template_size = 5;
	float s_,d_,e_;
	
	Mat dst = Mat::zeros(template_size, template_size, CV_8UC1);
	uchar* dstdata = dst.data;
	Mat S = Mat::zeros(height - template_size + 1, width - template_size + 1, CV_32FC1);
	Mat D = Mat::zeros(height - template_size + 1, width - template_size + 1, CV_32FC1);
	Mat E = Mat::zeros(height - template_size + 1, width - template_size + 1, CV_32FC1);
	unsigned char *s = S.data;
	unsigned char *d = D.data;
	unsigned char *e = E.data;
	int imglabelnum = connectedComponentsWithStats(mat, Inimg_labels, Inimg_stats, Inimg_centriods);
	//imglabelnum类别总数
	for (int m = template_size/2; m < height-template_size/2; m++) {
		for (int n = template_size/2; n < width-template_size/2; n++) {
			for (int x = -template_size/2; x < template_size / 2+1; x++)
				for (int y = -template_size/2; y < template_size / 2+1; y++)
					*(dstdata + (y+template_size/2)*template_size + x+template_size/2) = *(imagedata_gray + (n+y)*(height-template_size/2) + m+x);
			//dst为每个像素点的窗口邻域
			//计算每个像素点的分形维数
			Fractal(dst, epsilon,s_,d_,e_);
			//printf("%d行%d列的分型维数%f\n", m, n, s_);
			*(s + m*(height - template_size + 1) + n) = s_;
			*(d + m*(height - template_size + 1) + n) = d_;
			*(e + m*(height - template_size + 1) + n) = e_;
			
			 //cout << "s_="<< s_ << '\t' << "d_="<< d_ << '\t' << "e_="<< e_ << endl;
		}
	}
	//对分型维数分型误差进行处理
	S_E_selection(Inimg, s, d, e, imagedata_gray, height, width);

	/*
	//拟合方程
	//printf("succes");
	for (int i = 0; i < 5; i++)
	{
		printf("x=%f\n", log_x[i]);
		printf("y=%f\n", log_y[i]);
	}
	double coefficient[5];
	memset(coefficient, 0, sizeof(double) * 5);
	vector<double> vx, vy;
	for (int i = 0; i < 5; i++)
	{
		vx.push_back(log_x[i]);
		vy.push_back(log_y[i]);
	}
	EMatrix(vx, vy, 5, 3, coefficient);
	printf("拟合方程为：y = %lf + %lfx + %lfx^2 \n", coefficient[1], coefficient[2], coefficient[3]);
	double D = coefficient[2] + 1 + coefficient[1] / 5;
	double E = 0;
	for (int i = 0; i < epsilon; i++)
	{
		E = E + abs(log(Nr[i]) - coefficient[1] * log(i));
	}
	printf("%ld", D);
	*/
	return 0;
}


void S_E_selection(unsigned char *Inimg, unsigned char *s, unsigned char *d, unsigned char *e, unsigned char *imagedata_gray,int height, int width) {
	Mat Inimg_labels, Inimg_imgstats, Inimg_centriods, Inimg_label(height, width, CV_8UC1, Inimg);
	int Inimg_imglabelnum = connectedComponentsWithStats(Inimg_label, Inimg_labels, Inimg_imgstats, Inimg_centriods);
	imshow("asdfasf",Inimg_label);
	cout << "Inimg:" <<Inimg_imglabelnum << endl;
	float *Inimg_s = new float[Inimg_imglabelnum];
	float *Inimg_e = new float[Inimg_imglabelnum];
	int *Inimg_num = new int[Inimg_imglabelnum];
	for (int i = 1; i < Inimg_imglabelnum; i++) {
		Inimg_s[i] = 0.0;
		Inimg_e[i] = 0.0;
		Inimg_num[i] = 0;
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (Inimg_labels.at<int>(i, j) != 0) {
				Inimg_num[Inimg_labels.at<int>(i, j)] += 1;
				Inimg_s[Inimg_labels.at<int>(i, j)] += *(s + i*width + j);
				Inimg_e[Inimg_labels.at<int>(i, j)] += *(e + i*width + j);
			}
		}
	}
	int *M_dex = new int[2];//分型维数
	//整个区域的分型维数
	for (int i = 1; i < Inimg_imglabelnum; i++)
		cout << "第" << i << "个区域的分型维数:" << Inimg_s[i] << endl;
		
	for (int i = 1; i < Inimg_imglabelnum; i++)
		cout << "第" << i << "个区域的分型误差:" << Inimg_e[i] << endl;

	for (int i = 1; i < Inimg_imglabelnum; i++)
		cout << "第" << i << "个区域数量:" << Inimg_num[i] << endl;
	//分形维数
	float average_frat=0.0;
	for (int i = 1; i < Inimg_imglabelnum; i++) {
		average_frat += Inimg_s[i] / Inimg_num[i];
		cout << Inimg_s[i] / Inimg_num[i] << endl;;
	}
	
	average_frat /= Inimg_imglabelnum;
	printf("%f", average_frat);
	Mat a(height, width, CV_8UC1, Inimg);
	for (int i = 0; i < 2; i++) {
		cout << M_dex[i] << endl;
		for (int m = 0; m < height; m++)
			for (int n = 0; n < width; n++)
				if (Inimg_labels.at<int>(m, n) >= average_frat)
					*(Inimg + m*width + n) = 0;
				else
					kuangtu(Inimg_labels, Inimg_imgstats, Inimg_centriods, imagedata_gray,m,n);
	}
	imshow("分形维数", a);
}
//标签矩阵 Inimg_labels
//矩形矩阵 Inimg_imgstats
//中心矩阵 Inimg_centriods
//灰度图像 imagedata_gray
void kuangtu(Mat Inimg_labels,Mat Inimg_imgstats,Mat Inimg_centriods,unsigned char *imagedata_gray,int m,int n) {
	Mat window_pic(Inimg_labels.rows, Inimg_labels.cols, CV_8UC1, imagedata_gray);
	Inimg_centriods.at<int>(m,n)
	rectangle(window_pic, );
}



//计算窗口的分形维数、分型误差
void Fractal(Mat dst, int epsilon, float &s, float &d, float &e) {
	//建立二维数组
	float **N = new float*[5];
	for (int i = 0; i < 5; ++i) {
		N[i] = new float[epsilon];
	}
	float *data_x = new float[epsilon];
	float *data_y = new float[epsilon];
	unsigned char *dst_data = dst.data;
	int MAX_a = 0, MIN_a = 300, MAX_b = 0, MIN_b = 300;
	vector<float> cvResult;
	for (int k = 0; k < epsilon; k++) {
		//按行
		for (int i = 0; i < dst.rows; i++) {
			int MAX_row = 0;
			for (int j = 0; j < dst.cols; j++) {
				if (*(dst_data + j*dst.rows + i) > MAX_row)
					MAX_row = *(dst_data + i*dst.cols + j);
			}
			if (MAX_a < MAX_row)
				MAX_a = MAX_row;
			if (MIN_a > MAX_row)
				MIN_a = MAX_row;
		}
		//int k = k;
		N[0][k] = min((255 - MAX_a) / (k + 1), MIN_a / (k + 1));

		//按列
		for (int i = 0; i < dst.cols; i++) {
			int MAX_col = 0;
			for (int j = 0; j < dst.rows; j++) {
				if (*(dst_data + j*dst.cols + i) > MAX_col)
					MAX_col = *(dst_data + j*dst.cols + i);
			}
			if (MAX_b < MAX_col)
				MAX_b = MAX_col;
			if (MIN_b > MAX_col)
				MIN_b = MAX_col;
		}
		N[1][k] = min((255 - MAX_b) / (k + 1), MIN_b / (k + 1));

		N[2][k] = min(N[0][k], N[1][k]);

		N[3][k] = log(k + 1);

		N[4][k] = log(N[2][k]);
		//cout << N[3][k] <<"\t"<< N[4][k] << endl;
		data_x[k] = N[3][k]+1;
		data_y[k] = N[4][k]+1;
	}
	//N[2]每个epsilon对应的N[epsilon];N[3]--->log x;N[4]----->logN[epsilon];
	//根据这些进行拟合求解获得S,D,E参数
	float a, b;
	
	//cout << data_x[0]<<data_x[1]<<data_x[2]<<data_x[3] << endl;
	//求得拟合直线
	//cout << Array << endl;
	//
	LineFitLeastSquares(data_x, data_y, epsilon, cvResult, a, b);
	//cout << a << '\t' << b << endl;
	
	//cout << A.at<float>(0,0) << endl;
	//cout << A.at<float>(0, 0) << endl;
	//cout << cvResult[0] << '\t' << cvResult[1] << endl;
	//cout << "k=" << k << "b=" << b << endl;
	if (isnan(a)) {
		a = 0;
	}
	if (isnan(b)) {
		b = 0;
	}
	d = a + 1 + b/epsilon;
	e = 0.0;
	s = b;
	for (int i = 0; i < epsilon; i++) {
		e += abs(N[4][i]-a*N[3][i]);
	}
	//cout << "d=" << d << "e=" << e << "s+" << s << endl;
}


void LineFitLeastSquares(float *data_x, float *data_y, int data_n, vector<float> &vResult, float &a, float &b)
{
	float A = 0.0;
	float B = 0.0;
	float C = 0.0;
	float D = 0.0;
	float E = 0.0;
	float F = 0.0;

	for (int i = 0; i < data_n; i++)
	{
		A += data_x[i] * data_x[i];
		B += data_x[i];
		C += data_x[i] * data_y[i];
		D += data_y[i];
	}

	// 计算斜率a和截距b
	float temp = 0;
	if (temp = (data_n*A - B*B))// 判断分母不为0
	{
		a = (data_n*C - B*D) / (temp+1e-8);
		b = (A*D - B*C) / (temp+1e-8);
	}
	else
	{
		a = 1;
		b = 0;
	}

}


double sum(vector<double> Vnum, int n)
{
	double dsum = 0;
	for (int i = 0; i<n; i++)
	{
		dsum += Vnum[i];
	}
	return dsum;
}
//乘积和
double MutilSum(vector<double> Vx, vector<double> Vy, int n)
{
	double dMultiSum = 0;
	for (int i = 0; i<n; i++)
	{
		dMultiSum += Vx[i] * Vy[i];
	}
	return dMultiSum;
}
//ex次方和
double RelatePow(vector<double> Vx, int n, int ex)
{
	double ReSum = 0;
	for (int i = 0; i<n; i++)
	{
		ReSum += pow(Vx[i], ex);
	}
	return ReSum;
}
//x的ex次方与y的乘积的累加
double RelateMutiXY(vector<double> Vx, vector<double> Vy, int n, int ex)
{
	double dReMultiSum = 0;
	for (int i = 0; i<n; i++)
	{
		dReMultiSum += pow(Vx[i], ex)*Vy[i];
	}
	return dReMultiSum;
}
//计算方程组的增广矩阵
void EMatrix(vector<double> Vx, vector<double> Vy, int n, int ex, double coefficient[])
{
	for (int i = 1; i <= ex; i++)
	{
		for (int j = 1; j <= ex; j++)
		{
			Em[i][j] = RelatePow(Vx, n, i + j - 2);
		}
		Em[i][ex + 1] = RelateMutiXY(Vx, Vy, n, i - 1);
	}
	Em[1][1] = n;
	CalEquation(ex, coefficient);
}
//求解方程
void CalEquation(int exp, double coefficient[])
{
	for (int k = 1; k<exp; k++) //消元过程
	{
		for (int i = k + 1; i<exp + 1; i++)
		{
			double p1 = 0;

			if (Em[k][k] != 0)
				p1 = Em[i][k] / Em[k][k];

			for (int j = k; j<exp + 2; j++)
				Em[i][j] = Em[i][j] - Em[k][j] * p1;
		}
	}
	coefficient[exp] = Em[exp][exp + 1] / Em[exp][exp];
	for (int l = exp - 1; l >= 1; l--)   //回代求解
		coefficient[l] = (Em[l][exp + 1] - F(coefficient, l + 1, exp)) / Em[l][l];
}
//供CalEquation函数调用
double F(double c[], int l, int m)
{
	double sum = 0;
	for (int i = l; i <= m; i++)
		sum += Em[l - 1][i] * c[i];
	return sum;
}


double Regionfractal(Mat &img) {
	int epsilon = 5;
	int i, j;
	int r = img.rows, c = img.cols;
	int template_size = 5;
	int Row = template_size - 1 + r;
	int Col = template_size - 1 + c;

	//初始化未知大小的二维数组
	/*Mat **Img_extension;
	cin >> Row >> Col;
	Img_extension = new Mat *[Row];
	for (int i = 0; i < Row; i++)
	{
	Img_extension[i] = new Mat[Col];
	}*/
	/*
	Mat **Img_extension = NULL;
	Img_extension = (Mat **)realloc(Img_extension, sizeof(Mat *)*r);
	for (int i = 0; i != r; i++) {
	Img_extension[i] = (Mat *)calloc(c, sizeof(Mat));
	}
	*/
	Mat Img_extension(Row, Col, CV_8UC3);
	//	imshow("chushihua", Img_extension);
	uchar* p;
	int *win_pic_r = new int[template_size*template_size];
	int *win_pic_g = new int[template_size*template_size];
	int *win_pic_b = new int[template_size*template_size];
	for (int i = 0; i < Row; i++) {
		for (int j = 0; j < Col; j++) {
			int x = 0;
			if ((i < Row - (template_size - 1) / 2) && (i >= (template_size - 1) / 2) && (j >= (template_size - 1) / 2) && (j < Col - (template_size - 1) / 2)) {
				for (int m = i - (template_size - 1) / 2; m <= i + (template_size - 1) / 2; m++) {
					for (int n = j - (template_size - 1) / 2; n <= j + (template_size - 1) / 2; n++) {
						Vec3b pix = img.at<Vec3b>(m, n);
						win_pic_r[x] = pix[0];
						win_pic_g[x] = pix[1];
						win_pic_b[x] = pix[2];
						x++;
					}
				}
			}
		}
	}

	//Img_extension[i][j] = pix;
	//p = img.ptr<uchar>(i);

	//}
	//else {
	//	Vec3b pix = img.at<Vec3b>(i,j);
	//	Img_extension[i][j] = pix;
	//}
	//	}
	//	}

	/*
	for (i = (template_size + 1) / 2; i < Row - (template_size - 1) / 2; i++)
	{
	for (j = (template_size + 1) / 2; j < Col - (template_size - 1) / 2; j++)
	{
	Vec3b pix = img.at<Vec3b>(i - (template_size + 1) / 2 + 1, j - (template_size + 1) / 2 + 1);
	Img_extension[i][j] = pix;
	}
	}
	*/
	/*
	int **d = NULL;
	d = (int **)realloc(d, sizeof(int *)*r);
	for (int i = 0; i != r; i++) {
	d[i] = (int *)calloc(c, sizeof(int));
	}
	Mat **win_pic = NULL;
	win_pic = (Mat **)realloc(win_pic, sizeof(Mat *)*template_size);
	for (int i = 0; i < template_size; i++) {
	win_pic[i] = (Mat *)calloc(template_size, sizeof(Mat));
	}
	//Mat dst=Mat(img.size(),CV_8UC3,Scalar(255,255,255));//uchar类型转Mat
	int D = 0, E = 0,d_ = 0,e_ = 0;
	//Img_extension = uint8(Img_extension);
	for (i = 0; i < r; i++)
	{
	for (j = 0; j < c; j++)
	{

	for (int m = i; m < i + template_size; m++)
	{
	for (int n = j; n < j + template_size; n++)
	{
	win_pic[m-i][n-j] = Img_extension[m][n];
	//*dst.data = Img_extension[i][j];//uchar类型转Mat
	}
	}
	//d[i][j]= FastBlanket(**win_pic, 5);
	//if (~_isnan(d[i][j]))
	//{
	//D = D + d[i][j];
	//d_ = d_ + 1;
	//}
	if (~isnan(e(i, j))
	{
	E = E + e(i, j);
	e_ = e_ + 1;
	}
	}
	}
	*/
	//D = D / d_;
	//E = E / e_;
	//return D;

	return 0.0;
}



//void rectangle(Mat &img,Mat &outimg,int h,int H)
//{
//	Mat dst;
//	namedWindow("RGB", WINDOW_AUTOSIZE);
//	imshow("RGB", img);
//
//
//	cvtColor(img, dst, CV_BGR2GRAY);
//	namedWindow("GRAY", WINDOW_AUTOSIZE);
//	imshow("GRAY", dst);
//	cout << dst.channels() << endl;
//
//	waitKey(0);
//
//	img.release();
//	dst.release();
//	destroyWindow("RGB");
//	destroyWindow("GRAY");
//	//return 0;
//
//	int r = img.rows;
//	int c = img.cols;
//	int i ,j ;
//	for (i = 0; i < r; i++)
//	{
//		for ( j = 0; j < c; j++)
//		{
//
//		}
//	}
//
//}
