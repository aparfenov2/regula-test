#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

__declspec(dllexport)
void detectFaces(cv::CascadeClassifier &faceCascade, std::string imgPath, cv::Mat image, std::vector<cv::Rect> &foundFaces) {
    if (image.empty()) {
        throw std::invalid_argument("image");
    }
    if (imgPath.empty()) {
        throw std::invalid_argument("imgPath");
    }
    cv::Mat grayImg;
	cv::cvtColor(image, grayImg, CV_BGR2GRAY);
	cv::equalizeHist(grayImg, grayImg);
	faceCascade.detectMultiScale(grayImg, foundFaces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
    std::cout << imgPath << " processing done. Faces found " << foundFaces.size() << std::endl;
}
