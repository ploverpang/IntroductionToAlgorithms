#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include <opencv2/opencv.hpp>

using namespace std;

bool sortByX(const cv::Point &p1, const cv::Point &p2)
{
	return p1.x < p2.x;
}

bool sortByY(const cv::Point &p1, const cv::Point &p2)
{
	return p1.y < p2.y;
}

float l2Distance(const cv::Point &p1, const cv::Point &p2)
{
	return sqrtf((float)((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)));
}

float findNearestPointWhenPointLess3(vector<cv::Point> &points, vector<cv::Point> &nearestPointPair)
{
	if(points.size() <= 1)
	{
		return FLT_MAX;
	}
	if(points.size() == 2)
	{
		float dist = l2Distance(points[0], points[1]);
		nearestPointPair[0] = points[0];
		nearestPointPair[1] = points[1];
		return dist;
	}
	if(points.size() == 3)
	{
		float dist;
		float dist0_1 = l2Distance(points[0], points[1]);
		float dist0_2 = l2Distance(points[0], points[2]);
		float dist1_2 = l2Distance(points[1], points[2]);
		if(dist0_1 <= dist0_2 && dist0_1 <= dist1_2)
		{
			dist = dist0_1;
			nearestPointPair[0] = points[0];
			nearestPointPair[1] = points[1];
		}
		else if(dist0_2 <= dist0_1 && dist0_2 <= dist1_2)
		{
			dist = dist0_2;
			nearestPointPair[0] = points[0];
			nearestPointPair[1] = points[2];
		}
		else
		{
			dist = dist1_2;
			nearestPointPair[0] = points[1];
			nearestPointPair[1] = points[2];
		}

		return dist;
	}
}

void splitPointByX(vector<cv::Point> &PX, int splitX, vector<cv::Point> &PL, vector<cv::Point> &PR)
{
	for(int i=0; i<PX.size(); i++)
	{
		if(PX[i].x <= splitX)
			PL.push_back(PX[i]);
		if(PX[i].x >= splitX)
			PR.push_back(PX[i]);
	}
}

void splitPointInRangeX(vector<cv::Point> &PY, int splitX, int delta, vector<cv::Point> &inRangeX)
{
	int startX = splitX - delta;
	int endX = splitX + delta;

	for(int i=0; i<PY.size(); i++)
	{
		if(startX <= PY[i].x && PY[i].x <= endX)
			inRangeX.push_back(PY[i]);
	}
}

float combineTwoSplit(vector<cv::Point> &PY, int splitX, int delta, vector<cv::Point> &nearestPointPair)
{
	assert(nearestPointPair.size() == 2);

	vector<cv::Point> inRangeX;
	splitPointInRangeX(PY, splitX, delta, inRangeX);

	float minDist = FLT_MAX;

	for(int i=0; i<inRangeX.size(); i++)
	{
		for(int j=i+1; j<i+7 && j<inRangeX.size(); j++)
		{
			float dist = l2Distance(inRangeX[i], inRangeX[j]);
			if(dist < minDist)
			{
				minDist = dist;
				nearestPointPair[0] = inRangeX[i];
				nearestPointPair[1] = inRangeX[j];
			}
		}
	}
	return minDist;
}

float reserveProcess(vector<cv::Point> &PX, vector<cv::Point> &PY, vector<cv::Point> &nearestPointPair)
{
	assert(PX.size()==PY.size());
	float dist;
	nearestPointPair.resize(2);
	if(PX.size() < 4)
	{
		return findNearestPointWhenPointLess3(PX, nearestPointPair);
	}

	int splitX = (PX[0].x+PX[PX.size()-1].x)>>1;
	vector<cv::Point> XL, XR, YL, YR;

	splitPointByX(PX, splitX, XL, XR);
	splitPointByX(PY, splitX, YL, YR);

	vector<cv::Point> nearestL, nearestR;
	float distL = reserveProcess(XL, YL, nearestL);
	float distR = reserveProcess(XR, YR, nearestR);
	float minDist;

	if(distL < distR)
	{
		minDist = distL;
		nearestPointPair[0] = nearestL[0];
		nearestPointPair[1] = nearestL[1];
	}
	else
	{
		minDist = distR;
		nearestPointPair[0] = nearestR[0];
		nearestPointPair[1] = nearestR[1];
	}

	vector<cv::Point> nearestBetweenSplit(2);
	float minDistBetweenSplit = combineTwoSplit(PY, splitX, minDist, nearestBetweenSplit);

	if(minDistBetweenSplit < minDist)
	{
		minDist = minDistBetweenSplit;
		nearestPointPair[0] = nearestBetweenSplit[0];
		nearestPointPair[1] = nearestBetweenSplit[1];
	}
	return minDist;
}

float findNearestPointPair(vector<cv::Point> &points, vector<cv::Point> &nearestPointPair)
{
	vector<cv::Point> PX(points);
	vector<cv::Point> PY(points);

	sort(PX.begin(), PX.end(), sortByX);
	sort(PY.begin(), PY.end(), sortByY);

	return reserveProcess(PX, PY, nearestPointPair);
}

extern void prepareNPoints(vector<cv::Point> &points, int N);

float verifyMethod(vector<cv::Point> &points, vector<cv::Point> &nearestPointPair)
{
	float minDist = FLT_MAX;
	nearestPointPair.resize(2);
	for(int i=0; i<points.size(); i++)
	{
		for(int j=i+1; j<points.size();j++)
		{
			float dist = l2Distance(points[i], points[j]);
			if(dist < minDist)
			{
				minDist = dist;
				nearestPointPair[0] = points[i];
				nearestPointPair[1] = points[j];
			}
		}
	}
	return minDist;
}
int main()
{
	vector<cv::Point> points;
	prepareNPoints(points, 20);

	vector<cv::Point> nearestPair;
	float dist = findNearestPointPair(points, nearestPair);

	vector<cv::Point> verifyNearestPair;
	float verifyDist = verifyMethod(points, verifyNearestPair);

	cv::Mat dbgImg(1000, 1000, CV_8UC3, cv::Scalar(0));
	for(int i=0; i<points.size(); i++)
	{
		cv::circle(dbgImg, points[i], 1, cv::Scalar(0,255,0));
	}
	cv::line(dbgImg, nearestPair[0], nearestPair[1], cv::Scalar(0,0,255), 2);
	cv::line(dbgImg, verifyNearestPair[0], verifyNearestPair[1], cv::Scalar(255,0,255), 2);

	cv::imshow("nearest point pair", dbgImg);
	cv::waitKey();
}

