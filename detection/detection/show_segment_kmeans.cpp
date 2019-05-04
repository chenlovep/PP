#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const int MAX_CLUSTERS = 7;
Vec3b colorTab[] =
{
	Vec3b(255, 0, 0),
	Vec3b(0, 0, 255),
	Vec3b(0, 255, 0),
	Vec3b(255, 100, 100),
	Vec3b(255, 0, 255),
	Vec3b(0, 255, 255),
	Vec3b(0, 0, 0)
};
void show_segment_kmeans(Mat &pic, int k, Mat &label) {
	int num_of_segment[MAX_CLUSTERS] = { 0 };
	for (int i = 0; i < pic.rows; i++) {
		for (int j = 0; j < pic.cols; j++) {
			Vec3b pix = pic.at<Vec3b>(i, j);
			for (int k = 0; k < MAX_CLUSTERS; k++) {
				if (pix == colorTab[k]) {
					num_of_segment[k] += 1;
				}
			}
		}
	}
	//for (int i = 0; i < MAX_CLUSTERS; i++) {
	//	printf("%d\n", num_of_segment[i]);
	//}
	int max_label[MAX_CLUSTERS] = { -1 }, m_label;
	for (int i = 0; i < k; i++) {
		int MAX = 0;
		for (int j = 0; j < MAX_CLUSTERS; j++) {
			if (MAX < num_of_segment[j]) {
				MAX = num_of_segment[j];
				m_label = j;
			}
		}
		max_label[i] = m_label;
		for (int i = 0; i < MAX_CLUSTERS - 1; i++) {
			if (i == m_label) {
				num_of_segment[i] = 0;
			}
		}
	}
	cout << max_label[0] << max_label[1];
	int n = 0, clusterIdx, flag;
	for (int i = 0; i < pic.rows; i++) {
		for (int j = 0; j < pic.cols; j++) {
			int clusterIdx = label.at<int>(n);
			flag = 1;
			//cout << "第" << i << "行" << "第" << j << "列" << "类别为:" << clusterIdx << "n为:"<<n<<"cl_ID:"<<clusterIdx<<endl;
			for (int m = 0; m < k; m++) {
				if (clusterIdx == max_label[m]) {
					flag = 0;
					pic.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
				}
			}
			if (flag != 0)
				pic.at<Vec3b>(i, j) = colorTab[clusterIdx];
			n++;
		}
	}
}

/*
void convert_black(Mat &label_gray, unsigned char &imagedata){
imagedata = label_gray.data;
for (int i = 0; i < label_gray.rows;i++) {
uchar *data = label_gray.ptr<uchar>(i);
for (int j = 0; j < label_gray.cols;j++) {
if (int(data[j]) == 255) {
*(imagedata + j*label_gray.cols + i) = 0;
}
else
*(imagedata + j*label_gray.cols + i) = 255;
}
}
}
*/