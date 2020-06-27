#include <iostream>
#include "showpic.h"
#include <string>
int main() {
    std::vector<Tx*> tx;
//    Mat  pic = Mat(300,300,CV_8UC1,Scalar(0));
    tx.push_back(new Square);
    tx.push_back(new Circle);
    tx.push_back(new Wbx);
    tx.push_back(new Wjx);
    tx.push_back(new Sx);
    tx.push_back(new Halfcircle);
    tx.push_back(new Ttx);
    tx.push_back(new Triangle);
    Point pp[] = {Point(75,75),Point(225,75),Point(225,225),Point(75,225),Point(150,75),Point(150,225)};
    std::vector<Scalar> scalar;
    for(int i = 0;i < 8;i++){
        scalar.push_back(Scalar(125 + 10 * i));
    }
    srand((unsigned )time(NULL));
    int index(0);
    for(int i = 0;i < tx.size();i++){
        Mat  pic = Mat(300,300,CV_8UC1,Scalar(0));
        tx[i]->show(pic,pp[4],scalar[i]);
        std::string  ouputname = std::to_string(i + 1) + ".jpg";
        imwrite(ouputname,pic);
    }

//    waitKey();
    for(auto tmp : tx){
        delete  tmp;
    }
    return 0;
}
