import os
import sys, getopt
import signal
import time
from edge_impulse_linux.audio import AudioImpulseRunner

import random
import time
from paho.mqtt import client as mqtt_client

# Training model 

runner = None

def signal_handler(sig, frame):
    print('Interrupted')
    if (runner):
        runner.stop()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

def help():
    print('python classify.py <path_to_model.eim> <audio_device_ID, optional>' )

# MQTT 
broker = YOUR_MQTT_BROKER_NAME
port = YOUR_MQTT_PORT
topic = "student/ucfnxla/birdmood/"
# Generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 1000)}'
username = YOUR_USERNAME
password = YOUR_PASSWORD



def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)
           

    client = mqtt_client.Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client
    print('successfully mqtt')




def main(argv):
    try:
        opts, args = getopt.getopt(argv, "h", ["--help"])
    except getopt.GetoptError:
        help()
        sys.exit(2)

    for opt, arg in opts:
        if opt in ('-h', '--help'):
            help()
            sys.exit()

    if len(args) == 0:
        help()
        sys.exit(2)

    model = args[0]

    dir_path = os.path.dirname(os.path.realpath(__file__))
    modelfile = os.path.join(dir_path, model)

    # mqtt connect
    client = connect_mqtt()

    with AudioImpulseRunner(modelfile) as runner:
        try:
            model_info = runner.init()
            labels = model_info['model_parameters']['labels']
            print('Loaded runner for "' + model_info['project']['owner'] + ' / ' + model_info['project']['name'] + '"')

            #Let the library choose an audio interface suitable for this model, or pass device ID parameter to manually select a specific audio interface
            selected_device_id = None
            if len(args) >= 2:
                selected_device_id=int(args[1])
                print("Device ID "+ str(selected_device_id) + " has been provided as an argument.")

            for res, audio in runner.classifier(device_id=selected_device_id):
                print('Result (%d ms.) ' % (res['timing']['dsp'] + res['timing']['classification']), end='\n')
                for label in labels:
                    score = res['result']['classification'][label]
                    print('%s: %.2f\t' % (label, score), end='')
                    # time.sleep(0.5)
                    # publish the training results to MQTT
                    client.publish(topic + label, score)
                    # change the data pulished frequency 
                    # if label == 'unhappy chirp' :
                    #     time.sleep(5)
                
                    
                   
                print('', flush=True)

   
        finally:
            if (runner):
                runner.stop()



              
# def run():
    

   


if __name__ == '__main__':
   main(sys.argv[1:])






