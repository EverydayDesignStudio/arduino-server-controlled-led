#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;       // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(801);     // Create a webserver object that listens for HTTP request on port 801

int count = 0;
int isOn = 0;

void handleRoot();              // function prototypes for HTTP handlers
void handleLED();
void handleNotFound();

void setup(void){
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  pinMode(D7, OUTPUT);

  wifiMulti.addAP("WIFI NETWORK", "PASSWORD");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("WIFI NETWORK", "PASSWORD");
  wifiMulti.addAP("WIFI NETWORK", "PASSWORD");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED", HTTP_POST, handleLED);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();                    // Listen for HTTP requests from clients
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  String l1 = "";
  if (isOn == 0) {
    l1 = "<h1>Jordan's LED is off &#x26AA</h1>";
  } else {
    l1 = "<h1>Jordan's LED is ON &#x1F534</h1>";
  }
  
  String l2 = "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>";
  String l3 = "<div>It has been toggled " + String(count) + " times by Jordan's friends.</div>";

  String html = "<center>" + l1 + l2 + l3 + "</center>";
  server.send(200, "text/html", html);
}

void handleLED() {                          // If a POST request is made to URI /LED
  count++;                                  // Update the count
  digitalWrite(D7,!digitalRead(D7));        // Change the state of the LED
  isOn = digitalRead(D7);
  
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
