#include <iostream>
#include <Eigen/Dense>
#include <map>


float calculate_mean(Eigen::MatrixXd input){
    float sum = 0.f;
    for (int val = 0 ; val < 100; val++){
        float v = input(val,0);
        sum += v;
    }
    return sum / 100.f;

};

float calculate_sum_squared_difference(Eigen::MatrixXd input, float mean){
    float sum_sqd = 0.f;
    for (int val = 0 ; val < 100; val++){
        float v = input(val,0);
        float sqd = (mean - v) * (mean - v);
        sum_sqd += sqd;
    }
    return sum_sqd ;
};

void print_zs(std::map<std::string,double> z_score){
    std::map<std::string,double> _0_1;
    std::map<std::string,double> _1_2;
    std::map<std::string,double> _2_3;
    std::map<std::string,double> _3p;
    double anomaly_threshold = 1.45;

    for(std::map<std::string,double>::iterator x = z_score.begin(); x != z_score.end(); ++x){
        if (x->second <= 1){
            _0_1[x->first] = x->second;
        }
        else if (x->second > 1 && x->second <=2){
            _1_2[x->first] = x->second;
        }
        else if(x->second > 2 && x->second <= 3){
            _2_3[x->first] = x->second;
        } else{
            _3p[x->first] = x->second;
        }
    }

    std::cout << "number of values <= 1 standard dev from mean = " << _0_1.size() << std::endl;
    std::cout << "number of values between 1-2 standard dev from mean = " << _1_2.size() << std::endl;
    std::cout << "number of values between 2-3 standard dev from mean = " << _2_3.size() << std::endl;
    std::cout << "number of values between 3+ standard dev from mean = " << _3p.size() << std::endl;
    std::cout << "\n\n";
    
    for (auto itt = _1_2.begin(); itt != _1_2.end(); itt++){
        if (itt->second > anomaly_threshold){
            std::cout << "data row :" << itt->first << " is an anomaly" << std::endl;
        }
    }
}

int main(){

    Eigen::MatrixXd data = Eigen::MatrixXd::Random(100,1);
    std::map<std::string,double> z_score; 
    double mean = calculate_mean(data);
    double variance = calculate_sum_squared_difference(data,mean) / (data.rows() - 1);
    double standard_dev = std::sqrt(variance);
    

    for (int r = 0; r < data.rows(); r++){
        double entry = data(r,0);
        double z = (entry - mean) / standard_dev;
        std::cout << std::to_string(r) + ": " + std::to_string(entry) << " = "  << z << std::endl;
        z_score[std::to_string(r) + ": " + std::to_string(entry)] = z;
    }

    std::cout << "\n\n";
    print_zs(z_score);

    



    





    return 0;
}