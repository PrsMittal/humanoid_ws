#pragma once
#include<opencv2/opencv.hpp>
namespace huroiitk{
	
	void shrink(const cv::Mat& src, cv::Mat& dest);
	void expand(const cv::Mat& src, cv::Mat& dest);
}

