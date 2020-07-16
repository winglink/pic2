#include <iostream>
#include "showpic.h"
#include <string>
#include <set>
#include <fstream>
#include <thread>
const int N = 10000;
const std::string out_txt1 = "out_11.txt";
const std::string out_txt2 = "out_12.txt";
const std::string out_dri1= "D:\\pic2\\out11\\";
const std::string out_dri2= "D:\\pic2\\out12\\";
void print_zh(const std::vector<Tx*> &tx,const std::vector<Point> &pp,const std::vector<Scalar> &scalar,const std::vector<F_base*> &fbase);
void print_sj(const std::vector<Tx*> &tx,const std::vector<Point> &pp,const std::vector<Scalar> &scalar,const std::vector<F_base*> &fbase);
void print_all(const std::vector<Tx*> &tx,const std::vector<Point> &pp,const std::vector<Scalar> &scalar,const std::vector<F_base*> &fbase);
void pj(Mat &mat){
    Mat zymat = Mat::zeros(mat.rows,10,mat.type());
    Mat shmat = Mat::zeros(10,mat.cols + 20,mat.type());
    hconcat(mat,zymat,mat);
    hconcat(zymat,mat,mat);
    vconcat(shmat,mat,mat);
    vconcat(mat,shmat,mat);
}
Mat fsbh(Mat &mat,const std::vector<F_base*> &fbase,int n){
//        int index = output_sj(0,fbase.size() -1 );
        int index = n % (fbase.size());
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
    fbase.push_back(new Py(3,3));
    fbase.push_back(new Py(-3,-3));
    fbase.push_back(new Sf(0.6,1));
    fbase.push_back(new Sf(1,0.6));
    fbase.push_back(new Jy());
    fbase.push_back(new Jx());
    fbase.push_back(new Fs(-10,0.7));
    fbase.push_back(new Fs(5,0.8));
    fbase.push_back(new Fs(90,0.8));
//    fbase.push_back(new Fs(10,0.7));

    std::vector<Point> pp = {Point(75,75),Point(225,75),Point(225,225),Point(75,225),Point(150,75),Point(150,225)};
    std::vector<Scalar> scalar;
    for(int i = 0;i < 4;i++){
        scalar.push_back(Scalar(125 + 35 * i));
    }
    std::thread t(print_sj,std::ref(tx),std::ref(pp),std::ref(scalar),std::ref(fbase));
//  print_sj(tx,pp,scalar,fbase);
    print_zh(tx,pp,scalar,fbase);
    t.join();
//    print_all(tx,pp,scalar,fbase);
//    waitKey();
   for(auto tmp : tx)
        delete  tmp;
    for(auto tmp : fbase)
        delete tmp;
    return 0;
}

void print_sj(const std::vector<Tx*> &tx,const std::vector<Point> &pp,const std::vector<Scalar> &scalar,const std::vector<F_base*> &fbase){
    std::ofstream  outfile;
    outfile.open(out_txt1);
    Bq bq;

    int index(0);
    int init(0);
    std::set<int> counter;
    for(int n = 0;n < N;n++) {
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
        std::string ouputname = out_dri1 + std::to_string(n + 1) + ".jpg"; //outpu 路径
        Mat fs_mat = fsbh(pic,fbase,n);
        bq.push_mat(fs_mat);  //标签： 仿射矩阵
        gaussnoise(pic);  //高斯噪声
        pj(pic);  //补四周10
        imwrite(ouputname, pic);
        bq.convert_mat(fs_mat);//转换center根据仿射矩阵
        outfile << bq;
        bq.clearall();
    }
    outfile.close();
}
void print_zh(const std::vector<Tx*> &tx,const std::vector<Point> &pp,const std::vector<Scalar> &scalar,const std::vector<F_base*> &fbase){
    std::ofstream  outfile;
    std::vector<Point> point_tmp(pp);
    for(int i = 0 ;i < point_tmp.size();i++){
        point_tmp[i] = pp[i];
//        std::cout << "**" << point_tmp[i] << std::endl;
    }
    outfile.open(out_txt2);
    Bq bq;

    int index(0);
    int init(0);
    std::set<int> counter;
    for(int n = 0;n < N;n++) {
        Mat  pic = Mat(300,300,CV_8UC1,Scalar(0));
        bq.bq["nb"].push_back(n + 1);  //标签：number
        point_tmp = pp;
        for (int i = 0; i < 4; i++) {

            while (counter.find(index = output_sj(0, 7)) != counter.end()) {
            }
            tx[index]->show_py(pic, point_tmp[i], scalar[init++]);
            counter.insert(index);
            bq.bq["xh"].push_back(index + 1); //标签： xh
            bq.bq["hd"].push_back(scalar[init - 1].val[0]);
            bq.bq["center"].push_back(point_tmp[i].x);
            bq.bq["center"].push_back(point_tmp[i].y);
        }

        init = 0;
        counter.clear();
        std::string ouputname = out_dri2 + std::to_string(n + 1) + ".jpg"; //outpu 路径
        Mat fs_mat = fsbh(pic,fbase,n);
        bq.push_mat(fs_mat);  //标签： 仿射矩阵
        gaussnoise(pic);  //高斯噪声
        pj(pic); //四周补10
        imwrite(ouputname, pic);
        bq.convert_mat(fs_mat);//转换center根据仿射矩阵
        outfile << bq;
        bq.clearall();
    }
    outfile.close();
}
void print_all(const std::vector<Tx*> &tx,const std::vector<Point> &pp,const std::vector<Scalar> &scalar,const std::vector<F_base*> &fbase){
    std::ofstream  outfile;
    std::vector<Point> point_tmp = {Point(75,75),Point(223,75),Point(75,220),Point(223,140 + 73),Point(150,173),Point(159,254),Point(125,280),Point(150,198)};
    std::vector<Scalar>  vectorscalar;
    for(int i = 0;i < tx.size();i++){
        vectorscalar.push_back(Scalar(125 + 15 * i));
    }
    outfile.open("out_all.txt");
    Bq bq;
    for(int n = 0;n < 10;n++) {
        Mat  pic = Mat(300,300,CV_8UC1,Scalar(0));
        bq.bq["nb"].push_back(n + 1);  //标签：number

        for (int i = 0; i < tx.size(); i++) {
            tx[i]->show(pic, point_tmp[i], vectorscalar[i]);
            bq.bq["xh"].push_back(i + 1); //标签： xh
            bq.bq["hd"].push_back(vectorscalar[i].val[0]);
            bq.bq["center"].push_back(point_tmp[i].x);
            bq.bq["center"].push_back(point_tmp[i].y);
        }
        std::string ouputname = "./all\\" + std::to_string(n + 1) + ".jpg"; //outpu 路径
        Mat fs_mat = fsbh(pic,fbase,n);
        bq.push_mat(fs_mat);  //标签： 仿射矩阵
        gaussnoise(pic);  //高斯噪声
        pj(pic); //四周补10
        imwrite(ouputname, pic);
        bq.convert_mat(fs_mat);//转换center根据仿射矩阵
        outfile << bq;
        bq.clearall();
    }
    outfile.close();
    }


//    int index(0);
//    int init(0);
//    std::set<int> counter;
//    for(int i = 0;i < tx.size();i++){
//        tx[index]->show(pic,point_tmp[i],vectorscalar[i]);
//    }
//    for(int n = 0;n < N;n++) {
//        Mat  pic = Mat(300,300,CV_8UC1,Scalar(0));
//        bq.bq["nb"].push_back(n + 1);  //标签：number
//        point_tmp = pp;
//        for (int i = 0; i < 4; i++) {
//
//            while (counter.find(index = output_sj(0, 7)) != counter.end()) {
//            }
//            tx[index]->show_py(pic, point_tmp[i], scalar[init++]);
//            counter.insert(index);
//            bq.bq["xh"].push_back(index + 1); //标签： xh
//            bq.bq["hd"].push_back(scalar[init - 1].val[0]);
//            bq.bq["center"].push_back(point_tmp[i].x);
//            bq.bq["center"].push_back(point_tmp[i].y);
//        }
//
//        init = 0;
//        counter.clear();
//        std::string ouputname = "D:\\pic\\out3\\" + std::to_string(n + 1) + ".jpg"; //outpu 路径
//        Mat fs_mat = fsbh(pic,fbase);
//        bq.push_mat(fs_mat);  //标签： 仿射矩阵
//        gaussnoise(pic);  //高斯噪声
//        imwrite(ouputname, pic);
//        bq.convert_mat(fs_mat);//转换center根据仿射矩阵
//        outfile << bq;
//        bq.clearall();
//    }
//    outfile.close();
