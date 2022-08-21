#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>

const char* ssid     = "YOUR_SSID";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "YPUR_PASSWORD";     // The password of the Wi-Fi network

// MQTT Broker
const char *mqtt_broker = "MQTT_BROKER";
const char *topic = "YOUR_TOPIC";
const char *mqtt_username = "YPUR_USERNAME";
const char *mqtt_password = "YPUR_PASSWORD";
const int mqtt_port = YPUR_PORT;

WiFiClient espClient;
PubSubClient client(espClient);


Adafruit_NeoPixel pixels(64, 5, NEO_GRB + NEO_KHZ800);

//Define diferent labels
float background;
float unhappy_chirp;
float single_tweet;
float happy_chirp;
float relax_chirp;




void setup() {
  //pixels begin
  pixels.begin();
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  while (!client.connected()) {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  // publish and subscribe
  Serial.println("ESP8266 AS SUBSCRIBER");
  Serial.println("Subscribing topic test:");
  client.subscribe("student/ucfnxla/birdmood/#");//topic name="abc"

}

//Reconnect function for MQTT
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
      client.subscribe("SUBSCRIBE_TOPIC");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

//callback function for MQTT
void callback(char *topic, byte *payload, unsigned int length) {
  payload[length] = '\0';
  
  // Convert topic format from char to string for subsequent editing
  String strTopic = String((char*)topic);


  Serial.print("Message received in topic: ");
  Serial.print(topic);

  char value[length + 1];

  //  Serial.print("   length is:");
  //  Serial.println(length);
  Serial.print("Data recieved from Broker");
//  
  for (int i = 0; i < length; i++) {
    value[i] = (char) payload[i];

    Serial.print((char) payload[i]);
  }

  Serial.println();
  value[length] = NULL;
  
  //  Serial.println(value);


  //classify the value and obtain data from each topic
  if (strTopic == "student/ucfnxla/birdmood/background") {
    background = (float)strtod(value, NULL);
    Serial.println(background);
  }
  else if (strTopic == "student/ucfnxla/birdmood/happy chirp") {
    happy_chirp = (float)strtod(value, NULL);
    Serial.println(happy_chirp);
  }
  else if (strTopic == "student/ucfnxla/birdmood/relax") {
    relax_chirp = (float)strtod(value, NULL);
    Serial.println(relax_chirp);
  }
  else if (strTopic == "student/ucfnxla/birdmood/single tweet") {
    single_tweet = (float)strtod(value, NULL);
    Serial.println(single_tweet);
  }
  else if (strTopic == "student/ucfnxla/birdmood/unhappy chirp") {
    unhappy_chirp = (float)strtod(value, NULL);
    Serial.println(unhappy_chirp);
  }



  Serial.println("-----------------------");




}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();



  // LED control based on dofferent training results
  
  if (unhappy_chirp > 0.7) {
    Serial.println("I am unhappy");
    for (int i = 0; i <= 7; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 102, 204));
      pixels.show();
    }
    for (int i = 56; i <= 63; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 128));
      pixels.show();
    }
    delay(500);
    pixels.clear();
  }
  else if (relax_chirp > 0.7) {
    Serial.println("I am relaxed");
    for (int i = 0; i <= 7; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 102, 204));
      pixels.show();
    }
    for (int i = 56; i <= 63; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 204, 0));
      pixels.show();
    }
    delay(500);
    pixels.clear();
  }
  else if (happy_chirp > 0.7) {
    Serial.println("I am happy");
    for (int i = 0; i <= 7; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 102, 204));
      pixels.show();
    }
    for (int i = 8; i <= 23; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 0));
      pixels.show();
    }
    delay(500);
    pixels.clear();
  }
  else if (single_tweet > 0.7) {
    Serial.println("I am contactting");
    for (int i = 0; i <= 7; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 102, 204));
      pixels.show();
    }
    for (int i = 24; i <= 39; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 102, 178));
      pixels.show();
    }
    delay(500);
    pixels.clear();
  }
  else {
    for (int i = 0; i <= 63; i++) {
      pixels.setPixelColor(i, pixels.Color(10, 10, 10));
      pixels.show();
    }
    delay(500);
    pixels.clear();
  }




}
