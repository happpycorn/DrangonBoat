// Import

#include <WiFi.h>
#include <stdio.h>
#include "config.h"
#include <WebServer.h>

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

LedcDefine LEDR{12} ;
LedcDefine LEDG{13} ;
LedcDefine LEDB{14} ;

LedcDefine headVer{25, 50, 16} ;
LedcDefine headHor{26, 50, 16} ;

LedcDefine tailObj{27, 50, 16} ;

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

// Main

void setup(){

    Serial.begin(115200) ;

    WiFi.mode(WIFI_AP) ;
    WiFi.softAP(ssid, pwd) ;

    Serial.println() ;
    Serial.print("AP IP address: ") ;
    Serial.println(WiFi.softAPIP()) ;

    server.on("/", []() {server.send(200, "text/html", indexHtml);}) ;
    server.on("/motor", motor) ;
    server.on("/led", led) ;
    server.on("/head", head) ;
    server.on("/tail", tail) ;

    server.begin() ;
    Serial.println("Start!") ;
}

void loop(){server.handleClient();}