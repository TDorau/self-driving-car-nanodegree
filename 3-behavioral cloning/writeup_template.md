
---

**Behavioral Cloning Project**

The goals / steps of this project are the following:
* Use the simulator to collect data of good driving behavior
* Build, a convolution neural network in Keras that predicts steering angles from images
* Train and validate the model with a training and validation set
* Test that the model successfully drives around track one without leaving the road
* Summarize the results with a written report


[//]: # (Image References)

[image1]: ./examples/placeholder.png "Model Visualization"
[image2]: ./examples/placeholder.png "Grayscaling"
[image3]: ./examples/placeholder_small.png "Recovery Image"
[image4]: ./examples/placeholder_small.png "Recovery Image"
[image5]: ./examples/placeholder_small.png "Recovery Image"
[image6]: ./examples/placeholder_small.png "Normal Image"
[image7]: ./examples/placeholder_small.png "Flipped Image"

## Rubric Points
###Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/432/view) individually and describe how I addressed each point in my implementation.  

---
###Files Submitted & Code Quality

####1. Submission includes all required files and can be used to run the simulator in autonomous mode

My project includes the following files:
* model.py containing the script to create and train the model
* drive.py for driving the car in autonomous mode
* model.h5 containing a trained convolution neural network 
* writeup_report.md 

####2. Submission includes functional code
Using the Udacity provided simulator and my drive.py file, the car can be driven autonomously around the track by executing 
```sh
python drive.py model.h5
```

####3. Submission code is usable and readable

The model.py file contains the code for training and saving the convolution neural network. The file shows the pipeline I used for training and validating the model, and it contains comments to explain how the code works.

###Model Architecture and Training Strategy

####1. An appropriate model architecture has been employed

My model consists of a downsized version of the NVDIA end-to-end learning model with depths between 24 and 48 (model.py lines 62-78) 

The model includes RELU layers to introduce nonlinearity. A seperate preprocessing routine has been implemented. As an alternative the keras lambda layer could be used for preprocessing without it being necessary to change drive.py.
 

####2. Attempts to reduce overfitting in the model

The model contained dropout layers in order to reduce overfitting. It turned out that using Dropout-layers didn't improve model accuracy. To reduce overfitting the number of epochs was reduced from around 8 to 3 in the final model.

The model was trained and validated on different data sets to ensure that the model was not overfitting. The model was tested by running it through the simulator and ensuring that the vehicle could stay on the track.

####3. Model parameter tuning

The model used an adam optimizer, so the learning rate was not tuned manually (model.py line 81).

####4. Appropriate training data

Training data was chosen to keep the vehicle driving on the road. I tried to use my own data with recovery laps, curve laps and center driving in both directions of the track. This strategy didn't lead to a viable training data set in multiple attempts, so I decided to simply use the dataset provided by Udacity.


###Model Architecture and Training Strategy

####1. Solution Design Approach

The overall strategy for deriving a model architecture was to use an architecutre which is known to work very well in this scenario. 

My first step was to use a convolution neural network model similar to the NVDIA-model. I thought this model might be appropriate because in its original paper it is used in quite similar scenarios. Because I used the dataset provided by Udacity I had to downsize the model a bit because to train the NVDIA model more training data would've been necessary.

In order to gauge how well the model was working, I split my image and steering angle data into a training and validation set. I found that my first model had a low mean squared error on the training set but a high mean squared error on the validation set. This implied that the model was overfitting. 

To combat the overfitting, I modified the model so that there are less convolutional layers and I reduced the number of epochs.

The final step was to run the simulator to see how well the car was driving around track one. There were a few spots where the vehicle fell off the track especially the section right after the bridge. To improve the driving behavior in these cases, I learned in the forum that it is beneficial to transform the cv2-BGR image to the RGB-space.

At the end of the process, the vehicle is able to drive autonomously around the track without leaving the road or wiggling around too much.

####2. Final Model Architecture

The final model architecture (model.py lines 62-78) consisted of a convolution neural network with the following layers and layer sizes:

* Convolutional layer with filter number 1 and kernel size 1 with glorot uniform initialization and same padding
* Convolutional layer with filter number 24 and kernel size 5, relu activation
* Convolutional layer with filter number 24 and kernel size 5, relu activation
* Convolutional layer with filter number 36 and kernel size 5, relu activation
* Convolutional layer with filter number 48 and kernel size 5, relu activation
* Flatten Layer
* 4 fully connected layers with output 100, 50, 10 and 1

####3. Creation of the Training Set & Training Process

Like it was already mentioned, I tried to create a dataset on my own, but ended up using the Udacity dataset.

I finally randomly shuffled the data set and put 20% of the data into a validation set. 

I used this training data for training the model. The validation set helped determine if the model was over or under fitting. The ideal number of epochs was 3 as evidenced by the final video. I used an adam optimizer so that manually training the learning rate wasn't necessary.
