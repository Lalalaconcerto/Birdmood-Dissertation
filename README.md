# Birdmood-Dissertation

This project develops a system for acoustic monitoring device to classify birds’ emotions by their calls through machine learning and an interactive device which allows human to speak to birds. 

The recording devices are based on the Raspberry Pi 4, where a USB microphone and a speaker are attached. Machine learning model is deployed on the Raspberry Pi. The model classifies different bird calls with different emotional labels. The training results are uploaded to MQTT. For a full overview of the electronic and mechanical design of the Raspberry Pi based device, please refer to the Birdmood hardware handover document.

At the same time, a push button is introduced which allows people to control the speaker to play pre-recorded birds calls for communication with the real bird. The overview of the design of the Human-bird sound interaction device based on Raspberry Pi is shown in ww.

A physical device displays the bird emotions training results with a RGB LED text display based on ESP8266 NodeMcu board. It subscribes data from MQTT and display it with different lighted texts. The overview of the mechanical design of the bird emotion notification device based on ESP8266 is shown in Birdmood hardware handover document.

The design of Bird Emotion Classification Using Edge Impulse and Live Data Streaming is shown as follows.

## Code design

Audio captured with microphone is clipped and used as input for model training. The model is trained on Edge Impulse. Here, 4 birds’ emotions are labelled in the mode with random audio clips as background noise. The project is made public: 



Once the model is well trained, the model is downloaded in a file named modelfile.eim by following the Installation guidance of Linux Python SDK issued by Edge Impulse, as well as a json file named edge-impulse-config.json . In the Linux Python SDK library, an example file named classify.py can be modified to run the model on Raspberry Pi 4, which is located in the directory linux-sdk-python/examples/audio/ . 



The firmware is triggered to run on boot from the command python3 classify-mqtt.py modelfile.eim. 



The sequence of events from the classify function (in classify-mqtt.py) is as follows:

1. Import library of training model on Edge Impulse 

2. Import library of MQTT publishing data 

3. Publish training results on MQTT : client.publish(topic + label, score)

The screenshot of the data published on MQTT is shown in MQTT-Screenshot

## **Configuring the device**

The modelfile.eim file, the edge-impulse-config.json file and the classify-mqtt.py file should be placed on a microSD card and insert into the Raspberry Pi 4. The edge-impulse-config.json file contains the authentication details for the account and project created on Edge Impulse.



## **Setup** 

##### **Setup from a stock Raspberry Pi OS image using Raspberry Pi 4** 

The Raspberry Pi 4 is fully supported on Edge Impulse, If you would start using this, please follow the instruction issued by Edge Impulse: Raspberry Pi 4 https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-cpu-gpu-targets/raspberry-pi-4

You could connect to the Raspberry Pi and connect to Edge Impulse easily.

 
