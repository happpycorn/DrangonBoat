// Import

#include <WiFi.h>
#include <stdio.h>
#include <WebServer.h>
#include <FS.h>
#include <SPIFFS.h>

// Defind class

class LedcDefine {
private:

    int pin ;

public:

    LedcDefine(int pin, int freq = 5000, int resolution = 8)
        : pin(pin){
        ledcAttach(pin, freq, resolution) ;
    }

    void write(int duty){
      ledcWrite(pin, duty > 0 ? duty : 0) ;
    }
} ;

// Defind obj

const char* ssid = "Fhehs-DragonBoat" ;
const char* pwd = "00000000" ;

WebServer server(80) ;

LedcDefine motorFL{32} ;
LedcDefine motorBL{33} ;
LedcDefine motorFR{22} ;
LedcDefine motorBR{23} ;

LedcDefine LEDR{25} ;
LedcDefine LEDG{26} ;
LedcDefine LEDB{27} ;

LedcDefine headVer{11, 50, 16} ;
LedcDefine headHor{13, 50, 16} ;

LedcDefine tailObj{12, 50, 16} ;

// Defind function

void motor(){

    float left, right ;
    sscanf(server.arg("duty").c_str(), "%f,%f", &left, &right) ;

    motorFL.write(left) ;
    motorBL.write(-left) ;
    motorFR.write(right) ;
    motorBR.write(-right) ;
}

void led(){
    
    float R, G, B ;
    sscanf(server.arg("duty").c_str(), "%f,%f,%f", &R, &G, &B) ;

    LEDR.write(R) ;
    LEDG.write(G) ;
    LEDB.write(B) ;
}

void head(){

    float ver, hor ;
    sscanf(server.arg("duty").c_str(), "%f,%f", &ver, &hor) ;

    headVer.write(ver) ;
    headHor.write(hor) ;
}

void tail(){

    float duty = server.arg("duty").toInt() ;

    tailObj.write(duty) ;
}

// Load file

void handleRoot() {
  File file = SPIFFS.open("/index.html", FILE_READ) ;
  if (!file) {
    server.send(404, "text/plain", "File Not Found") ;
    return;
  }

  String htmlContent;
  while (file.available()) {
    htmlContent += char(file.read()) ;
  }
  file.close() ;
  
  server.send(200, "text/html", htmlContent) ;
}

void handleStyle() {
    File file = SPIFFS.open("/style.css", "r");
    if (!file) {
        server.send(404, "text/plain", "File Not Found");
        return;
    }
    server.streamFile(file, "text/css");
    file.close();
}

void handleJQuery() {
    File file = SPIFFS.open("/jquery-3.6.0.min.js", "r");
    if (!file) {
        server.send(404, "text/plain", "File Not Found");
        return;
    }
    server.streamFile(file, "application/javascript");
    file.close();
}

void handleCreateJS() {
    File file = SPIFFS.open("/createjs.min.js", "r");
    if (!file) {
        server.send(404, "text/plain", "File Not Found");
        return;
    }
    server.streamFile(file, "application/javascript");
    file.close();
}

void handleHammerJS() {
    File file = SPIFFS.open("/hammer.min.js", "r");
    if (!file) {
        server.send(404, "text/plain", "File Not Found");
        return;
    }
    server.streamFile(file, "application/javascript");
    file.close();
}

void handleScript() {
    File file = SPIFFS.open("/script.js", "r");
    if (!file) {
        server.send(404, "text/plain", "File Not Found");
        return;
    }
    server.streamFile(file, "application/javascript");
    file.close();
}

// Main

void setup(){

    Serial.begin(115200) ;
    Serial.println("START") ;

    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed") ;
        return ;
    }

    WiFi.mode(WIFI_AP) ;
    WiFi.softAP(ssid, pwd) ;

    Serial.println() ;
    Serial.print("AP IP address: ") ;
    Serial.println(WiFi.softAPIP()) ;

    server.on("/", handleRoot) ;
    server.on("/style.css", handleStyle) ;
    server.on("/jquery-3.6.0.min.js", handleJQuery) ;
    server.on("/createjs.min.js", handleCreateJS) ;
    server.on("/hammer.min.js", handleHammerJS) ;
    server.on("/script.js", handleScript) ;

    server.on("/motor", motor) ;
    server.on("/led", led) ;
    server.on("/head", head) ;
    server.on("/tail", tail) ;

    server.begin() ;
    Serial.println("Start!") ;
}

void loop(){server.handleClient();}