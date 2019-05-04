#pragma once
#pragma once

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>

const int MAX_CLUSTERS = 5;
Vec3b colorTab[] =
{
	Vec3b(0, 0, 255),
	Vec3b(0, 255, 0),
	Vec3b(255, 100, 100),
	Vec3b(255, 0, 255),
	Vec3b(0, 255, 255)
};