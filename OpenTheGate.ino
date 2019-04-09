#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer server(80);
void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) { // start ethernet using mac & DHCP
    Serial.println("Failed to configure Ethernet using DHCP");
  }
  delay(2000); // give the Ethernet shield a second to initialize
  server.begin();
  Serial.print("This IP address: ");
  Serial.print(Ethernet.localIP());
  pinMode(6, OUTPUT);
}

void loop()
{
  EthernetClient client = server.available();
  if (client) {
    if (client.connected()) {
      if (client.available()) {
        delay(100);
        digitalWrite(6, HIGH);  //open the door
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();
        client.println("<!DOCTYPE html><html><head>");
        client.println("<link rel=\"shortcut icon\" type=\"image/x-icon\" href=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAIAAACQd1PeAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAAAAMSURBVBhXY/j//z8ABf4C/qc1gYQAAAAASUVORK5CYII=\"/>");
        client.println("<link rel=\"apple-touch-icon\" href=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAIAAACQd1PeAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAAAAMSURBVBhXY/j//z8ABf4C/qc1gYQAAAAASUVORK5CYII=\">");
        client.println("</head><body><h1>Door is opened.</h1></body></html>");
      }
    }
    client.stop();
    delay(100);
    digitalWrite(6, LOW);  //close the door
  }
}
