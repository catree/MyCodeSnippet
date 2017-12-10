// RANdom SAmple Consensus algorithm
// author: chenyu

#include "FeatureMatcher.h"

#include <cmath>

#define INFINITY 0x7fffffff

int N = INFINITY; // 采样次数
int excuteSC = 0;           // 已执行的采样次数


int getInliersCount()
{

}

void getSampleCount(vector<Point2d> imgPoints1, vector<Point2d> imgPoints2, double p = 0.99)
{
    int pointCount = imgPoints1.count();
    while(N > excuteSC)
    {
        int inliersCount = getInliersCount();
        double inlierProbability = inliersCounts / pointCount;
        N = (int)(log(1 - p) / log( 1 - pow(inlierProbability, pointCount) ) );
        excuteSC++;
    }
}


int main()
{
    Mat img1 = imread("/home/chenyu/桌面/三维重建/data/david/B00.jpg");
    Mat img2 = imread("/home/chenyu/桌面/三维重建/data/david/B01.jpg");

    if(img1.empty())
    {
        cout << "img1 cannot be loaded!" << endl;
        return -1;
    }

    if(img2.empty())
    {
        cout << "img2 cannot be loaded!" << endl;
        return -1;
    }

    FeatureMatcher* matcher = new FeatureMatcher();
    matcher->startMatch(img1, img2, kp1, kp2);
    delete(matcher);

    waitKey(0);
}