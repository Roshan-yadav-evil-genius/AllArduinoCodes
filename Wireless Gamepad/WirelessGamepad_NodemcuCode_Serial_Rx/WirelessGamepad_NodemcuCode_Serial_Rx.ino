#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

const char* ssid = "Server";
const char* pswd = "Testing1";
String homepage = "<!DOCTYPE html><html lang='en'> <head> <meta charset='UTF-8'/> <meta http-equiv='X-UA-Compatible' content='IE=edge'/> <meta name='viewport' content='width=device-width, initial-scale=1.0'/> <title>Homepage</title> <style>*{font-family: 'Lucida Sans Unicode'; margin: 0; padding: 0;}body{width: 100%; height: 100vh; overflow: hidden; background-color: rgb(233, 244, 255); display: flex; justify-content: center; align-items: center; flex-direction: column;}.datawrapper{background-color: white; border-radius: 8px; padding: 20px;}table, th, td{border: 1.5px solid rgb(201, 201, 201); border-collapse: collapse; text-align: left; padding: 10px 20px; width: 100%;}h1{font-weight: 900; margin: 10px 0 50px 0;}th{font-size: 20px; color: rgb(31, 175, 141);}td{font-weight: 600;}.status{display: flex; justify-content: space-between;}#statusled{width: 20px; height: 20px; background-color: rgb(255, 189, 189); box-shadow: 0 2px 6px 0 hsla(0, 0%, 0%, 0.2); border-radius: 50%;}.senddata{box-shadow: 0 2px 6px 0 hsla(0, 0%, 0%, 0.1); margin: 10px 0; padding: 10px 10px; border-radius: 5px; display: flex; flex-direction: column; background-color: rgb(239, 239, 239);}input{padding: 5px 10px; font-size: 17px; font-weight: 700; outline: none; border: 1px solid rgb(185, 185, 185); border-radius: 5px; margin: 20px 0; letter-spacing: 1px; color: rgb(77, 77, 77);}input:focus{border: 1px solid rgb(54, 178, 255);}input::placeholder{opacity: 0.5;}button{padding: 5px 10px; font-size: 17px; font-weight: 700; border-radius: 5px; border: none; background-color: rgb(69, 69, 69); color: white; letter-spacing: 1px;}button:hover{background-color: rgb(0, 0, 0);}button:active{box-shadow: 0 2px 6px 0 hsla(0, 0%, 0%, 0.5);}</style> </head> <body> <div class='datawrapper'> <div class='status'> <h1>Hlo Client Esp8266 is here</h1> <div id='statusled'></div></div><table> <thead> <tr> <th>Name</th> <th>Data</th> </tr></thead> <tbody id='recivedData'> </tbody> </table> <div class='senddata'> <input type='text' name='commands' placeholder='Send Data...'/> <input type='text' name='commands2' placeholder='Send Data...'/> <button id='submit''>Send</button> </div></div><script>const ws=new WebSocket('ws://' + window.location.hostname + ':81/'); const led=document.getElementById('statusled'); const table=document.getElementById('recivedData'); ws.onopen=(event)=>{console.log('Websocket connected successfully'); led.style.backgroundColor='rgb(189, 255, 189)';}; ws.onmessage=(event)=>{var RecivedData=JSON.parse(event.data); const row=(key,value)=>{return `<tr><td>${key}</td><td>${value}</td></tr>`;}; let allData=''; for (var key in RecivedData){if (RecivedData.hasOwnProperty(key)){allData+=row(key,RecivedData[key]);}}table.innerHTML=allData; console.log(RecivedData);}; ws.onerror=(event)=>{console.log('Websocket Error Occured ');}; ws.onclose=(event)=>{console.log('Websocket Closed'); led.style.backgroundColor='rgb(255, 189, 189)';}; document.getElementById('submit').addEventListener('click', ()=>{datas={}; document.querySelectorAll('input').forEach((input)=>{datas[input.name]=input.value}); console.log(datas); ws.send(JSON.stringify(datas))}); </script> </body></html>";


StaticJsonDocument<500> doctx;
StaticJsonDocument<500> docrx;

int a=0;
int loopDelay = 100;
unsigned long previousMillis = 0;

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void setup() {
  Serial.begin(9600);
//  Serial.setTimeout(100);
  Serial.println();
  // ---------------(Start) connect with wifi --------------------
  WiFi.begin(ssid, pswd);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());


  // ---------------(Start) URL Paths --------------------
  server.on("/", homepageView );

  server.begin(); //Start webserver
  webSocket.begin();//Start websocket
  webSocket.onEvent(webSocketEvent);


}

void loop() {

  unsigned long now = millis();

  server.handleClient();
  webSocket.loop();

  if (now - previousMillis > loopDelay) {
    Serial.println(a);
    if (Serial.available()>0) {
//      String data = Serial.readString();
      String data = Serial.readStringUntil('\n');
      data.trim();
      Serial.println(data);
      int datalength = data.length()+1;
      char arrayformat[datalength];
      data.toCharArray(arrayformat,datalength);
      webSocket.broadcastTXT(arrayformat);  //only accept charArray  of value
    }
    previousMillis = now;
    a = a+1;
  }

}
void homepageView() {
  Serial.println("Homepage Requested");
  server.send(200, "text/html", homepage);
}

// ---------------(Start) Websocket event handlers --------------------

//num -> Client number
//WStype_t -> type of event
//payload -> pointer unsigned integer
//size_t -> number of bytes

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    //--------------------Disconnect--------------------
    case WStype_DISCONNECTED:
      break;
    //--------------------Connect--------------------
    case WStype_CONNECTED:
      break;

    //--------------------OnMessage--------------------
    case WStype_TEXT:

      //--------Print all recived data--------
      for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
      }
      Serial.println();

      //--------deserialize recived data--------
      deserializeJson(docrx, payload);
      String cmd1 = docrx["cmd1"];
      String cmd2 = docrx["cmd2"];
      Serial.println("Recived : cmd1 :" + String(cmd1) + " cmd2 :" + String(cmd2));
      break;


  }

}
