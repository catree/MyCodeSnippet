#ifndef UTILITY_H
#define UTILITY_H

#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <ctime>
#include <sys/time.h> 

void saveImage(Mat img, string path)
{
	vector<int> compression_params;
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	try {
		imwrite(path + ".png", img, compression_params);
	}
	catch (cv::Exception& ex) {
		cout << "Exception converting image to PNG format: %s\n" << ex.what();
		return;
	}
}



double getCurrentTime()  
{  
    struct timeval time ;  
    if (gettimeofday(&time,NULL)){  
        return 0;  
    }  
    return (double)time.tv_sec + (double)time.tv_usec * .000001;  
} 

#endif