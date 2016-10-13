//
//  ViewController.swift
//  TestOpenCV
//
//  Created by Nguyen Huu Thanh on 10/10/16.
//  Copyright © 2016 nus.cs3216.a0112069. All rights reserved.
//

import UIKit
import Foundation
import AVFoundation

class ViewController: UIViewController, UIImagePickerControllerDelegate, UINavigationControllerDelegate {

    @IBOutlet weak var origImage: UIImageView!
    @IBOutlet weak var modifiedImage: UIImageView!
    @IBOutlet weak var turbanImage: UIImageView!
    
    let imagePicker = UIImagePickerController()
    
    @IBAction func selectImageTapped(_ sender: AnyObject) {
        imagePicker.allowsEditing = false
        imagePicker.sourceType = .photoLibrary
        
        present(imagePicker, animated: true, completion: nil)
    }
    
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        dismiss(animated: true, completion: nil)
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : Any]) {
        if let pickedImage = info[UIImagePickerControllerOriginalImage] as? UIImage {
            origImage.contentMode = .scaleAspectFit
            origImage.image = pickedImage
            
            let copyImage:UIImage = OpenCVWrapper.addTurban(origImage.image, turbanImage.image) as UIImage
            modifiedImage.image = copyImage
        }
        
        dismiss(animated: true, completion: nil)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
//        OpenCVVersion.text = OpenCVWrapper.openCVVersionString()
//        let copyImage:UIImage = OpenCVWrapper.copy(origImage.image) as UIImage
        
        imagePicker.delegate = self
    }

    @IBOutlet weak var OpenCVVersion: UILabel!
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

