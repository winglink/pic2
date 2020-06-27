//
// Created by think on 2020/6/26.
//

#ifndef PIC2_SHOWPIC_H
#define PIC2_SHOWPIC_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <iostream>
using namespace  cv;
const double PI = std::atan(1.0) * 4;
class Tx{
public:
    virtual void show(Mat &mat,const Point &center,const Scalar &scalar) = 0;
    virtual void show_py(Mat &mat,const Point &center,const Scalar &scalar) = 0;

protected:
    std::vector<Point> input;
};

class Triangle : public Tx{
public:
    Triangle(int ll) : ll(ll) {}
    Triangle() {}

    void show_py(Mat &mat, const Point &center, const Scalar &scalar) override {
        input.push_back(Point(center.x,center.y - ll));
        input.push_back(Point(center.x - ll * cos(30.0 / 180.0 * PI),center.y + ll * sin(30.0 / 180.0 * PI)));
        input.push_back(Point(center.x + ll * cos(30.0 / 180.0 * PI),center.y + ll * sin(30.0 / 180.0 * PI)));
        int py(0);
        if(center.y >= 150)
            py = (150 - input[0].y);
        else
            py = abs(150 - input[2].y ) ;//偏移量
//            std::cout <<"start" << std::endl;
//             for(auto point : input){
//            std::cout << point.x << " " << point.y << std::endl;
//        }
//    polylines(pic, input, true, scalar[i], -1, LINE_8, 0);
        std::for_each(input.begin(),input.end(),[py](Point &p){ p.y = p.y + py; });
        fillConvexPoly(mat,input,scalar,LINE_8,0);
        input.clear();
    }

    void show(Mat &mat, const Point &center, const Scalar &scalar) override {
        input.push_back(Point(center.x,center.y - ll));
        input.push_back(Point(center.x - ll * cos(30.0 / 180.0 * PI),center.y + ll * sin(30.0 / 180.0 * PI)));
        input.push_back(Point(center.x + ll * cos(30.0 / 180.0 * PI),center.y + ll * sin(30.0 / 180.0 * PI)));
//            std::cout <<"start" << std::endl;
//             for(auto point : input){
//            std::cout << point.x << " " << point.y << std::endl;
//        }
//    polylines(pic, input, true, scalar[i], -1, LINE_8, 0);
        fillConvexPoly(mat,input,scalar,LINE_8,0);
        input.clear();
    }

private:
        int ll = 8;
};
class Square : public Tx{
public:
    Square(int ll) : ll(ll) {}

    Square() {}

    void show(Mat &mat, const Point &center, const Scalar &scalar) override {
        rectangle(mat,Point(center.x - ll, center.y - ll),Point(center.x + ll,center.y + ll),scalar,-1);
    }

    void show_py(Mat &mat, const Point &center, const Scalar &scalar) override {
        rectangle(mat,Point(center.x - ll, center.y - ll),Point(center.x + ll,center.y + ll),scalar,-1);
    }

private:
        int ll = 75; //1/2边长

};

class Wbx : public Tx{
public:
    Wbx(int r) : r(r) {}
    Wbx() {}

    void show(Mat &mat, const Point &center, const Scalar &scalar) override {
        input.push_back(Point(center.x,center.y - r));
        input.push_back(Point(center.x + r * sin(angle),center.y - r * cos(angle)));
        input.push_back(Point(center.x + r * sin(angle / 2),center.y + r * cos(angle / 2)));
        input.push_back(Point(center.x - r * sin(angle / 2),center.y + r * cos(angle / 2)));
        input.push_back(Point(center.x - r * sin(angle),center.y - r * cos(angle)));

//        for(auto point : input){
//            std::cout << point.x << " " << point.y << std::endl;
//        }
        fillConvexPoly(mat,input,scalar,LINE_8,0);
        input.clear();
    }

    void show_py(Mat &mat, const Point &center, const Scalar &scalar) override {
        input.push_back(Point(center.x,center.y - r));
        input.push_back(Point(center.x + r * sin(angle),center.y - r * cos(angle)));
        input.push_back(Point(center.x + r * sin(angle / 2),center.y + r * cos(angle / 2)));
        input.push_back(Point(center.x - r * sin(angle / 2),center.y + r * cos(angle / 2)));
        input.push_back(Point(center.x - r * sin(angle),center.y - r * cos(angle)));
        int py(0) ;
        if(center.y >= 150)
            py = 150 - input[0].y ;
        else
            py = 150 - input[2].y;

        std::for_each(input.begin(),input.end(),[py](Point &p){ p.y = p.y + py;});

//        for(auto point : input){
//            std::cout << point.x << " " << point.y << std::endl;
//        }
        fillConvexPoly(mat,input,scalar,LINE_8,0);
        input.clear();
    }

private:
      int r = 70;
      double angle = 72.0 / 180.0 * PI;

};
class Ttx : public Tx{
public:
    Ttx(int h, int a, int b) : h(h), a(a), b(b) {}
    Ttx(){}

    void show(Mat &mat, const Point &center, const Scalar &scalar) override {
        int tt = (a + 2 * b) * h / (3.0 * (a + b));
        input.push_back(Point(center.x - a / 2.0,center.y - tt));
        input.push_back(Point(center.x + a / 2.0,center.y - tt));
        input.push_back(Point(center.x + b / 2.0,center.y + h - tt));
        input.push_back(Point(center.x - b / 2.0,center.y + h - tt));

//        for(auto point : input){
//            std::cout << point.x << " " << point.y << std::endl;
//        }
        fillConvexPoly(mat,input,scalar,LINE_8,0);
        input.clear();
    }

    void show_py(Mat &mat, const Point &center, const Scalar &scalar) override {
        int tt = (a + 2 * b) * h / (3.0 * (a + b));
        input.push_back(Point(center.x - a / 2.0,center.y - tt));
        input.push_back(Point(center.x + a / 2.0,center.y - tt));
        input.push_back(Point(center.x + b / 2.0,center.y + h - tt));
        input.push_back(Point(center.x - b / 2.0,center.y + h - tt));
        int py(0) ;
        if(center.y >= 150)
            py = 150 - input[0].y ;
        else
            py = 150 - input[2].y;

        std::for_each(input.begin(),input.end(),[py](Point &p){ p.y = p.y + py;});

//        for(auto point : input){
//            std::cout << point.x << " " << point.y << std::endl;
//        }
        fillConvexPoly(mat,input,scalar,LINE_8,0);
        input.clear();
    }

private:
    int h = 17;
    int a = 15;
    int b = 30;
};
class Circle : public Tx{
public:
    Circle(int r) : r(r) {}
    Circle() {}

    void show(Mat &mat, const Point &center, const Scalar &scalar) override {
        Point center1(center.x,center.y);
        circle(mat,center1,r,scalar,-1,LINE_8);
    }

    void show_py(Mat &mat, const Point &center, const Scalar &scalar) override {
        int py(0);
        if(center.y >= 150)
            py = 150 - center.y + r ;
        else
            py = 150 - center.y - r;
        Point center1(center.x,center.y + py);
        circle(mat,center1,r,scalar,-1,LINE_8);

    }

private:
        int r = 73;
};
class Halfcircle : public Tx{
public:
    Halfcircle() {}
    Halfcircle(int r, int initan, int endan) : r(r), initan(initan), endan(endan) {}

    void show(Mat &mat, const Point &center, const Scalar &scalar) override {
        Point center2(center.x,center.y + 4 * r / (3 * PI));
        ellipse(mat,center2,Size(r,r),0,initan,endan,scalar,-1);
    }

    void show_py(Mat &mat, const Point &center, const Scalar &scalar) override {

    }


private:
    int r = 25;
    int initan = 0;
    int endan = -180;
};

class Sx : public Tx{
public:
    Sx() {}
    Sx(int r, int initan, int endan) : r(r), initan(initan), endan(endan) {}

    void show(Mat &mat, const Point &center, const Scalar &scalar) override {
        Point center2(center.x,center.y + 4 * r / (3 * PI));
        ellipse(mat,center2,Size(r,r),0,initan,endan,scalar,-1);

    }

    void show_py(Mat &mat, const Point &center, const Scalar &scalar) override {

    }

private:
    int r = 40;
    int initan = -30;
    int endan = -150;
};
class Wjx : public Tx {
public:
    Wjx() {}
    Wjx(int r, int r1) : r(r), R(r1) {}

    void show(Mat &mat, const Point &center, const Scalar &scalar) override {
        std::vector<Point> input1;
        std::vector<Point> input2;
        Point tmp;
        for(int i = 0;i < 5;i++){
            tmp.x = center.x + cos((18 + 72 * i) / 180.0 * PI) * R;
            tmp.y = center.y - sin((18 + 72 * i) / 180.0 * PI) * R;
            input1.push_back(tmp);
        }

        for(int i = 0;i < 5;i++){
            tmp.x = center.x + cos((54+ 72 * i) / 180.0 * PI) * r;
            tmp.y = center.y - sin((54+ 72 * i) / 180.0 * PI) * r;
            input2.push_back(tmp);
        }
        auto start = input2.begin();
        for(auto init = input1.begin(); init != input1.end();init++){
             start = input2.insert(start,(*init));
             start++;
             if( (start + 1) != input2.end())
                 start++;
        }
        std::vector<std::vector<Point>> result;
        result.push_back(input2);
        fillPoly(mat,result,scalar);
    }

    void show_py(Mat &mat, const Point &center, const Scalar &scalar) override {

    }

private:
    int r = 30;
    int R = 65;
};
#endif //PIC2_SHOWPIC_H
