#include<optical_flow.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<thread>
using namespace std;
namespace huroiitk{
	void flowLK(const cv::Mat& prev, const cv::Mat& next, cv::Mat& U, cv::Mat& V){
		//assert dims = 2
		cv::Mat k_x = (cv::Mat_<double>(2, 2) << -1, 1, -1, 1);
		cv::Mat fx, fy, ft, fxfy, fx2, fy2, fxft, fyft;
		cv::Mat Sfx2, Sfy2, Sfxfy, Sfxft, Sfyft;
		cv::Mat fx_1, fx_2, fy_1, fy_2;
		cv::Mat tprev, tnext;
		prev.convertTo(tprev, CV_64F);
		next.convertTo(tnext, CV_64F);
		ft = tnext - tprev;
		
		cv::filter2D(prev, fx_1, CV_64F, k_x);
		cv::filter2D(next, fx_2, CV_64F, k_x);
		cv::filter2D(prev, fy_1, CV_64F, k_x.t());
		cv::filter2D(next, fy_2, CV_64F, k_x.t());
		fx = (fx_1 + fx_2)/2;
		fy = (fy_1 + fy_2)/2;

		fxft = fx.mul(ft);
		fyft = fy.mul(ft);
		fx2 = fx.mul(fx);
		fy2 = fy.mul(fy);
		fxfy = fx.mul(fy);		
		
		float sig_ = 0.707;
		cv::GaussianBlur(fxft, Sfxft, cv::Size(3,3), sig_);
		cv::GaussianBlur(fyft, Sfyft, cv::Size(3,3), sig_);
		cv::GaussianBlur(fx2, Sfx2, cv::Size(3,3), sig_);
		cv::GaussianBlur(fy2, Sfy2, cv::Size(3,3), sig_);
		cv::GaussianBlur(fxfy, Sfxfy, cv::Size(3,3), sig_);

		cv::Mat destu(cv::Size(prev.cols, prev.rows), CV_64F, cv::Scalar(0));
		cv::Mat destv(cv::Size(prev.cols, prev.rows), CV_64F, cv::Scalar(0));
		
		#pragma omp parallel for
		for (int i=0; i<prev.rows; i++){
			const double* Sfx2i = Sfx2.ptr<double>(i);
			const double* Sfy2i = Sfy2.ptr<double>(i);
			const double* Sfxfyi = Sfxfy.ptr<double>(i);
			const double* Sfxfti = Sfxft.ptr<double>(i);
			const double* Sfyfti = Sfyft.ptr<double>(i);
			double* Ui = destu.ptr<double>(i);
			double* Vi = destv.ptr<double>(i);
			
			#pragma omp parallel for
			for (int j=0; j<prev.cols; j++){
				double den_ = (Sfy2i[j]*Sfx2i[j] - Sfxfyi[j]*Sfxfyi[j]) + 1e-9;
				cv::Mat Ainv = (cv::Mat_<double>(2, 2) << Sfy2i[j]/den_, -Sfxfyi[j]/den_, -Sfxfyi[j]/den_, Sfx2i[j]/den_);
				cv::Mat B = (cv::Mat_<double>(2, 1) << -Sfxfti[j], -Sfyfti[j]);
				cv::Mat X;
				X = Ainv*B;
				Ui[j] = (X.ptr<double>(0))[0];
				Vi[j] = (X.ptr<double>(1))[0];
			}
		}

		U = destu;
		V = destv;
		return;
	}
}