#include "EGGraph.h"
#include "FeatureManager.h"

#define __GMS__
#define __DEBUG__

EGGraph::EGGraph()
{

}

EGGraph::~EGGraph()
{
    nodeList.clear();

    for(int i = 0; i < this->nodeNum; i++)
    {
        delete [] edgeMap[i];
    }
    delete [] edgeMap;
}

vector<EGNode> EGGraph::getEGNodeList() const
{
    return this->nodeList;
}

EGEdge** EGGraph::getEdgeMap() const
{
    return this->edgeMap;
}

int EGGraph::getNodeNum() const
{
    return this->nodeNum;
}

void EGGraph::startMatch(vector<Mat> imgBuffer, int i, int j)
{
    vector<KeyPoint> keypoints1, keypoints2;
    Mat img1 = imgBuffer[i];
    Mat img2 = imgBuffer[j];

        Ptr<ORB> orb = ORB::create(10000);
        orb->setFastThreshold(0);

        #ifdef __GMS__
            keypoints1.assign(this->nodeList[i].keypoints.begin(), this->nodeList[i].keypoints.end());
            keypoints2.assign(this->nodeList[j].keypoints.begin(), this->nodeList[j].keypoints.end());
        #else
            this->edgeMap[i][j].keypoints1.assign(this->nodeList[i].keypoints.begin(), this->nodeList[i].keypoints.end());
            this->edgeMap[i][j].keypoints2.assign(this->nodeList[j].keypoints.begin(), this->nodeList[j].keypoints.end());
        #endif
        this->edgeMap[i][j].descriptor1 = this->nodeList[i].descriptor.clone();
        this->edgeMap[i][j].descriptor2 = this->nodeList[j].descriptor.clone();
    
        BFMatcher matcher(NORM_HAMMING);
        vector<DMatch> allMatches;
    
        #ifdef __GMS__
            matcher.match(this->edgeMap[i][j].descriptor1, this->edgeMap[i][j].descriptor2, allMatches);
        #else
            matcher.match(this->edgeMap[i][j].descriptor1, this->edgeMap[i][j].descriptor2, this->edgeMap[i][j].matches);
        #endif
    
        #ifdef __GMS__
            FeatureManager featureManager;
            featureManager.filterWrongMatches(img1, img2, keypoints1, keypoints2,
                this->edgeMap[i][j].keypoints1, this->edgeMap[i][j].keypoints2, allMatches, this->edgeMap[i][j].matches, "GMS");
        #endif
    
        #ifdef __DEBUG__
        
        cout << "image pair (" << i << ", " << j << "): ";
        cout << "Before ransac(using gms), there are " << this->edgeMap[i][j].matches.size() << " matches" << endl; 
    
        #endif
}

void EGGraph::buildEGNode(vector<Mat> imgBuffer)
{
    cout << "build EGNode begins..." << endl;
    for(int i = 0; i < imgBuffer.size(); i++)
    {
        EGNode egNode;
        
        Ptr<ORB> orb = ORB::create(10000);
        orb->setFastThreshold(0);
        orb->detectAndCompute(imgBuffer[i], Mat(), egNode.keypoints, egNode.descriptor);
        egNode.idx = i;

        this->nodeList.push_back(egNode);
        cout << egNode.keypoints.size() << endl;
    }
    this->nodeNum = imgBuffer.size();
    cout << "build EGNode ends...\n" << endl;
}

void EGGraph::buildEGEdge(vector<Mat> imgBuffer)
{
    cout << "build EGEdge begins...\n"; 
    edgeMap = new EGEdge* [this->nodeNum];

    for(int i = 0; i < this->nodeNum; i++)
    {
        edgeMap[i] = new EGEdge [this->nodeNum];

        for(int j = i + 1; j < this->nodeNum; j++)
        {
            this->startMatch(imgBuffer, i, j);
            this->estimateFundamentalMat(imgBuffer, i, j);
        }
    }
    cout << "build EGEdge ends...\n" << endl;
}

void EGGraph::buildEGGraph(vector<Mat> imgBuffer)
{
    this->buildEGNode(imgBuffer);
    this->buildEGEdge(imgBuffer);
}

void EGGraph::estimateFundamentalMat(vector<Mat> imgBuffer, int i, int j)
{
    FeatureManager featureManager;
    vector<KeyPoint> rkpts1, rkpts2;
    vector<DMatch> rMatches;


    if(this->edgeMap[i][j].matches.size() < 16) 
    {
        cout << "matches number " << this->edgeMap[i][j].matches.size() << " < 16\n" << endl;
        return;
    }

    featureManager.filterWrongMatches(
        imgBuffer[i], imgBuffer[j], 
        this->edgeMap[i][j].keypoints1, this->edgeMap[i][j].keypoints2,
        rkpts1, rkpts2, this->edgeMap[i][j].matches, rMatches, "RANSAC");

    
    vector<KeyPoint>().swap(this->edgeMap[i][j].keypoints1);
    vector<KeyPoint>().swap(this->edgeMap[i][j].keypoints2);
    vector<DMatch>().swap(this->edgeMap[i][j].matches);

    // updates keypoints and matches
    for(int k = 0; k < rMatches.size(); k++)
    {
        this->edgeMap[i][j].keypoints1.push_back(rkpts1[k]);
        this->edgeMap[i][j].keypoints2.push_back(rkpts2[k]);
        this->edgeMap[i][j].matches.push_back(rMatches[k]);
    }

    #ifdef __DEBUG__
        cout << "image pair (" << i << ", " << j << "): ";
        cout << "after ransac(using gms),  there are " << this->edgeMap[i][j].matches.size() << " matches\n" << endl;        
    #endif
}

void EGGraph::estimateEssentialMat()
{

}

