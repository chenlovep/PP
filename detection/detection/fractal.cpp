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


void Fractal(Mat dst, int epsilon, float &s, float &d, float &e);
void S_E_selection(Mat gray, unsigned char *Inimg, unsigned char *s, unsigned char *d, unsigned char *e, unsigned char *imagedata_gray,int height, int width);
void kuangtu(Mat gray,int ID, Mat Inimg_imgstats);
int FastBlanket(unsigned char *Inimg, int height, int width, unsigned char *imagedata_gray)
{
	Mat mat(height, width,CV_8UC1, Inimg);
	

	Mat gray(height, width, CV_8UC1, imagedata_gray), Inimg_labels, Inimg_stats, Inimg_centriods;
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
	//imglabelnum�������
	for (int m = template_size/2; m < height-template_size/2; m++) {
		for (int n = template_size/2; n < width-template_size/2; n++) {
			for (int x = -template_size/2; x < template_size / 2+1; x++)
				for (int y = -template_size/2; y < template_size / 2+1; y++)
					*(dstdata + (y+template_size/2)*template_size + x+template_size/2) = *(imagedata_gray + (n+y)*(height-template_size/2) + m+x);
			//dstΪÿ�����ص�Ĵ�������
			//����ÿ�����ص�ķ���ά��
			Fractal(dst, epsilon,s_,d_,e_);
			//printf("%d��%d�еķ���ά��%f\n", m, n, s_);
			*(s + m*(height - template_size + 1) + n) = s_;
			*(d + m*(height - template_size + 1) + n) = d_;
			*(e + m*(height - template_size + 1) + n) = e_;
			
			 //cout << "s_="<< s_ << '\t' << "d_="<< d_ << '\t' << "e_="<< e_ << endl;
		}
	}
	//�Է���ά�����������д���
	S_E_selection(gray, Inimg, s, d, e, imagedata_gray, height, width);

	return 0;
}


void S_E_selection(Mat gray, unsigned char *Inimg, unsigned char *s, unsigned char *d, unsigned char *e, unsigned char *imagedata_gray, int height, int width) {
	Mat Inimg_labels, Inimg_imgstats, Inimg_centriods, Inimg_label(height, width, CV_8UC1, Inimg);
	int Inimg_imglabelnum = connectedComponentsWithStats(Inimg_label, Inimg_labels, Inimg_imgstats, Inimg_centriods);
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

	int *M_dex = new int[2];//����ά��
	//��������ķ���ά��
	for (int i = 1; i < Inimg_imglabelnum; i++)
		cout << "��" << i << "������ķ���ά��:" << Inimg_s[i] << endl;

	for (int i = 1; i < Inimg_imglabelnum; i++)
		cout << "��" << i << "������ķ������:" << Inimg_e[i] << endl;

	for (int i = 1; i < Inimg_imglabelnum; i++)
		cout << "��" << i << "����������:" << Inimg_num[i] << endl;

	//ƽ������ά��
	float average_frat = 0.0, average_wucha = 0.0;
	for (int i = 1; i < Inimg_imglabelnum; i++) {
		average_frat += (float)Inimg_s[i] / Inimg_num[i];
		average_wucha += (float)Inimg_e[i] / Inimg_num[i];
		cout << "�������:"<<Inimg_e[i] / Inimg_num[i] << endl;
	}
	for (int i = 1; i < Inimg_imglabelnum; i++) {
		cout << "����ά��:" << Inimg_s[i] / Inimg_num[i] << endl;
	}
	average_frat = (float)average_frat / Inimg_imglabelnum;
	average_wucha = (float)average_wucha / Inimg_imglabelnum;
	printf("%f\n", average_frat);
	printf("%f\n", average_wucha);
	//�����������͵�a��Ŀ���ų�
	int a = 2;
	int *fra_label = new int[a];
	for (int k = 0; k < a; k++) {
		float MIN = 100;int MIN_label = 1;
		for (int i = 1; i < Inimg_imglabelnum; i++) {
			if (MIN > (float)Inimg_e[i]/Inimg_num[i]) {
				MIN = (float)Inimg_e[i]/Inimg_num[i];
				MIN_label = i;
			}
		}
		fra_label[k] = MIN_label;
		Inimg_e[MIN_label] = 10000;
	}
	cout << fra_label << endl;
	
	//������ά����͵�b��Ŀ���ų�
	int b = 5;
	int *wucha_label = new int[a];
	for (int i = 0; i < b; i++) {
		float MIN = 100;int MIN_label = 1;
		for (int i = 1; i < Inimg_imglabelnum; i++) {
			if (MIN > (float)Inimg_s[i] / Inimg_num[i]) {
				MIN = (float)Inimg_s[i] / Inimg_num[i];
				MIN_label = i;
			}
		}
		if (MIN_label != fra_label[0] && MIN_label != fra_label[1])
			wucha_label[i] = MIN_label;
		else
			i -= 1;
		Inimg_s[MIN_label] = 10000;
	}


	for (int i = 0; i < 2; i++) {
		cout << fra_label[i] << '\t' << wucha_label[i] << endl;
	}
	for (int j = 1; j < Inimg_imglabelnum; j++) {
		if (j != wucha_label[0] && j != wucha_label[1] && j != wucha_label[2] && j != wucha_label[3] && j != wucha_label[4] &&j != fra_label[0] && j != fra_label[1] && (float)Inimg_s[j]/Inimg_num[j] > average_frat)
			kuangtu(gray, j, Inimg_imgstats);
	}

}
//��ǩ���� Inimg_labels
//���ξ��� Inimg_imgstats
//���ľ��� Inimg_centriods
//�Ҷ�ͼ�� imagedata_gray
void kuangtu(Mat gray, int ID, Mat Inimg_imgstats) {
	int left_x =  Inimg_imgstats.at<int>(ID, CC_STAT_LEFT);
	int top_y =  Inimg_imgstats.at<int>(ID, CC_STAT_TOP);
	int height = Inimg_imgstats.at<int>(ID, CC_STAT_HEIGHT);
	int width = Inimg_imgstats.at<int>(ID, CC_STAT_WIDTH);
	//cout << "gao" << Inimg_labels.rows << "chang" << Inimg_labels.cols << endl;
	rectangle(gray, Rect(left_x, top_y, width, height), Scalar(255, 0, 0));
//	rectangle(a, Rect(center_x-height/2, center_y-width/2, height,width), Scalar(255,0,0));
	imshow("kuangtu", gray);

}



//���㴰�ڵķ���ά�����������
void Fractal(Mat dst, int epsilon, float &s, float &d, float &e) {
	//������ά����
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
		//����
		for (int i = 0; i < dst.rows; i++) {
			int MAX_row = 0, MIN_row=300;
			for (int j = 0; j < dst.cols; j++) {
				if (*(dst_data + i*dst.cols + j) > MAX_row)
					MAX_row = *(dst_data + i*dst.cols + j);
				if (*(dst_data + i*dst.cols + j) < MIN_row)
					MIN_row = *(dst_data + i*dst.cols + j);
			}
			if (MAX_a < MAX_row)
				MAX_a = MAX_row;
			if (MIN_a > MIN_row)
				MIN_a = MIN_row;
		}
		//int k = k;
		N[0][k] = min((255 - MAX_a) / (k + 1), MIN_a / (k + 1));

		//����
		for (int i = 0; i < dst.cols; i++) {
			int MAX_col = 0, MIN_col = 300;
			for (int j = 0; j < dst.rows; j++) {
				if (*(dst_data + j*dst.cols + i) > MAX_col)
					MAX_col = *(dst_data + j*dst.cols + i);
				if (*(dst_data + j*dst.cols + i) < MIN_col)
					MIN_col = *(dst_data + j*dst.cols + i);
			}
			if (MAX_b < MAX_col)
				MAX_b = MAX_col;
			if (MIN_b > MIN_col)
				MIN_b = MIN_col;
		}
		N[1][k] = min((255 - MAX_b) / (k + 1), MIN_b / (k + 1));

		N[2][k] = min(N[0][k], N[1][k]);

		N[3][k] = log(k + 1);

		N[4][k] = log(N[2][k]);
		//cout << N[3][k] <<"\t"<< N[4][k] << endl;
		data_x[k] = N[3][k]+1;
		data_y[k] = N[4][k]+1;
	}
	//N[2]ÿ��epsilon��Ӧ��N[epsilon];N[3]--->log x;N[4]----->logN[epsilon];
	//������Щ������������S,D,E����
	float a, b;
	
	//cout << data_x[0]<<data_x[1]<<data_x[2]<<data_x[3] << endl;
	//������ֱ��
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
	d = a + 1;// +b / epsilon;
	e = 0.0;
	s = b;
	for (int i = 0; i < epsilon; i++) {
		e += abs(N[4][i]-(a)*N[3][i]);
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

	// ����б��a�ͽؾ�b
	float temp = 0;
	if (temp = (data_n*A - B*B))// �жϷ�ĸ��Ϊ0
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
//�˻���
double MutilSum(vector<double> Vx, vector<double> Vy, int n)
{
	double dMultiSum = 0;
	for (int i = 0; i<n; i++)
	{
		dMultiSum += Vx[i] * Vy[i];
	}
	return dMultiSum;
}
//ex�η���
double RelatePow(vector<double> Vx, int n, int ex)
{
	double ReSum = 0;
	for (int i = 0; i<n; i++)
	{
		ReSum += pow(Vx[i], ex);
	}
	return ReSum;
}
//x��ex�η���y�ĳ˻����ۼ�
double RelateMutiXY(vector<double> Vx, vector<double> Vy, int n, int ex)
{
	double dReMultiSum = 0;
	for (int i = 0; i<n; i++)
	{
		dReMultiSum += pow(Vx[i], ex)*Vy[i];
	}
	return dReMultiSum;
}
//���㷽������������
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
//��ⷽ��
void CalEquation(int exp, double coefficient[])
{
	for (int k = 1; k<exp; k++) //��Ԫ����
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
	for (int l = exp - 1; l >= 1; l--)   //�ش����
		coefficient[l] = (Em[l][exp + 1] - F(coefficient, l + 1, exp)) / Em[l][l];
}
//��CalEquation��������
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

	//��ʼ��δ֪��С�Ķ�ά����
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
	//Mat dst=Mat(img.size(),CV_8UC3,Scalar(255,255,255));//uchar����תMat
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
	//*dst.data = Img_extension[i][j];//uchar����תMat
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
