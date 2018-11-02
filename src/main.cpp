#include <vector>
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace fs = boost::filesystem;

class UnsupportedImageFormatException : public std::exception {
public:
	fs::path imgPath;
public:
	UnsupportedImageFormatException(fs::path imgPath) :std::exception(imgPath.string().c_str()), imgPath(imgPath) {
	}
};

class Main {
private:
	cv::CascadeClassifier faceCascade;
	fs::path imagePath;
public:
	Main(std::string imagePath):imagePath(imagePath) {
		std::string faceCascadeName = "etc/haarcascades/haarcascade_frontalface_alt.xml";
		if (!faceCascade.load(faceCascadeName)) {
			throw std::runtime_error("failed to load cascade data file");
		}
	}

	void detectFaces(cv::Mat image, std::vector<cv::Rect> &foundFaces) {
		cv::Mat grayImg;
		cv::cvtColor(image, grayImg, CV_BGR2GRAY);
		cv::equalizeHist(grayImg, grayImg);
		faceCascade.detectMultiScale(grayImg, foundFaces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
	}

	fs::path processImage(fs::path imgPath, std::vector<cv::Rect> &foundFaces) {
		auto image = cv::imread(imgPath.string(), CV_LOAD_IMAGE_COLOR);
		if (image.empty()) {
			throw UnsupportedImageFormatException(imgPath);
		}
		detectFaces(image, foundFaces);
		// blur faces
		for (auto &r : foundFaces) {
			auto roi = image(r);
			GaussianBlur(roi, roi, cv::Size(), 5, 5);
		}
		// save 1/2 size jpeg with blurred faces, return file path
		fs::path newPath = imgPath.parent_path() / fs::path("blurred_" + imgPath.stem().string() +  imgPath.extension().string());
		cv::imwrite(newPath.string(), image);
		// print file path & num of faces
		std::cout << imgPath << ": numFaces: " << foundFaces.size() << std::endl;
		return newPath;
	}

	void run() {
		namespace pt = boost::property_tree;
		fs::recursive_directory_iterator fileIt(imagePath);
		fs::recursive_directory_iterator end;
		pt::ptree imagesNode;
		// for each file in path:
		while (fileIt != end) {
			fs::path _path(*fileIt);
			if (!fs::is_directory(_path)) {
				std::vector<cv::Rect> foundFaces;
				try {
					auto processedFileName = processImage(_path, foundFaces);
					// save into result.json: file12, foundFaces
					pt::ptree facesNode;
					for (auto &r : foundFaces) {
						std::ostringstream st;
						st << r.x << ", " << r.y << ", " << r.width << ", " << r.height;
						facesNode.add("rect", st.str());
					}

					pt::ptree imageNode;
					imageNode.add("fileName", processedFileName.string());
					imageNode.add_child("faces", facesNode);
					imagesNode.add_child("image", imageNode);

				} catch (UnsupportedImageFormatException &ex) {
					std::cout << "can't read " << ex.imgPath << std::endl;
				}
			}
			++fileIt;
		}
		pt::ptree jsonRoot;
		jsonRoot.add_child("images", imagesNode);
		fs::path jsonFile("result.json");
		pt::write_json((imagePath / jsonFile).string(), jsonRoot);
	}
};


int main(int argc, const char** argv) {
	if (argc < 2) {
		std::cout << "parameter required: path to images folder" << std::endl;
		return -1;
	}
	Main m(argv[1]);
	m.run();
	return 0;
}