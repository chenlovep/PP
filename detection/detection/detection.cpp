// Detection.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


/*
int main()
{
unsigned char *img;
FILE *fp1;
fp1 = fopen("C:\\Users\\44175\\Desktop\\分形目标检测\\picture\\11.jpg", "rb");

if (fp1 == NULL)
{
printf("file not exist!\n");
return;
}
fread(img, 1, 960 * 540, fp1);
fclose(fp1);

//RGB2Lab(img, labimg);
return 0;
}
*/

void rgb2lab(Mat &img, Mat &lab);
int FastBlanket(unsigned char *Inimg, int height, int width, unsigned char *imagedata_gray);
//void convert_black(Mat &label_gray, unsigned char *imagedata);
void show_segment_kmeans(Mat &pic, int k, Mat &label);
//double Regionfractal(Mat &img);


int main()
{
	
	const int MAX_CLUSTERS = 7;
	Vec3b colorTab[] =
	{
		Vec3b(255, 0, 0),
		Vec3b(0, 0, 255),
		Vec3b(0, 255, 0),
		Vec3b(255, 100, 100),
		Vec3b(255, 0, 255),
		Vec3b(0, 255, 255),
		Vec3b(255, 255, 0)
	};

	Mat data, labels, pic_gray;
	Mat pic = imread("1.jpg");
	cvtColor(pic,pic_gray, CV_BGR2GRAY);
	

	uchar* imagedata_gray = pic_gray.data;
	//Mat pic_ = pic;
	Mat lab = Mat(pic.rows, pic.cols, CV_8UC3);
	waitKey(0);
	imshow("原图", pic);
	rgb2lab(pic, lab);
	//imshow("pic", pic);
	imshow("labimg", lab);	

	//提取蓝色通道的数据  
	//cout << Lab.rows << Lab.cols << Lab.channels << endl;
	//printf("rows: %d, cols: %d, channels:%d", Lab.rows, Lab.cols, Lab.channels);
	int i;
	for (i = 0; i < pic.rows; i++)     //像素点线性排列
	{
		for (int j = 0; j < pic.cols; j++)
		{
			Vec3b pix = pic.at<Vec3b>(i, j);
			//RGB2Lab(pix[0], pix[1], pix[2], (float *)pix_lab[0], (float *)pix_lab[1], (float *)pix_lab[2]);
			Vec3b point = pic.at<Vec3b>(i, j);
			Mat tmp = (Mat_<float>(1, 3) << point[0], point[1], point[2]);
			data.push_back(tmp);
		}
	}
	//根据浏览图片，确定分类类别数量
	kmeans(data, MAX_CLUSTERS, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0), 3, KMEANS_RANDOM_CENTERS);

	int n = 0;
	//显示聚类结果，不同的类别用不同的颜色显示
	for (int i = 0; i < pic.rows; i++)
	{
		for (int j = 0; j < pic.cols; j++)
		{
			int clusterIdx = labels.at<int>(n);
			pic.at<Vec3b>(i, j) = colorTab[clusterIdx];
			n++;
		}
	}
	imshow("K-means聚类算法", pic);
	//##############################
	//判别一
	int k = 2;
	//##############################
	show_segment_kmeans(pic, k, labels);
	Mat label_gray;
	imshow("k-means聚类2算法", pic);
	cvtColor(pic, label_gray, CV_BGR2GRAY);
	//convert_black(label_gray, imagedata);
	uchar* imagedata = label_gray.data;
	for (int i = 0; i < label_gray.rows; i++) {
		for (int j = 0; j < label_gray.cols; j++) {
			if (*(imagedata + i*label_gray.cols + j) >= 250) {
				*(imagedata + i*label_gray.cols + j) = 0;
			}
			else
				*(imagedata + i*label_gray.cols + j) = 255;
		}
	}
	imshow("去除K-means聚类算法", label_gray);
	//连通区域处理
	Mat imglabels, imgstats, imgcentriods;
	//label_gray原图像，imglabels含有类别的图像
	int imglabelnum = connectedComponentsWithStats(label_gray, imglabels, imgstats, imgcentriods);
	cout << "imglabel:"<<imglabelnum << endl;
	int labelnum = imgcentriods.rows;
	//printf("连通区域个数%d", imglabelnum);
	for (int i = 0; i < label_gray.rows; i++) {
		for (int j = 0; j < label_gray.cols; j++) {
			//CC_STAT_AREA为面积，
			//CC_STAT_HEIGHT为高
			//CC_STAT_WIDTH为宽
			if (*(imagedata + i*label_gray.cols + j) != 0 && imglabels.at<int>(i, j) != 0 && imgstats.at<int>(imglabels.at<int>(i, j), CC_STAT_AREA) <= label_gray.rows*label_gray.cols / (25) && imgstats.at<int>(imglabels.at<int>(i, j), CC_STAT_AREA) >= label_gray.rows*label_gray.cols / (750))
				*(imagedata + i*label_gray.cols + j) = 255;
			else
				*(imagedata + i*label_gray.cols + j) = 0;
		}
	}

	imshow("连通域消除算法", label_gray);
	int template_size = 5;
	//获得图像的分型维数；分型误差
	
	
	//对剩余灰度图像进行分型维数分形误差
	FastBlanket(imagedata, label_gray.rows, label_gray.cols, imagedata_gray);
	//Regionfractal(pic);
	

	waitKey(0);
	return 0;
}


void kuangtu(Mat img, unsigned char *Inimg, int num1, int nums2)
{
	int row = img.rows;
	int col = img.cols;
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if (*(Inimg + i*row + j) != 0)
				*(Inimg + i*row + j) = 255;
		}
	}

}



typedef struct QNode {
	int data;
	struct QNode *next;
}QNode;

typedef struct Queue {
	struct QNode* first;
	struct QNode* last;
}Queue;

void PushQueue(Queue *queue, int data) {
	QNode *p = NULL;
	p = (QNode*)malloc(sizeof(QNode));
	p->data = data;
	if (queue->first == NULL) {
		queue->first = p;
		queue->last = p;
		p->next = NULL;
	}
	else {
		p->next = NULL;
		queue->last->next = p;
		queue->last = p;
	}
}


//https://blog.csdn.net/u013369277/article/details/50740608
//连通区域标记
int PopQueue(Queue *queue) {
	QNode *p = NULL;
	int data;
	if (queue->first == NULL) {
		return -1;
	}
	p = queue->first;
	data = p->data;
	if (queue->first->next == NULL) {
		queue->first = NULL;
		queue->last = NULL;
	}
	else {
		queue->first = p->next;
	}
	free(p);
	return data;
}

static int NeighborDirection[8][2] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };

void SearchNeighbor(unsigned char *bitmap, int width, int height, int *labelmap,
	int labelIndex, int pixelIndex, Queue *queue) {
	int searchIndex, i, length;
	labelmap[pixelIndex] = labelIndex;
	length = width * height;
	for (i = 0; i < 8; i++) {
		searchIndex = pixelIndex + NeighborDirection[i][0] * width + NeighborDirection[i][1];
		if (searchIndex > 0 && searchIndex < length &&
			bitmap[searchIndex] == 255 && labelmap[searchIndex] == 0) {
			labelmap[searchIndex] = labelIndex;
			PushQueue(queue, searchIndex);
		}
	}
}

int ConnectedComponentLabeling(unsigned char *bitmap, int width, int height, int *labelmap) {
	int cx, cy, index, popIndex, labelIndex = 0;
	Queue *queue = NULL;
	queue = (Queue*)malloc(sizeof(Queue));
	queue->first = NULL;
	queue->last = NULL;
	memset(labelmap, 0, width * height);
	for (cy = 1; cy < height - 1; cy++) {
		for (cx = 1; cx < width - 1; cx++) {
			index = cy * width + cx;
			if (bitmap[index] == 255 && labelmap[index] == 0) {
				labelIndex++;
				SearchNeighbor(bitmap, width, height, labelmap, labelIndex, index, queue);

				popIndex = PopQueue(queue);
				while (popIndex > -1) {
					SearchNeighbor(bitmap, width, height, labelmap, labelIndex, popIndex, queue);
					popIndex = PopQueue(queue);
				}
			}
		}
	}
	free(queue);
	return labelIndex;
}