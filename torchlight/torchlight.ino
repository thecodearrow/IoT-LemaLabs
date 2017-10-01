/*IoT over Intranet
Devices involved-- PC/Laptop, NodeMCU, Smartphone 
The devices are all expected to be connected to NodeMCU 
Arduino code that uses NodeMCU ESP8266 to control its LED as per the user's choice on http://192.168.4.1/led 
Updates the same on http://192.168.4.1/check 
The android application then uses the text on http://192.168.4.1/check to turn on/off the user's torchlight accordingly.
*/

#include<ESP8266WebServer.h> //ESP Webserver library

ESP8266WebServer server; //Declaring ESP8266WebServer as server

//Access point credentials
const char username[]="prashanth_team49";
const char password[]="root1234";

int val;
#define pin 16

void setup() {
  pinMode(pin,OUTPUT); //Making pin 16 as OUTPUT pin
  Serial.begin(115200); //Baud rate
  WiFi.softAP(username,password); //Setting up access point with credentials
  IPAddress myip=WiFi.softAPIP(); //Getting IP Address
  Serial.print("AP IP address ");
  Serial.println(myip); //Printing IP Address to Serial Monitor
  server.begin(); //Starting the server
  server.on("/led",led);  //Calling LED function on http://192.168.4.1/led
  server.on("/check",check); //Calling check function on http://192.168.4.1/check
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient(); //Checks for requests from clients continuously 
}

void led(){
  
  String myhtml="<!DOCTYPE html><html><head><title>Prashanth IoT</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><link href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" rel=\"stylesheet\" media=\"screen\"></head><body  style=\"background-color: #20B2AA;\"><div style=\"width:200px;height:200px;position:absolute; top:0;bottom:0;right:0;left:0; margin:auto;\"><h1><center>IoT</center></h1><form><center><button class=\"btn btn-large btn-primary\" type=\"submit\" style=\"background-color: green;font-weight: bold\" name=\"state\" value=\"0\">LED ON</button>&nbsp;&nbsp;&nbsp;<button class=\"btn btn-large btn-primary\" style=\"background-color: red; font-weight: bold\" type=\"submit\" name=\"state\" value=\"1\">LED OFF</button></center></form></div><script src=\"http://code.jquery.com/jquery.js\"></script></body></html>";
  server.send(200,"text/html",myhtml); //Send myhtml as response 
  if(server.arg("state")=="1"){ 
    digitalWrite(16,HIGH); //LED OFF
    val=0; //for torchlight off
    }
  else{
    digitalWrite(16,LOW); //LED ON
   val=1; //for torchlight on
    }
  }
void check(){
//This function's response assists the android app to control the phone's torchlight accordingly
  if(val==0){
    server.send(200, "text/html", "torchoff"); //sending as response
    
    }
   else{
    server.send(200,"text/html","torchon"); //sending as response
    }
    
  
  }
