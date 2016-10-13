//
//  CppWrapper.hpp
//  TestOpenCV
//
//  Created by Nguyen Huu Thanh on 11/10/16.
//  Copyright © 2016 nus.cs3216.a0112069. All rights reserved.
//

#ifndef CppWrapper_hpp
#define CppWrapper_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

cv::Mat copy (cv::Mat& imageMat);
cv::Mat faceDetect (cv::Mat& imageMat, std::string pathFace, std::string pathEyes);
std::vector<cv::Rect> listFaces (cv::Mat& imageMat, std::string pathFace, std::string pathEyes);
cv::Mat addTurban (cv::Mat& imageMat, cv::Mat& turbanMat, std::string pathFace, std::string pathEyes);

#endif /* CppWrapper_hpp */
