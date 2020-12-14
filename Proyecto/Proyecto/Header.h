#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <time.h>

using namespace std;
using namespace cv;

class Proyecto {
public:
	void Prosesamiento();
	void ColorDetection();
};
