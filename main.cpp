#include <iostream>
#include "showpic.h"
#include <string>
#include <set>
#include <fstream>
void print_sj(const std::vector<Tx*> &tx,const Point *pp,const std::vector<Scalar> &scalar,const std::vector<F_base*> &fbase);
int  output_sj(int low,int up){
    srand((unsigned )time(NULL));
    int result = rand() % (up - low + 1) + low;
    return result;
}
Mat fsbh(Mat &mat,const std::vector<F_base*> &fbase){
        int index = output_sj(0,fbase.size() -1 );
        Mat result = fbase[index] -> bh(mat);
//        std::cout << "fangshe bh" << index << std::endl;
        return result;

}
void  gaussnoise(Mat &mat){
    Mat noise = Mat::zeros(mat.rows,mat.cols,mat.type());
    RNG rng;
    rng.fill(noise,RNG::NORMAL,15,5);
    mat = mat + noise;
//    std::cout << noise <<std::endl;
}
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
    std::vector<F_base*> fbase;
    fbase.push_back(new Py(20,20));
    fbase.push_back(new Py(-20,15));
    fbase.push_back(new Sf(1.5,1));
    fbase.push_back(new Sf(0.5,1));
    fbase.push_back(new Sf(1,0.5));
    fbase.push_back(new Sf(1,1.5));
    fbase.push_back(new Jy());
    fbase.push_back(new Jx());
    fbase.push_back(new Fs(90,0.7));
    fbase.push_back(new Fs(-30,1.2));
    fbase.push_back(new Fs(-60,1));
    fbase.push_back(new Fs(-180,0.9));

    Point pp[] = {Point(75,75),Point(225,75),Point(225,225),Point(75,225),Point(150,75),Point(150,225)};
    std::vector<Scalar> scalar;
    for(int i = 0;i < 4;i++){
        scalar.push_back(Scalar(125 + 35 * i));
    }

    print_sj(tx,pp,scalar,fbase);


//    waitKey();
   for(auto tmp : tx)
        delete  tmp;
    for(auto tmp : fbase)
        delete tmp;
    return 0;
}

void print_sj(const std::vector<Tx*> &tx,const Point *pp,const std::vector<Scalar> &scalar,const std::vector<F_base*> &fbase){
    std::ofstream  outfile;
    outfile.open("out_1.txt");
    Bq bq;

    int index(0);
    int init(0);
    std::set<int> counter;
    for(int n = 0;n < 10000;n++) {
        Mat  pic = Mat(300,300,CV_8UC1,Scalar(0));
        bq.bq["nb"].push_back(n + 1);  //标签：number
        for (int i = 4; i < 6; i++) {

            while (counter.find(index = output_sj(0, 6)) != counter.end()) {
            }
            tx[index]->show(pic, pp[i], scalar[init++]);
            counter.insert(index);
            bq.bq["xh"].push_back(index+1); //标签： xh
            bq.bq["hd"].push_back(scalar[init - 1].val[0]);
            bq.bq["center"].push_back(pp[i].x);
            bq.bq["center"].push_back(pp[i].y);

            if (index == 6) {
                index = 7;
                tx[index]->show(pic, pp[i], scalar[init++]);
                counter.insert(7);
            } else if (index == 4) {
                index = 7;
                tx[index]->show(pic, pp[i], scalar[init++]);
                counter.insert(7);
            } else {
                int tmp = index;
                while (counter.find(index = output_sj(tmp + 1,7)) != counter.end()) {
                }
                tx[index]->show(pic, pp[i], scalar[init++]);
                counter.insert(index);
            }
            bq.bq["xh"].push_back(index+1); //标签： xh
            bq.bq["hd"].push_back(scalar[init - 1].val[0]);
            bq.bq["center"].push_back(pp[i].x);
            bq.bq["center"].push_back(pp[i].y);
        }
        init = 0;
        counter.clear();
        std::string ouputname = "D:\\pic\\out1\\" + std::to_string(n + 1) + ".jpg"; //outpu 路径
        Mat fs_mat = fsbh(pic,fbase);
        bq.push_mat(fs_mat);  //标签： 仿射矩阵
        gaussnoise(pic);  //高斯噪声
        imwrite(ouputname, pic);
        bq.convert_mat(fs_mat);//转换center根据仿射矩阵
        outfile << bq;
        bq.clearall();
    }
    outfile.close();
}
