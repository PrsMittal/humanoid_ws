#pragma once
#include<Eigen/Dense>
namespace huroiitk{

    class KalmanFilter{
        public: 
            KalmanFilter(const Eigen::VectorXd& init): state(init), F();
            Eigen::VectorXd predict(const Eigen::VectorXd control, 
                                    const Eigen::MatrixXd F, 
                                    const Eigen::MatrixXd H, 
                                    const Eigen::MatrixXd B,
                                    const Eigen::MatrixXd K
                                    );
        
        protected:
            void update(const Eigen::VectorXd );

            Eigen::VectorXd state;
            Eigen::MatrixXd P;
            Eigen::MatrixXd F;
            Eigen::MatrixXd K;
            Eigen::MatrixXd H;
            Eigen::MatrixXd Q;
    };

}