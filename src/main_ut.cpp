#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

__declspec(dllimport)
void detectFaces(cv::CascadeClassifier &faceCascade, cv::Mat image, std::vector<cv::Rect> &foundFaces);
