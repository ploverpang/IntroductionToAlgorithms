#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int findBottlePointIdx(const vector<Point> &points)
{
	int bottleIdx=0;
	int bottleY = points[0].y;
	for(int i=1; i<points.size(); i++)
	{
		if(points[i].y > bottleY)
		{
			bottleIdx = i;
			bottleY = points[i].y;
		}
	}
	return bottleIdx;
}

inline int crossMultiply(Point &p0, Point &p1, Point &p2)
{
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

class AngleLess
{
public:
	AngleLess(Point &base) : _base(base) {}
	bool operator()(Point &p1, Point &p2)
	{
		int cross = crossMultiply(_base, p1, p2);
		return (cross < 0 || (cross==0 && p1.y > p2.y));
	}
private:
	Point _base;
};

void sortPointsByPolarAngle(vector<Point> &points)
{
	Point bottleP = points[0];
	AngleLess comp(bottleP);

	sort(points.begin()+1, points.end(), comp);
}

bool turnLeft(Point &p0, Point &p1, Point &p2)
{
	return (crossMultiply(p0, p1, p2) < 0);
}

vector<Point> findConvexHull(vector<Point> &points)
{
	if(points.size() < 4)
		return points;

	vector<Point> vertexPoints;
	stack<Point> vertexStack;

	int bottleIdx = findBottlePointIdx(points);
	Point tmp = points[0];
	points[0] = points[bottleIdx];
	points[bottleIdx] = tmp;

	sortPointsByPolarAngle(points);

	for(int i=0; i<3; i++)
		vertexStack.push(points[i]);
	for(int i=3; i< points.size(); i++)
	{
		do{
			Point top = vertexStack.top();
			vertexStack.pop();
			Point subTop = vertexStack.top();

			bool bReserve = turnLeft(subTop, top, points[i]);
			if(bReserve)
			{
				vertexStack.push(top);
				break;
			}

		}while(1);
		vertexStack.push(points[i]);
	}

	while(!vertexStack.empty())
	{
		vertexPoints.push_back(vertexStack.top());
		vertexStack.pop();
	}

	return vertexPoints;
}

void prepareNPoints(vector<Point> &points, int N)
{
	const int MAX_RANGE = 500;
	for(int i=0; i<N; i++)
	{
		points.push_back(Point(250+rand()%MAX_RANGE, 250+rand()%MAX_RANGE));
	}
}

void drawPointAndConvexHull(Mat &img, vector<Point> &points, vector<Point> &vertexPoints)
{

	for(int i=0; i<points.size(); i++)
	{
		circle(img, points[i], 1, Scalar(0,255,0));
		char buffer[256];
		sprintf(buffer, "%d", i);
		putText(img, string(buffer), points[i]+Point(5,5), CV_FONT_HERSHEY_SIMPLEX, 1, Scalar(255,0,0));
	}

	for(int i=0; i<vertexPoints.size(); i++)
		line(img, vertexPoints[i], vertexPoints[(i+1)%vertexPoints.size()], Scalar(0,0,255), 2);
}

//int main()
//{
//	vector<Point> points;
//	prepareNPoints(points, 20);
//	vector<Point> convexVertex = findConvexHull(points);
//
//	cv::Mat drawImg(Size(1000,1000), CV_8UC3, Scalar::all(0));
//
//	drawPointAndConvexHull(drawImg, points, convexVertex);
//	imshow("vertex", drawImg);
//	waitKey();
//
//	return 0;
//}
