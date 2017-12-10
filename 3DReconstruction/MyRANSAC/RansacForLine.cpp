#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

// a 2d-point is represented as (x, y)
struct Point2d
{
    double x;   // x坐标
    double y;   // y坐标
};

// a 2d-line is represented as y = slove * x + bias
struct Line2d
{
    double slove; // 直线斜率
    double bias;  // 直线偏置
};

#define SAMPLE_POINT_NUMBER 500

vector<Point2d> samplePoints;

// generating sample points randomly
void generateSamplePoints()
{
    for(int i = 0; i < SAMPLE_POINT_NUMBER; i++)
    {

    }
}


// Random Sample consensus
// param maxIteration: the maximum number of iterations allowed in the algorithm
// param threshold: a threshold value for determining when a data point fit a model

void RANSAC(int maxIteration, int threshold)
{

}

int main()
{

}