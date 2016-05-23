#include <opencv2/opencv.hpp>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

void Str2Point(string src, Point2f& pt)
{
	string first,second;
	stringstream xstm,ystm;
	bool seq=true;
	for (auto iter = src.begin(); iter != src.end(); iter++)
	{
		if (*iter != ' '&&seq)
		{
			first.push_back(*iter);
		}
		else if (*iter == ' ')
		{
			seq = false;
		}
		else if (*iter != ' '&&!seq)
		{
			second.push_back(*iter);
		}
	}
	xstm << first;
	xstm >> pt.x;

	ystm << second;
	ystm >> pt.y;

}

void getGroundTruth(int number, Point2f& left, Point2f& right)
{
	std::stringstream strStream;
	std::string filename;
	int line=1;
	string str;
	strStream << number;
	if (number < 10)
	{
		filename = "BioID-FaceDatabase-V1.2/BioID_000" + strStream.str() + ".pts";
	}
	if (number < 100 && number >= 10)
	{
		filename = "BioID-FaceDatabase-V1.2/BioID_00" + strStream.str() + ".pts";
	}
	if (number < 1000 && number >= 100)
	{
		filename = "BioID-FaceDatabase-V1.2/BioID_0" + strStream.str() + ".pts";
	}
	if (number < 10000 && number >= 1000)
	{
		filename = "BioID-FaceDatabase-V1.2/BioID_" + strStream.str() + ".pts";
	}
	ifstream in(filename);
	if (in.good())
	{
		while (getline(in, str))
		{
			if (line == 4)
			{
				//cout << str << endl;
				Str2Point(str,right);
				
			}
			if (line == 5)
			{
				//cout << str << endl;
				Str2Point(str, left);
			}
			line++;
		}

	}
}

void readImg(int number, Mat& img)
{
	std::stringstream strStream;
	std::string filename;
	strStream << number;
	if (number < 10)
	{
		filename = "BioID-FaceDatabase-V1.2/BioID_000" + strStream.str() + ".pgm";
	}
	if (number < 100&&number>=10)
	{
		filename = "BioID-FaceDatabase-V1.2/BioID_00" + strStream.str() + ".pgm";
	}
	if (number < 1000 && number >= 100)
	{
		filename = "BioID-FaceDatabase-V1.2/BioID_0" + strStream.str() + ".pgm";
	}
	if (number < 10000 && number >= 1000)
	{
		filename = "BioID-FaceDatabase-V1.2/BioID_" + strStream.str() + ".pgm";
	}
	//filename = "eye region/eye" + strStream.str() + ".jpg";
	img = cv::imread(filename);
	strStream.str("");
}

int main()
{
	Mat img;
	Point2f LeftEye, RightEye;
	int count = 0;
	while (waitKey(0) != 27)
	{
		readImg(count, img);
		getGroundTruth(count, LeftEye, RightEye);
		cout << "Left:" << LeftEye.x << " " << LeftEye.y << endl;
		cout << "Right:" << RightEye.x << " " << RightEye.y << endl;
		if (img.data != nullptr)
		{
			circle(img, LeftEye, 1, Scalar(150, 0, 0), -1);
			circle(img, RightEye, 1, Scalar(0, 0, 150), -1);
			imshow("img", img);
		}
		count++;
	}
}