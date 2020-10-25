# Self-Driving-Car-POC-with-DonkeyCar

## Introduction:

This was a fun DIY side project I worked on in collaboration with my colleagues at Panasonic Automotive as a way to expand this automotive supplier's technology roadmap in Artificial Intelligence and Machine Learning. The team followed guidelines set by the Donkey Car Open Source project site and attempted to build a model that can help navigate the toy car around a track. 

This is a DIY project. For more info, you can visit https://www.donkeycar.com/. The open source project also has an active Slack channel too where you can get insight from people worldwide who are also doing this project for fun! Here, I'll detail what my team did and provide any tips for you to consider if you decide to take on the challenge yourselves! :)


## Setup:

You can find detailed and easy-to-follow user guides on http://docs.donkeycar.com/. Some difficulties could be attributed to configuring the WiFi connnection of the Donkey Car, especially if the local WiFi you use also has a proxy that severely and strictly limits the content and internet traffic. The best thing to do is to use your mobile phone's hotspot as a WiFi connection for the Donkey Car; if you do, make sure that your phone is fully charged and that you would be present the entire time for all activities involving Donkey Car (you'll understand what I mean).

## Calibration: 

To have the Donkey Car move properly, you would need to calibrate its throttle and steering parameters. My team referred to the guide at http://docs.donkeycar.com/guide/calibrate/. There is really no "magic" pair of steering and throttle values that can work for all possible track environments. Also, calibration may have to be done several times depending on the track's characteristics and environment (i.e lighting, surface, types of turns, corners). Once my team found the pair of throttle and steering values that we needed, then my colleagues and I practiced driving to get a feel for controlling the Donkey Car. The Donkey Car had to be controlled via its Web Application which had to be accessed via the WiFi or hotspot, hence that's why I earlier emphasized that anyone providing the mobile phone hotspot should be present at all times for any activities in Donkey Car. The guide for driving the car can be found at http://docs.donkeycar.com/guide/get_driving/.

## Training Autopilot Model:

Finally, now comes the fun part! My team referred to the training and modeling documentation at http://docs.donkeycar.com/guide/train_autopilot/.

Once my team got used to driving the Donkey Car, it was time to collect data by driving the car around the track by controlling it using the web application through the hotspot. The kind of data being collected are json files and image frames. The json files has data on throttle and steering values the car had at that very moment. The image files shows the view from the Donkey Car's camera. 

The guide recommended 5-20k samples of data (i.e 5-20k json files and 5-20k json files). However, the team collected close to 40k samples. No one on the team is an expert in driving the Donkey Car as it is easy to veer off the track. Hence, when cleaning up the data, the frames that show the car off the track are removed, and then the corresponding json files are also removed. That way, the team had enough clean data to train and build the model. After cleaning, the team retained 90% of the total data. 

Now with the cleaned data, the team builds the model. Donkey Car already has a framework that facilitates the model building process. Once the model is built, the team assesses the accuracy of the model as the Donkey Car runs in autopilot. 

All of these steps - data collection, data cleaning, and buliding autopllot model - were iterated over until the team got the model that enabled the Donkey Car to complete at least two laps around the track (you can find the video here in the repo "DonkeyCarRun_07MAR2019.mp4"). It turns out that the Donkey Car in autopilot mode veered off course if it saw other objects (i.e chairs, trashcan, tables) or people. Thus, the team had to move stuff around in the area surrounding the track and make sure that no one is in the way or in the view of the Donkey Car while collecting data. 

## Further Applications

Once the team got a working model, the team experimented with the following real-world applications:

1. Stopping the car at a red light
2. Collect additional sensor data (i.e accelerometer, LIDAR, battery voltage) and send it up to a cloud service, similar to fleet management. 

