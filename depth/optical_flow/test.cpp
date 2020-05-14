#include<iostream>
#include<opencv2/opencv.hpp>
#include<optical_flow.hpp>
#include<cmath>
#include<chrono>
using namespace std;
using namespace cv;

int main(){
	// int index;
	// cin >> index;
	// VideoCapture cam(index);
	// Mat prev;
	// cam.read(prev);
	// while(true){
	// 	Mat next, U, V;
	// 	cam.read(next);
	// 	//next = imread("../test_img.jpg", 0);
	// 	//cout << "check 1"<< endl;
	// 	namedWindow("test");
	// 	imshow("test", next);
	// 	//waitKey(0);
	// 	huroiitk::flowLK(prev, next, U, V);
	// 	Mat mag(Size(U.cols, U.rows), CV_64F, Scalar(0));
	// 	for (int i=0; i<U.rows; i++){
	// 		double* magi = mag.ptr<double>(i);
	// 		const double* Ui = U.ptr<double>(i);
	// 		const double* Vi = V.ptr<double>(i);

	// 		for (int j=0; j<U.cols; j++){
	// 			magi[j] = sqrt(Ui[j]*Ui[j] + Vi[j]*Vi[j]);
	// 		}
	// 	}

	// 	Mat norm(Size(mag.cols, mag.rows), CV_8U, Scalar(0));
	// 	normalize(mag, norm, 0, 255, NORM_MINMAX, CV_8U);
	// 	namedWindow("result");
	// 	imshow("result", norm);

	// 	if (waitKey(5) >= 0) break;
	// }

	Mat prev, next, tprev, tnext, U, V;
	prev = imread("../IMG_5438.JPG", 0);
	next = imread("../IMG_5437.JPG", 0);
	// cout << prev.rows << endl;
	huroiitk::shrink(prev, tprev);
	huroiitk::shrink(tprev, prev);
	huroiitk::shrink(prev, tprev);
	// huroiitk::shrink(tprev, prev);
	// huroiitk::shrink(prev, tprev);
	// tprev = prev;
	huroiitk::shrink(next, tnext);
	huroiitk::shrink(tnext, next);
	huroiitk::shrink(next, tnext);
	// huroiitk::shrink(tnext, next);
	// huroiitk::shrink(next, tnext);
	// tnext = next;
	double min = 10000000, max = -1;
	
	auto start = chrono::high_resolution_clock::now(); 
	huroiitk::flowLK(tprev, tnext, U, V);
	auto end = chrono::high_resolution_clock::now();
	double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
	time_taken *= 1e-9;
	cout << time_taken << setprecision(9) << endl;

	Mat mag(Size(U.cols, U.rows), CV_64F, Scalar(0));
	for (int i=0; i<U.rows; i++){
		double* magi = mag.ptr<double>(i);
		const double* Ui = U.ptr<double>(i);
		const double* Vi = V.ptr<double>(i);

		for (int j=0; j<U.cols; j++){
			magi[j] = sqrt(Ui[j]*Ui[j] + Vi[j]*Vi[j]);
			if (magi[j] > max) max = magi[j];
			if (magi[j] < min) min = magi[j];
		}
	}
	cout << min << " " << max << endl;
	Mat tnorm(Size(mag.cols, mag.rows), CV_8U, Scalar(0));
	normalize(mag, tnorm, 0, 255, NORM_MINMAX, CV_8U);
	Mat norm;
	// huroiitk::expand(tnorm, norm);
	// huroiitk::expand(norm, tnorm);
	namedWindow("prev");
	imshow("prev", tprev);
	namedWindow("next");
	imshow("next", tnext);
	namedWindow("result");
	imshow("result", tnorm);
	waitKey(0);

	return 0;
}
