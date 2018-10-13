#include <SPI.h>
#include <Ethernet.h>
#include <DHT11.h>

DHT11 dht11(A0);

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 20); 
EthernetServer server(80);

String HTTP_req;

void setup() {
  
  Ethernet.begin(mac, ip);  
  server.begin();
  Serial.begin(9600);

  Serial.print("El servidor está en: ");
  Serial.println(Ethernet.localIP());

  HTTP_req = "";
}

void loop() {
  
  EthernetClient client = server.available();

  if(client) {

    boolean currentLineIsBlank = true;
    
    while(client.connected()) {
      
      if (client.available()) {
        
        char c = client.read();
        HTTP_req += c;
        
        if(c == '\n' && currentLineIsBlank) {

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: keep-alive");
          client.println();

          if (HTTP_req.indexOf("ajax_switch") > -1) {
            
            getValues(client);
            
          } else {
            
            drawPage(client);
          }
          
          Serial.print(HTTP_req);
          HTTP_req = "";
          break;
        }
        
        if (c == '\n') {
          
          currentLineIsBlank = true;
          
        }  else if (c != '\r') {
           
          currentLineIsBlank = false;
        }
      }
    }
    
    delay(1);
    client.stop();
  }
}

void drawPage(EthernetClient client) {

  client.println("<!doctype html><head>");
  client.println("<title>Temperatura y Humedad</title>");
  client.println("<script>");
  client.println("function GetValues() {");
  client.println("let nocache = \"&nocache=\" + Math.random() * 1000000;");
  client.println("let request = new XMLHttpRequest();");
  client.println("request.onreadystatechange = function() {");
  client.println("if(this.readyState === 4) {");
  client.println("if(this.status === 200) {");
  client.println("if(this.responseText != null) {");
  client.println("let values = this.responseText.split(\" \");");
  client.println("document.getElementById('temperatura').innerHTML = values[0];");
  client.println("document.getElementById('humedad').innerHTML = values[1];");
  client.println("}}}};");
  client.println("request.open(\"GET\", \"ajax_switch\" + nocache, true);");
  client.println("request.send(null);");
  client.println("setTimeout(GetValues, 1000);}");
  client.println("</script>");
  client.println("</head>");
  client.println("<body onload='GetValues()'>");
  client.println("<div style='text-align: center'>");
  client.println("<h2>Temperatura</h2>");
  client.println("<p id='temperatura'>0</p>");
  client.println("<h2>Humedad</h2>");
  client.println("<p id='humedad'>0</p>");
  client.println("</div></body></html>");
}

void getValues(EthernetClient client) {

  int err;
  float temp, hum;
  
  if((err = dht11.read(hum, temp)) == 0) {
    
    client.print(String((int)temp) + "°");
    client.print(" ");
    client.print(String((int)hum));
  }

  delay(1000);
}
