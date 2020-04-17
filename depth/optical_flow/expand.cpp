#include<optical_flow.hpp>
#include<opencv2/opencv.hpp>
using namespace huroiitk;

void expand(const cv::Mat& src, cv::Mat& dest){
	//assert dest is half the dimensions of src, or uninitailised. 
	cv::Mat tempx(Size(2*src.cols, src.rows), cv::CV_32F, cv::Scalar(0));
	cv::Mat tdest(Size(2*src.rows, 2*src.cols), cv::CV_8U, cv::Scalar(0));
	#pragma omp parallel for
	for (int i=0; i<tempx.rows; i++){
		const uint8_t* srci = src.ptr<uint8_t>(i);
		float* desti = tempx.ptr<float>(i);
		#pragma omp parallel for
		for (int j=1; j<tempx.cols-1; j++){
			if (j%2 == 0){
				desti[j] += gx[0]*srci[(j-2)/2]; 
				desti[j] += gx[2]*srci[j/2];
				desti[j] += gx[4]*srci[(j+2)/2];
			}
			else {
				desti[j] += gx[1]*srci[(j-1)/2];
				desti[j] += gx[3]*srci[(j+1)/2];
			}
		}
	}
	
	cv::Mat tsrc = tempx.t();
	//delete tempx;
	#pragma omp parallel for
	for (int i=0; i<tdest.rows; i++){
                const float* srci = tsrc.ptr<float>(i);
                uint8_t* desti = tdest.ptr<uint8_t>(i);
                #pragma omp parallel for
		for (int j=1; j<tdest.cols-1; j++){
			if (j%2 == 0){
                        	desti[j] += static_cast<uint8_t>(gx[0]*srci[j/2-1]);
                        	desti[j] += static_cast<uint8_t>(gx[2]*srci[j/2]);
                       		desti[j] += static_cast<uint8_t>(gx[4]*srci[j/2+1]);
                        }
			else {
				desti[j] += static_cast<uint8_t>(gx[1]*srci[(j-1)/2]);
				desti[j] += static_cast<uint8_t>(gx[3]*srci[(j+1)/2]);
			}
                }
        }
	dest = tdest.t();
	
	return;
}
