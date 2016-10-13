//
//  CppWrapper.cpp
//  TestOpenCV
//
//  Created by Nguyen Huu Thanh on 11/10/16.
//  Copyright © 2016 nus.cs3216.a0112069. All rights reserved.
//

#include "CppWrapper.hpp"


const std::string face_cascade_name = "HaarCascades/haarcascade_frontalface_alt.xml";
const std::string eyes_cascade_name = "HaarCascades/haarcascade_eye_tree_eyeglasses.xml";
const cv::Mat defaultMat = cv::Mat();

cv::Mat copy (cv::Mat& imageMat) {
    cv::Point center(50, 50);
    cv::circle( imageMat, center, 10, cv::Scalar(255, 0, 0), 4, 8, 0);
    return imageMat;
}

void overlayImage(const cv::Mat &background, const cv::Mat &foreground,
             cv::Mat &output, cv::Point2i location)
{
    background.copyTo(output);
    
    
    // start at the row indicated by location, or at row 0 if location.y is negative.
    for(int y = std::max(location.y , 0); y < background.rows; ++y)
    {
        int fY = y - location.y; // because of the translation
        
        // we are done of we have processed all rows of the foreground image.
        if(fY >= foreground.rows)
            break;
        
        // start at the column indicated by location,
        
        // or at column 0 if location.x is negative.
        for(int x = std::max(location.x, 0); x < background.cols; ++x)
        {
            int fX = x - location.x; // because of the translation.
            
            // we are done with this row if the column is outside of the foreground image.
            if(fX >= foreground.cols)
                break;
            
            // determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
            double opacity =
            ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])
            
            / 255.;
            
            
            // and now combine the background and foreground pixel, using the opacity,
            
            // but only if opacity > 0.
            for(int c = 0; opacity > 0 && c < output.channels(); ++c)
            {
                unsigned char foregroundPx =
                foreground.data[fY * foreground.step + fX * foreground.channels() + c];
                unsigned char backgroundPx =
                background.data[y * background.step + x * background.channels() + c];
                output.data[y*output.step + output.channels()*x + c] =
                backgroundPx * (1.-opacity) + foregroundPx * opacity;
            }
        }
    }
}

cv::Mat addTurban (cv::Mat& imageMat, cv::Mat& turbanMat, std::string pathFace, std::string pathEyes) {
    std::vector<cv::Rect> faces = listFaces(imageMat, pathFace, pathEyes);
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Mat result;
        cv::rectangle(imageMat, cv::Point(faces[i].x, faces[i].y), cv::Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), cv::Scalar(255, 0, 0));
        cv::Mat resizedTurbanMat;
        float ratio = float(faces[i].width) / 250;
        cv::resize(turbanMat, resizedTurbanMat, cv::Size(0, 0),ratio, ratio);
        int twidth = resizedTurbanMat.size().width;
        int theight = resizedTurbanMat.size().height;
        overlayImage(imageMat, resizedTurbanMat, result, cv::Point(faces[i].x + faces[i].width / 2 - twidth / 2, faces[i].y - theight + 200 * ratio));
        imageMat = result;
    }
    return imageMat;
}

std::vector<cv::Rect> listFaces (cv::Mat& imageMat, std::string pathFace, std::string pathEyes) {
    cv::CascadeClassifier face_cascade;
    cv::CascadeClassifier eyes_cascade;
    if( !face_cascade.load( pathFace ) ){ printf("--(!)Error loading face cascade\n"); return defaultMat; };
    if( !eyes_cascade.load( pathEyes ) ){ printf("--(!)Error loading eyes cascade\n"); return defaultMat; };
    
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;
    
    cvtColor( imageMat, frame_gray, cv::COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
    
    return faces;
}

cv::Mat faceDetect (cv::Mat& imageMat, std::string pathFace, std::string pathEyes) {
    cv::CascadeClassifier face_cascade;
    cv::CascadeClassifier eyes_cascade;
    if( !face_cascade.load( pathFace ) ){ printf("--(!)Error loading face cascade\n"); return defaultMat; };
    if( !eyes_cascade.load( pathEyes ) ){ printf("--(!)Error loading eyes cascade\n"); return defaultMat; };
    
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;
    
    cvtColor( imageMat, frame_gray, cv::COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
    
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( imageMat, center, cv::Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );
        
        cv::Mat faceROI = frame_gray( faces[i] );
        std::vector<cv::Rect> eyes;
        
        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
        
        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            cv::Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( imageMat, eye_center, radius, cv::Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    //-- Show what you got
    return imageMat;
    
}
