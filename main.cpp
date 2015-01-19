// Boost headers
#include <boost/foreach.hpp>

// OpenCV headers
#include <opencv/cv.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//C++ headers
#include <iostream>
#include <string.h>

//other
#include "Recognizer.h"

using namespace std;
using namespace cv;

#define PI 3.14159265

Recognizer reco;
vector<Rect> faces; //this vector contains the faces details (x,y,width and height) to be recognized.
vector<Rect> new_class;
Mat image;			//the image frame where "faces" are located

void recognize();


int main(int argc, char **argv)
{
	init(argc, argv, "pftracking_node");
	
	string fn="/home/user/recognizer/inputs.csv"; //path to inputs.csv file
	if(!reco.prepare(fn))	//load the images (from the image pool) and their labels
    {
        	cout("error preparing LBP recognizer, could not read"<<fn);
        	return -1;
    }
    recognize();
	return 0;
}


void recognize()
{
    vector<int> prediction;
    vector<double>confidence;
    cout<<"recognize called"<<endl;
    Mat gray;
    cvtColor(frame,gray,CV_BGR2GRAY);
    if(image.empty())	//do not run recognizer if "image" is empty
	{
		cout<<"cannot recognize, image frame is empty"<<endl;
		return;
	}
	 if(faces.empty())	//do not run recognizer if "faces" is empty
	{
		cout<<"erros: no face to be recognized"<<endl;
		return;
	}
	reco.find_multiple(gray,faces,prediction,confidence);
	for(int i=0;i<faces.size();i++)
	if(prediction[i] <0)
		{
			cout<<"face unrecognized, adding new face to database"<<endl;
			new_class.push_back(faces[i];
			reco.add_class(new_class);
			new_class.clear();
		}
	else
		cout<<"pred: "<<prediction[i]<<" conf: "<<confidence[i]<<end;
}
