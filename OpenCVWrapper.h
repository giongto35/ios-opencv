//
//  OpenCVWrapper.h
//  TestOpenCV
//
//  Created by Nguyen Huu Thanh on 10/10/16.
//  Copyright © 2016 nus.cs3216.a0112069. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface OpenCVWrapper : NSObject

+ (UIImage*) copyImage: (UIImage*) inputImage;
+ (UIImage*) faceDetect: (UIImage*) inputImage;
+ (UIImage*) addTurban: (UIImage*) inputImage :(UIImage*) turbanImage;
//+(NSString *) openCVVersionString;

@end
