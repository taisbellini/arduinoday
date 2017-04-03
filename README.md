# Arduino Day
The code and presentation to my talk at Arduino Day 2017 - PUCRS. Porto Alegre, RS - Brazil.

Slides [here](https://drive.google.com/open?id=1Zv64BGLlVMG9voAHS8ktJM0N80V8e-KP8HkfdoDnFE4 "Arduino na Web")

## Contents:

### Arduino Code:
**ESPWebServer.ino**

Code to start a web server in ESP8266 using an Arduino and ArduinoIDE.

*Notes*:

- Replace the SSID and PWD in line 20 `sendData("AT+CWJAP=\"SSID\",\"PWD\"\r\n", 2000, DEBUG);` by your Wifi credentials;

**NodeMCUServer.ino**

Code to start a web server in a NodeMCU using ArduinoIDE (based on the *HelloServer.ino* example from ESP8266 module).

*Notes*:

- Replace the SSID and PWD in lines 20 and 21 `const char* ssid = "SSID";` by your Wifi credentials;

### Webhook Code:
**app.js**

Code to place directly in Facebook Messenger Bot Webhook. This parses the facebook's request to make requests to the Arduino.

*Notes*:

- Replace the VERIFY TOKEN in line 18 `req.query['hub.verify_token'] === 'myhometoken')` by your webhook's verify token;
- Replace the ACESS TOKEN in line 135 ` qs: { access_token: 'ACESS TOKEN' },` by your page's access token;
- Replace the url in line 85 `url: 'https://c22a7e44.ngrok.io',` by your Arduino's web server url;


**apiaiapp.js**

Code to place in api.ai Fulfillment. This parses the api.ai's request to make requests to the Arduino.

*Notes*:

- Replace the url in line 36 `url: 'https://c22a7e44.ngrok.io',` by your Arduino's web server url;

**apiaiNodeMCUHook.js**

Code to place in api.ai Fulfillment if you are using the NodeMCU web server. 

*Notes*:

- Replace the url in line 42 `url: 'https://5bd82048.ngrok.io/${action}',` by your Arduino's web server url;


## References

[1](http://www.pridopia.co.uk/pi-doc/ESP8266ATCommandsSet.pdf) AT Commands

[2](http://blog.filipeflop.com/wireless/esp8266-arduino-tutorial.html) Tutorial to start a web server in an ESP8266 using Arduino (Portuguese)

[3](https://www.youtube.com/watch?v=xa6dJvd7wHg) Video with tutorial on how to receive data from ESP8266 and generate an action in Arduino (Portuguese)

[4](http://www.instructables.com/id/Control-ESP8266-Over-the-Internet-from-Anywhere/?ALLSTEPS) Tutorial to make ESP8266 availablle to public internet

[5](https://developers.facebook.com/docs/messenger-platform/guides/quick-start) Quick start to build a Messenger Bot

[6](https://api.ai) API.ai



