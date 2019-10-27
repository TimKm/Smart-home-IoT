#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
#define wifi_ssid "timkm"
#define wifi_password "matrix123"
 
#define mqtt_server "m23.cloudmqtt.com"
#define mqtt_port 18858
#define mqtt_user "---"
#define mqtt_password "---"
 
#define in_topic "/light/in"
#define out_topic "/light/out"
// Replace by 2 if you aren't enable to use Serial Monitor... Don't forget to Rewire R1 to GPIO2!
#define in_led 2
 
WiFiClient espClient;
PubSubClient client;
 
void setup() {
    // initialize digital pin LED_BUILTIN as an output.
  pinMode(in_led, OUTPUT);
  digitalWrite(in_led, HIGH);
  
  Serial.begin(115200);
  delay(10);
  setup_wifi();
  client.setClient(espClient);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
 

}
 
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  //Serial.println();
 // Serial.print("Connecting to ");
 // Serial.println(wifi_ssid);
 
  WiFi.begin(wifi_ssid, wifi_password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  //  Serial.print(".");
  }
 
 // Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
}
 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
 //   Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
 //     Serial.println("connected");
    } else {
 //     Serial.print("failed, rc=");
  //    Serial.print(client.state());
  //    Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
 
void callback(char* topic, byte* payload, unsigned int length) {
// Serial.print("Message arrived [");
// Serial.print(topic);
// Serial.print("] ");
 for (int i = 0; i < length; i++) {
  char receivedChar = (char)payload[i];
 // Serial.print(receivedChar);
  if (receivedChar == '0')
  Serial.println(0);
  // digitalWrite(in_led, LOW);
  if (receivedChar == '1')
  // digitalWrite(in_led, HIGH);
  Serial.println(1);
  if (receivedChar == '2')
  Serial.println(2);
  if (receivedChar == '3')
  Serial.println(3);
  if (receivedChar == '4')
  Serial.println(4);
  if (receivedChar == '5')
  Serial.println(5);
  if (receivedChar == '6')
  Serial.println(6);
    if (receivedChar == '7')
  Serial.println(7);
    if (receivedChar == '8')
  Serial.println(8);
    if (receivedChar == '9')
  Serial.println(9);
 }
// Serial.println();
}
 
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // Publishes a random 0 or 1 like someone switching off and on randomly (random(2))
 // client.publish(out_topic, String(random(2)).c_str(), true);
 // delay(5000);
  client.subscribe(in_topic);
  delay(10);
}
