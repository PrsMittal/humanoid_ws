#pragma once
#include<opencv2/opencv.hpp>
namespace huroiitk{
	const float gx[5] = {0.06136, 0.24477, 0.38774, 0.24477, 0.06136};
	
	void shrink(const cv::Mat& src, cv::Mat& dest);
	void expand(const cv::Mat& src, cv::Mat& dest);
	void flowLK(const cv::Mat& prev, const cv::Mat& next, cv::Mat& U, cv::Mat& V);
}

