#include "opencv2/imgproc/imgproc.hpp"
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

struct point 
{
	int x;
	int y;
};

typedef struct point point;

//Function to detect yellow color
point detect(Mat img)
{
	point p;
	inRange(img,Scalar(40,100,100),Scalar(70,200,200),img); //Setting range for yellow color
	imshow("Range",img);
	Moments m;
	m=moments(img);
	p.x=m.m10/m.m00;
	p.y=m.m01/m.m00;
	return p;
}

int main()
{
	static point p_last;
	// Initialize camera
	VideoCapture cam(0);
	
	if(!cam.isOpened())
		cout<<"Camera not initialized";
	
	while(1)
	{
		point p_cur;
		Mat frame;
		cam >> frame;
		
		flip(frame,frame,1);
		
		p_cur=detect(frame);
		
		line(frame,Point(p_cur.x,p_cur.y),Point(p_last.x,p_last.y),Scalar(40,255,255),5,CV_AA);
		
		p_last.x=p_cur.x;
		p_last.y=p_cur.y;
		
		imshow("Video",frame);
		
		if(waitKey(30)>=0)
			break;
	}
}


	
