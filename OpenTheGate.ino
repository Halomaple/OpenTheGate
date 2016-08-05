#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer server(80);
void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) { // start ethernet using mac & DHCP
    Serial.println("Failed to configure Ethernet using DHCP");
  }
  delay(1000); // give the Ethernet shield a second to initialize
  server.begin();
  Serial.print("This IP address: ");
  IPAddress myIPAddress = Ethernet.localIP();
  Serial.print(myIPAddress);
  pinMode(6, OUTPUT);
}

void loop()
{
  EthernetClient client = server.available();
  if (client) {
    if (client.connected()) {
      if (client.available()) {
        digitalWrite(6, HIGH);  //open the door
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();
        client.print("<h1>Door is opened</h1>");//return this message to web page
      }
    }
    client.stop();  
    delay(15000);          //make sure the door stays opened before people get out
    digitalWrite(6, LOW);  //close the door
  }
}
