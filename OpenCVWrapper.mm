//
//  OpenCVWrapper.m
//  TestOpenCV
//
//  Created by Nguyen Huu Thanh on 10/10/16.
//  Copyright © 2016 nus.cs3216.a0112069. All rights reserved.
//

#import "OpenCVWrapper.h"
#import "UIImage+OpenCV.h"
#import "CppWrapper.hpp"

@implementation OpenCVWrapper

NSString *const faceCascadeName = @"haarcascade_frontalface_alt_tree";
NSString *const eyesCascadeName = @"haarcascade_eye_tree_eyeglasses";

+ (UIImage*) copyImage: (UIImage*) inputImage {
    cv::Mat imageMat = [inputImage CVMat3];
    UIImage* modifiedImage = [UIImage imageWithCVMat: copy(imageMat)];
    return modifiedImage;
}

NSString *getResource(NSString* resource, NSString* extension) {
    NSString* filePath = [[NSBundle mainBundle] pathForResource:resource ofType:extension];
    return filePath;
}
//- (NSString*) getResource: (NSString*) resource :(NSString*) extension{
//    NSString* filePath = [[NSBundle mainBundle] pathForResource:resource ofType:extension];
//    return filePath;
//}

+ (UIImage*) addTurban: (UIImage*) inputImage :(UIImage*) turbanImage {
    //    cv::Mat imageMat = [inputImage CVMat3];
    cv::Mat imageMat;
    cv::Mat turbanMat;
    UIImageToMat(inputImage, imageMat);
    UIImageToMat(turbanImage, turbanMat, true);
    std::string cppPathFace([getResource(faceCascadeName, @"xml") UTF8String]);
    std::string cppPathEyes([getResource(eyesCascadeName, @"xml") UTF8String]);
//    cv::Rect roi( cv::Point( 100, 100 ), turbanMat.size() );
//    UIImage* modifiedImage;
//    turbanMat.copyTo( imageMat( roi ) );
    UIImage* modifiedImage = [UIImage imageWithCVMat: addTurban(imageMat, turbanMat, cppPathFace, cppPathEyes)];
    return modifiedImage;
//    return MatToUIImage(faceDetect(imageMat, cppPathFace, cppPathEyes));
}

+ (UIImage*) faceDetect: (UIImage*) inputImage :(NSString*) pathFace :(NSString*) pathEyes {
//    cv::Mat imageMat = [inputImage CVMat3];
    cv::Mat imageMat;
    UIImageToMat(inputImage, imageMat);
    std::string cppPathFace([getResource(faceCascadeName, @"xml") UTF8String]);
    std::string cppPathEyes([getResource(eyesCascadeName, @"xml") UTF8String]);
//    UIImage* modifiedImage = [UIImage imageWithCVMat: faceDetect(imageMat, cppPathFace, cppPathEyes)];
//    return modifiedImage;
    return MatToUIImage(faceDetect(imageMat, cppPathFace, cppPathEyes));
}

//
//+ (UIImage*) processImageWithOpenCV: (UIImage*) inputImage
//{
//    NSArray* imageArray = [NSArray arrayWithObject:inputImage];
//    UIImage* result = [[self class] processWithArray:imageArray];
//    return result;
//}
//
//+ (UIImage*) processWithOpenCVImage1:(UIImage*)inputImage1 image2:(UIImage*)inputImage2;
//{
//    NSArray* imageArray = [NSArray arrayWithObjects:inputImage1,inputImage2,nil];
//    UIImage* result = [[self class] processWithArray:imageArray];
//    return result;
//}
//
//+ (UIImage*) processWithArray:(NSArray*)imageArray
//{
//    if ([imageArray count]==0){
//        NSLog (@"imageArray is empty");
//        return 0;
//    }
//    std::vector<cv::Mat> matImages;
//    
//    for (id image in imageArray) {
//        if ([image isKindOfClass: [UIImage class]]) {
//            /*
//             All images taken with the iPhone/iPa cameras are LANDSCAPE LEFT orientation. The  UIImage imageOrientation flag is an instruction to the OS to transform the image during display only. When we feed images into openCV, they need to be the actual orientation that we expect them to be for stitching. So we rotate the actual pixel matrix here if required.
//             */
//            UIImage* rotatedImage = [image rotateToImageOrientation];
//            cv::Mat matImage = [rotatedImage CVMat3];
//            NSLog (@"matImage: %@",image);
//            matImages.push_back(matImage);
//        }
//    }
//    NSLog (@"stitching...");
//    cv::Mat stitchedMat = stitch (matImages);
//    UIImage* result =  [UIImage imageWithCVMat:stitchedMat];
//    return result;
//}
//

@end
