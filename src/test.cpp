//#include "ImageLoader.h"
#include "FeatureManager.h"
#include "ImagePair.h"
#include <ctime>
#include <sys/time.h>
#include "Utility.h"


double getCurrentTime()  
{  
    struct timeval time ;  
    if (gettimeofday(&time,NULL)){  
        return 0;  
    }  
    return (double)time.tv_sec + (double)time.tv_usec * .000001;  
}

int main()
{
    ImageLoader* imageLoader = new ImageLoader();
    imageLoader->loadImage();

    vector<Mat> imgBuffer = imageLoader->getImgBuffer();

    vector<ImagePair> imgPairLists;
    
    double s = getCurrentTime();
    for(unsigned int i = 0; i < imgBuffer.size(); i++)
    {
        for(unsigned int j = i + 1; j < imgBuffer.size(); j++)
        {
            imresize(imgBuffer[i], 480);
            imresize(imgBuffer[j], 480);
            ImagePair imgPair(i, j, imgBuffer[i], imgBuffer[j], false);
            imgPair.startMatch();
            imgPair.estimateFundamentalMat();
            imgPairLists.push_back(imgPair);
        }
    }
    double e = getCurrentTime();
    cout << "using " << e - s << " ms." << endl;

    
    // imgPair.startMatch();
    // vector<KeyPoint> kp1, kp2;
    // vector<DMatch> matches_all;
    // kp1 = imgPair.getKeypoints1();
    // kp2 = imgPair.getKeypoints2();
    // matches_all = imgPair.getMatches();


    // cout << "before ransac, there are " << matches_all.size() << "matches." << endl;

    // Mat orbMatches;
    // drawMatches(img1, kp1, img2, kp2, matches_all, orbMatches);
    // imshow("matches", orbMatches);

    // estimate fundamental matrix
    // imgPair.estimateFundamentalMat();

    // vector<KeyPoint> ekp1, ekp2;
    // vector<DMatch> ematches_all;
    // ekp1 = imgPair.getKeypoints1();
    // ekp2 = imgPair.getKeypoints2();
    // ematches_all = imgPair.getMatches();

    // cout << "after ransac, there are " << ematches_all.size() << "matches." << endl;
    
    // Mat eorbMatches;
    // drawMatches(img1, ekp1, img2, ekp2, ematches_all, eorbMatches);
    // imshow("matches", eorbMatches);


    delete imageLoader;

    waitKey();
}