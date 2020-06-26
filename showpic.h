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
        int ll = 10;
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
    Ttx(int h) : h(h) {}
    Ttx(){}

    void show(Mat &mat, const Point &center, const Scalar &scalar) override {
        input.push_back(Point(center.x - this->h / 2.0,center.y - this->h /2.0));
        input.push_back(Point(center.x + this->h / 2.0,center.y - this->h /2.0));
        input.push_back(Point(center.x + this->h / 2.0 + this->h,center.y + this->h /2.0));
        input.push_back(Point(center.x -  this->h / 2.0 - this->h,center.y + this->h /2.0));

//        for(auto point : input){
//            std::cout << point.x << " " << point.y << std::endl;
//        }
        fillConvexPoly(mat,input,scalar,LINE_8,0);
        input.clear();
    }

    void show_py(Mat &mat, const Point &center, const Scalar &scalar) override {
        input.push_back(Point(center.x - this->h / 2.0,center.y - this->h /2.0));
        input.push_back(Point(center.x + this->h / 2.0,center.y - this->h /2.0));
        input.push_back(Point(center.x + this->h / 2.0 + this->h,center.y + this->h /2.0));
        input.push_back(Point(center.x -  this->h / 2.0 - this->h,center.y + this->h /2.0));
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
    int h = 20;
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
        ellipse(mat,center,Size(r,r),0,initan,endan,scalar,-1);
    }

    void show_py(Mat &mat, const Point &center, const Scalar &scalar) override {

    }


private:
    int r = 45;
    int initan = 0;
    int endan = -180;
};
#endif //PIC2_SHOWPIC_H
