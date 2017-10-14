#include<ESP8266WiFi.h>
#include<Adafruit_MQTT_Client.h>

#define ldr A0 //analog 0
#define wifi "redmi"
#define password "root1234"

#define server "io.adafruit.com" 
#define port 1883 //Adafruit server port 
#define username "prashanth_vaidya"
#define key "26588cde15564f13befe707d64b90028" //AIO Key from io.adafruit.com

WiFiClient esp; //NodeMCU is the client here
Adafruit_MQTT_Client mqtt(&esp,server,port,username,key); //connecting client to server

Adafruit_MQTT_Publish feed=Adafruit_MQTT_Publish(&mqtt,username"/feeds/photo-cell"); //giving location to publish data

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("Adafruit MQTT demo");
  Serial.println(wifi);
  WiFi.begin(wifi,password); //Connects client to internet
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    
    }

   Serial.println("WiFi connected");
   Serial.println("IP Address: ");
   Serial.println(WiFi.localIP()); //Prints the IP address
   Serial.println("Connecting to MQTT");
  while(mqtt.connect())//while mqtt is connected 
  {
    Serial.print(".");
    
    }

}

void loop() {
  // put your main code here, to run repeatedly:

  if(mqtt.connected()){
    int data=analogRead(ldr);
    Serial.print("nSending LDR val ");
    Serial.print(data);
    Serial.print("...");
    if(feed.publish(data)){

      Serial.print("Success");
      
      }
    else
    {
      
      Serial.print("Failure");}
    
    }

delay(1300); //Prevents overflow error
}
