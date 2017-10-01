/*Internet of Things*/
/*Arduino code that uses NodeMCU ESP8266 to control its LED as per the user's choice on http://192.168.4.1/prashanth */

#include<ESP8266WebServer.h> //ESP Webserver library

ESP8266WebServer server; //Declaring ESP8266WebServer as server

//Access point credentials 
const char username[]="prashanth_team49";
const char password[]="root1234";

#define pin 16 //Declaring 16 as pin

void setup() {

  pinMode(pin,OUTPUT); //Initialising PIN 16 as OUTPUT
  Serial.begin(115200); //Baud rate
  WiFi.softAP(username,password); //Setting up access point credentials
  IPAddress myip=WiFi.softAPIP(); //Getting IP Address
  Serial.print("AP IP address");
  Serial.println(myip); //Printing IP address on serial monitor
  server.begin(); //starts the server
  server.on("/prashanth",led); //Calling LED function when http://192.168.4.1/prashanth is requested
}

void loop() {
  // put your main code here, to run repeatedly:
 server.handleClient(); //Checks for requests from clients from clients continuously
}

void led(){
  
  String myhtml="<!DOCTYPE html><html><head><title>Prashanth IoT</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><link href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" rel=\"stylesheet\" media=\"screen\"></head><body  style=\"background-color: #FFC300  ;\"><div style=\"width:200px;height:200px;position:absolute; top:0;bottom:0;right:0;left:0; margin:auto;\"><h1><center>IoT</center></h1><form><center><button class=\"btn btn-large btn-primary\" type=\"submit\" style=\"background-color: green;font-weight: bold\" name=\"state\" value=\"0\">LED ON</button>&nbsp;&nbsp;&nbsp;<button class=\"btn btn-large btn-primary\" style=\"background-color: red; font-weight: bold\" type=\"submit\" name=\"state\" value=\"1\">LED OFF</button></center></form></div><script src=\"http://code.jquery.com/jquery.js\"></script></body></html>";
  server.send(200,"text/html",myhtml);//Sending html response
  //Based on user's click response
  if(server.arg("state")=="1"){
    digitalWrite(pin,HIGH); //Turn OFF LED
    }
  else{

   digitalWrite(pin,LOW); //Turn ON LED
    }
}
  
