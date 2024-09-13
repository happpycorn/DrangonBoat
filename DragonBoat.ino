// Import

#include <WiFi.h>
#include <stdio.h>
#include "config.h"
#include <WebServer.h>

const char* ssid_AP = "Esp32Cam_car" ;
const char* pwd_AP = "00000000" ;

WebServer server(80) ;

class LedcDefine {
private:

    int pin ;
    int freq ;
    int resolution ;

public:

    LedcDefine(int pin, int freq = 5000, int resolution = 8)
        : pin(pin), freq(freq), resolution(resolution){
        ledcSetup(pin, freq, resolution) ;
        ledcAttachPin(pin, pin) ;
    }

    void write(int duty){
      ledcWrite(pin, duty > 0 ? duty : 0) ;
    }
} ;

void motor() ;
LedcDefine motorFL{32} ;
LedcDefine motorBL{33} ;
LedcDefine motorFR{34} ;
LedcDefine motorBR{35} ;

void led() ;
LedcDefine LEDR{12} ;
LedcDefine LEDG{13} ;
LedcDefine LEDB{14} ;

void head() ;
LedcDefine headVer{25, 50, 16} ;
LedcDefine headHor{26, 50, 16} ;

void tail() ;
LedcDefine tailObj{27, 50, 16} ;

void setup(){

    Serial.begin(115200) ;

    WiFi.mode(WIFI_AP) ;
    WiFi.softAP(ssid_AP, pwd_AP) ;

    Serial.println() ;
    Serial.print("AP IP address: ") ;
    Serial.println(WiFi.softAPIP()) ;

    server.on("/", []() {server.send(200, "text/html", indexHtml);}) ;
    server.on("/motor", motor) ;
    server.on("/led", led) ;
    server.on("/head", head) ;
    server.on("/tail", tail) ;

}

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

void loop(){server.handleClient();}