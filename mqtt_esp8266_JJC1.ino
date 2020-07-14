
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

String command; // serial input capture string
String clientName;

uint32_t runTime = -99999;

//--topics
String input1 = "emon/emonpi/power2";
String input2 = "emon/emonpi/t1";
String input3 = "";
String input4 = "emon/emonpi/power2";
String input5 = "emon/emonpi/power1";
String input6 = "";

// Update these with values suitable for your network.

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "IP of the EmonPi";
const int mqttPort = 1883;
const char* mqttUser = "emonpi";
const char* mqttPassword = "emonpimqtt2016";

WiFiClient espClientLCD;
PubSubClient client(espClientLCD);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(19200);
  setup_wifi();
  client.setServer(mqtt_server, mqttPort);
  client.setCallback(callback);
 
}

void setup_wifi() {
WiFi.hostname("espTFTScreen");
  delay(10);
WiFi.mode(WIFI_STA);   
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  clientName += "esp8266-";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += macToStr(mac);
  clientName += "-";
  clientName += String(micros() & 0xff, 16);
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(clientName);
}

void callback(char* topic, byte* payload, unsigned int length) {


if (input1 == topic){
 String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
  Serial.print("cmd_1("); Serial.print(inString); Serial.println(")");
  }
if (input2 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);  
  }
   Serial.print("cmd_2("); Serial.print(inString); Serial.println(")");
} 
 if (input3 == topic){
  String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);
  }
   Serial.print("cmd_3("); Serial.print(inString); Serial.println(")");
  }
if (input4 == topic){
 String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]); 
  }
  Serial.print("cmd_4("); Serial.print(inString); Serial.println(")");  
} 
if (input5 == topic){
  String inString = "";
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);     
  }
 Serial.print("cmd_5("); Serial.print(inString); Serial.println(")"); 
} 
 
if (input6 == topic){
 String inString = "";
  //scan++;
  for (int i=0;i<length;i++) {
     inString +=  ((char)payload[i]);   
  }
  Serial.print("cmd_6("); Serial.print(inString); Serial.println(")");
  }

/// if adding more sensor strings edit publish or remove publish and error commands below for switches 

 
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}
String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
     
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe maxium 7 other wise issues arise
      client.subscribe("emon/#");
    
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(2000);
    }
  }
}
void loop() {
if(WiFi.status() != WL_CONNECTED) {setup_wifi();}
  if (!client.connected()) {
    reconnect();
 }
  client.loop();

   if(Serial.available())
   {
      char c = Serial.read();
    
      if (c == ')')
      {
       
        parseCommand(command);
        
        command="";
      }
      else
      {
       command += c;
      }
  }

}


void parseCommand(String com)
{

//--com variables  
char test[5];
  String part1;
  String part2;
  
  part1 = com.substring(6, com.indexOf("("));
  
  part2 = com.substring(com.indexOf("(")+1);
  


     }
    