#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>
using namespace std;
using namespace cv;

int main(){
	for(int i=0; i<200; i++){
		string path = "../focal_dataset_blurred/" + to_string(i) + ".jpg";
		string name = "image";
		Mat im = imread(path, 0);
		Mat dst1;
		Laplacian(im, dst1, CV_16S, 3);
		convertScaleAbs(dst1, im);
		namedWindow(name);
		imshow(name, im);
		waitKey(0);
	}

	return 0;
}	
