//#include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

const char* ssid     = "Oneplus";
const char* password = "11111111";
const char* host = "192.168.43.164";

const int redPin = 4; //  ~D2

void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(redPin, OUTPUT);
  
  analogWrite(redPin, 280);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}
double analogValue = 0.0;
double analogVolts = 0.0;
unsigned long timeHolder = 0;
void loop() {
  analogValue = analogRead(A0); // read the analog signal
   analogVolts = (analogValue * 3.08) / 1024;
    int chartValue=0;
    chartValue = (analogValue * 100) / 400;
     chartValue = 100 - chartValue;
    if (chartValue <= 25) {  // 0-25 red led off

      analogWrite(redPin, 0);

    } else if (chartValue > 25 ) // > 25  red led on
    {

      analogWrite(redPin, 1000);
    }

     Serial.println("Moisture Value"+chartValue);
      Serial.print("connecting to ");
  Serial.println(host);

 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   HTTPClient http;    //Declare object of class HTTPClient
   http.begin("http://192.168.43.164:80/API/insert.php");      //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  
   String reqBody = "moist="+ String(chartValue)  ;
   int httpCode = http.POST(reqBody);   //Send the request
   String payload = http.getString();                  //Get the response payload

   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload

   http.end();  //Close connection

 }else{

    Serial.println("Error in WiFi connection");   

 }
 Serial.println("closing connection");
  delay(3000);
  }

 
