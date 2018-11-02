#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

__declspec(dllimport)
void detectFaces(cv::CascadeClassifier &faceCascade, std::string imgPath, cv::Mat image, std::vector<cv::Rect> &foundFaces);

class CnFirstTest : public ::testing::Test {
protected:
    cv::CascadeClassifier faceCascade;
    std::string imgPath;
    cv::Mat image;
    std::vector<cv::Rect> foundFaces;
protected:
    virtual void SetUp() {
        imgPath = "data/1/2. 1376.jpg";
        image = cv::Mat(100, 100, 1);
    }
};

TEST_F(CnFirstTest, ImageNull) {
    image = cv::Mat();
    ASSERT_THROW({
        detectFaces(faceCascade, imgPath, image, foundFaces);
    }, std::invalid_argument);
}

TEST_F(CnFirstTest, ImagePathNull) {
    imgPath = "";
    ASSERT_THROW({
        detectFaces(faceCascade, imgPath, image, foundFaces);
    }, std::invalid_argument);
}
