# Birdmood-Dissertation

This project develops a system for acoustic monitoring device to classify birds’ emotions by their calls through machine learning and an interactive device which allows human to speak to birds. 

The recording devices are based on the Raspberry Pi 4, where a USB microphone and a speaker are attached. Machine learning model is deployed on the Raspberry Pi. The model classifies different bird calls with different emotional labels. The training results are uploaded to MQTT. For a full overview of the electronic and mechanical design of the Raspberry Pi based device, please refer to [Human-bird sound interaction device handover document](https://github.com/Lalalaconcerto/Birdmood-Dissertation/tree/main/Human-bird%20sound%20interaction%20device).

At the same time, a push button is introduced which allows people to control the speaker to play pre-recorded birds calls for communication with the real bird. The overview of the design of the Human-bird sound interaction device based on Raspberry Pi is shown in **Section 2** as follows.

A physical device displays the bird emotions training results with a RGB LED text display based on ESP8266 NodeMcu board. It subscribes data from MQTT and display it with different lighted texts. The overview of the mechanical design of the bird emotion notification device based on ESP8266 is shown in **Section 3** as follows.

 

## 1. **Bird Emotion Classification Using Edge Impulse and Live Data Streaming**

### **Code design**



Audio captured with microphone is clipped and used as input for model training. The model is trained on Edge Impulse. Here, 4 birds’ emotions are labelled in the mode with random audio clips as background noise. The project is made public:  https://studio.edgeimpulse.com/public/115266/latest



Once the model is well trained, the model is downloaded in a file named `modelfile.eim` by following the Installation guidance of **[Linux Python SDK](https://github.com/edgeimpulse/linux-sdk-python)** issued by Edge Impulse, as well as a json file named `edge-impulse-config.json` . In the Linux Python SDK library, an [example file](https://github.com/edgeimpulse/linux-sdk-python/tree/master/examples/audio) named `classify.py` can be modified to run the model on Raspberry Pi 4, which is located in the directory `linux-sdk-python/examples/audio/` . 

 

The firmware is triggered to run on boot from the command `python3 classify-mqtt.py modelfile.eim`.  

 

The sequence of events from the classify function (in `classify-mqtt.py`) is as follows:

1. Import library of training model on Edge Impulse 

2. Import library of MQTT publishing data 

3. Publish training results on MQTT : `client.publish(topic + label, score)`

`classify-mqtt.py` is available at [here](https://github.com/Lalalaconcerto/Birdmood-Dissertation/tree/main/Human-bird%20sound%20interaction%20device). The screenshot of the data published on MQTT is shown here:

![1981660920269_ pic](https://user-images.githubusercontent.com/92024194/185814930-64797b05-7ac9-4933-9735-6d7d6cafb6ca.jpg)




### **Configuring the device**

The `modelfile.eim file`, the `edge-impulse-config.json` file and the `classify-mqtt.py file` should be placed on a microSD card and insert into the Raspberry Pi 4. The `edge-impulse-config.json` file contains the authentication details for the account and project created on Edge Impulse.



### **Setup** 

**Setup from a stock Raspberry Pi OS image using Raspberry Pi 4** 

The Raspberry Pi 4 is fully supported on Edge Impulse, If you would start using this, please follow the instruction issued by Edge Impulse: [Raspberry Pi 4](https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-cpu-gpu-targets/raspberry-pi-4) 

You could connect to the Raspberry Pi and connect to Edge Impulse easily.

 
 <br/>
 <br/>
 

## 2. **Human-bird sound interaction device based on Raspberry Pi**

 

A speaker is attached to the Raspberry Pi, as well as a push button. The push button can control the speaker to play a pre-recorded bird singing, which allow people to talk to the real bird. The command is programmed in a [python file](https://github.com/Lalalaconcerto/Birdmood-Dissertation/blob/main/Human-bird%20sound%20interaction%20device/sound.py) named `sound.py`. The overview of the electronic and mechanical design of the Human-bird sound interaction device based on Raspberry Pi is shown [here](https://github.com/Lalalaconcerto/Birdmood-Dissertation/tree/main/Human-bird%20sound%20interaction%20device).

### **Code design:**

The sequence of events from the `sound` function (`in sound.py` ) is as follows:

1. Library `pygame`, `time` and gpiozero are imported for button control.
2. Define GPI of Raspberry Pi for Button connected.
3. Determine the audio file to play：`pygame.mixer.Sound（）`
4. `While` loop to play the audio when the button is pressed.

### **Hardware Components:**

| Hardware Components                                          |
| ------------------------------------------------------------ |
| [Raspberry Pi Compute Module 4](https://www.amazon.co.uk/Raspberry-Pi-Model-4GB/dp/B09TTNF8BT/ref=sr_1_3?crid=L9QIZHTYDX2R&keywords=raspberry+pi+4&qid=1661119483&sprefix=raspberry+pi%2Caps%2C67&sr=8-3) |
| [MONO USB Microphone](https://www.amazon.co.uk/Lavalier-Omnidirectional-Condenser-Computer-Microphone/dp/B0176NRE1G/ref=sr_1_5?crid=3TAUFMI6UXJQK&keywords=movo+usb+microphone&qid=1661119676&sprefix=movo+usb+microphone%2Caps%2C58&sr=8-5) |
| [Push Button](https://www.amazon.co.uk/X-DREE-Momentary-Rectangular-Interruptor-pulsador/dp/B09J2RB7ML/ref=sr_1_5?crid=D7FJKDTYZV95&keywords=%60rectangular+push+button+yellow&qid=1661119714&sprefix=%2Caps%2C63&sr=8-5) |
| USB Speaker                                                  |



### **Software apps and online devices:**

| Software apps and online devices                             |
| ------------------------------------------------------------ |
| Python                                                       |
| SSH                                                          |
| [Raspberry Pi OS](https://www.raspberrypi.org/software/) image |



### **Hand tools and fabrication machines:**

| Hand tools and fabrication machines |
| ----------------------------------- |
| Prusa 3D printer                    |

### Physical map:

The pysical maps are shown [here](https://github.com/Lalalaconcerto/Birdmood-Dissertation/tree/main/Human-bird%20sound%20interaction%20device/Pyhical%20map%20Pi).

### **Enclosure:** 

 The container of the Rasoberry Pi is made by WoodPLA material and printed by a Prusa 3D printer. The design sketches are shown [here](https://github.com/Lalalaconcerto/Birdmood-Dissertation/tree/main/Human-bird%20sound%20interaction%20device/Enclosure%20design%20Pi).

### **Circuit Diagram**:

The circuit diagram is shown [here](https://github.com/Lalalaconcerto/Birdmood-Dissertation/tree/main/Human-bird%20sound%20interaction%20device/Circuit%20diagram%20Pi).



<br/>
<br/>



## 3. **Bird Emotion Notification based on a RGB LED text display.** 

The device displays the emotion classified by a RGB LED text display based on ESP8266.

Training results are transferred to MQTT and subscribed on ESP8266. Then different texts express the different emotions of the bird by illuminated text. The overview of the electronic and mechanical design of the bird emotion notification device based on ESP8266 is shown [here](https://github.com/Lalalaconcerto/Birdmood-Dissertation/tree/main/Bird%20emotion%20notification%20device).

### **Code design:**

To programe ESP8266, Arduino IDE is applied. The sequence of events from the `Word_notification` function (in `Word_notification.ino` ) is as follows:



1. Library `<ESP8266WiFi.h>` and `<PubSubClient.h>` are introduced for WIFI connection.

2. Library `<Adafruit_NeoPixel.h>` is introduced for LED display

3. MQTT Broker is connected.`setup()`

4. Subscribe each topic on MQTT. `client.subscribe("SUBSCRIBE_TOPIC")`

5. Callback function and reconnect function to ensure that data can be collected continuously

6. LED design based on different classification result. `pixels.setPixelColor()` and `pixels.show()`

   

### **Hardware Components:**

| Hardware Components                                          |
| ------------------------------------------------------------ |
| [WS2812 LED 5050 RGB 8x8 64 LED Matrix for Arduino](https://www.aliexpress.com/item/32598269446.html?aff_fcid=a56b9cfe443a40d9b20243556f4fc76c-1661120123428-09544-bxmN10hi&aff_fsk=bxmN10hi&aff_platform=product&sk=bxmN10hi&aff_trace_key=a56b9cfe443a40d9b20243556f4fc76c-1661120123428-09544-bxmN10hi&terminal_id=b04c076b35264ed1b8df616667923947) |
| [ESP8266 Nodemcu](https://www.amazon.co.uk/10Gtek-ESP8266-connector-development-Micropython/dp/B09J4NLNVJ/ref=sr_1_1_sspa?crid=1Y1PAD1C1YUUW&keywords=esp8266&qid=1661120153&sprefix=esp8266%2Caps%2C78&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzOVVBSVFXUDVZUlImZW5jcnlwdGVkSWQ9QTEwNDI0MTAxVzNEN1cxUkU1OTgxJmVuY3J5cHRlZEFkSWQ9QTA5NzQyMTEyN0JJQkszWUgyTFNZJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==) |
| [M3 x 12mm Hex Socket Screws Bolts](https://www.amazon.com/gp/product/B0143GZIHQ/) |

### **Software apps and online devices:**

| **Software apps and online devices:**                        |
| ------------------------------------------------------------ |
| [Arduino IDE](https://www.hackster.io/arduino/products/arduino-ide?ref=project-073834) |

### **Hand tools and fabrication machines:**

| **Hand tools and fabrication machines:** |
| ---------------------------------------- |
| Laser cutting service                    |

### Physical map:

The physucal maps are shown [here](https://github.com/Lalalaconcerto/Birdmood-Dissertation/tree/main/Bird%20emotion%20notification%20device/Physical%20map).

### **Enclosure:** 

The body of this device is made of wood. The screen of this device is made made from a piece of acrylic and a piece of black cardboard. You can use laser cutter to cut material. The design sketches are shown [here](https://github.com/Lalalaconcerto/Birdmood-Dissertation/tree/main/Bird%20emotion%20notification%20device/Enclosure%20design). 

### **Circuit Diagram**:

 The circuit diagram is shown [here](https://github.com/Lalalaconcerto/Birdmood-Dissertation/tree/main/Bird%20emotion%20notification%20device/Circuit%20Diagram%20LED).

 

 

 


