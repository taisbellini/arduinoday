#include <SoftwareSerial.h>
 
//RX pin 0, TX pin 1
SoftwareSerial esp8266(0, 1);
 
#define DEBUG true

int led1 = 11;
int led2 = 12;
 
void setup()
{
  Serial.begin(9600);
  esp8266.begin(19200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  sendData("AT+RST\r\n", 2000, DEBUG); // rst
  // Connect to Wireless Network
  sendData("AT+CWJAP=\"SSID\",\"PWD\"\r\n", 2000, DEBUG);
  delay(3000);
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
  // Show IP address
  sendData("AT+CIFSR\r\n", 1000, DEBUG);
  // Configure multiple connections
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);
  // Starts server in port 80
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);
}
 
void loop()
{
  // Check if ESP is sending data
  if (esp8266.available())
  {
    if (esp8266.find("+IPD,"))
    {
      delay(300);
      int connectionId = esp8266.read() - 48;
      
      //set cursor to the word "action=" and gets its value
      // 1 to turn on, 0 to turn off 
      esp8266.find("action=");
      int action = esp8266.read()-48;

      esp8266.find("pin=");
      int pin = (esp8266.read()-48)*10;
      pin += esp8266.read()-48;
      
      // displays in web page the status
      String webpage = "<head><meta http-equiv=""refresh"" content=""3"">";
      webpage += "</head><h1><u>ESP8266 - Web Server</u></h1>";
      webpage += "<body><h2>Action: ";
      webpage += action;
      webpage += "</h2>";
      webpage += "<h2>Pin: ";
      webpage += pin;
      webpage += "</h2></body>";
      
      //sends the action to defined pin
      digitalWrite(pin, action);
      //digitalWrite(led2, action);
      
      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      cipSend += "\r\n";
 
      sendData(cipSend, 1000, DEBUG);
      sendData(webpage, 1000, DEBUG);
 
      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
      closeCommand += "\r\n";
 
      sendData(closeCommand, 3000, DEBUG);
    }
  }
}
 
String sendData(String command, const int timeout, boolean debug)
{
  // Sending AT commands to ESP module
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read(); // read next char.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
