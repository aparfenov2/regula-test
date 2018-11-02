#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

__declspec(dllexport)
void detectFaces(cv::CascadeClassifier &faceCascade, cv::Mat image, std::vector<cv::Rect> &foundFaces) {
	cv::Mat grayImg;
	cv::cvtColor(image, grayImg, CV_BGR2GRAY);
	cv::equalizeHist(grayImg, grayImg);
	faceCascade.detectMultiScale(grayImg, foundFaces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
}
