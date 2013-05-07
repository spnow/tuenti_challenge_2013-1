#include <opencv2/opencv.hpp>

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

bool framesSame(const cv::Mat& a, const cv::Mat& b) {
  bool eq = true;
  cv::Mat diff;
  cv::absdiff(a, b, diff);
  for(int row = 0; row < diff.rows; ++row) {
    for(int col = 0; col < diff.cols; ++col) {
      if (diff.at<uchar>(row, col)) {
        return false;
      }
    }
  }
  return true;
}

// Read the whole video, frame by frame. First fame is 0 since the router
// LED is turned off. Then write to a binary file every byte read for 8 frames.
int main() {
  cv::VideoCapture cap("build/video.avi");
  if (!cap.isOpened()) {
    std::cout << "!!! Failed to open file " << std::endl;
    return -1;
  }

  cv::Mat frame, prev, first;

  int i = 0;
  unsigned char byte = 0;
  std::ofstream out("out");

  while(cap.read(frame)) {
    if (i == 0) {
      first = frame.clone();
    }
    if (!framesSame(frame, first)) {
      byte |= 1 << (7-i % 8);
    } else {
    }

    if (i && i % 8 == 7) {
      out << byte;
      byte = 0;
    }

    prev = frame.clone();
    ++i;
  }

  return 0;
}
