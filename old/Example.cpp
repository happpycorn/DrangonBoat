// // Import

// #include "BluetoothSerial.h"

// // Const

// BluetoothSerial BT ;

// const char* boatName = "Myboat" ;

// const int LEDPinR = 0 ;
// const int LEDPinG = 0 ;
// const int LEDPinB = 0 ;

// const int motorPinFL = 0 ;
// const int motorPinBL = 0 ;
// const int motorPinFR = 0 ;
// const int motorPinBR = 0 ;

// const int freq = 50 ;
// const int resolution = 16 ;

// const int headPin = 0 ;
// const int headMinValue = 0 ;
// const int headMaxValue = 0 ;

// const int tailPin = 0 ;
// const int tailRightValue = 0 ;
// const int tailMiddleValue = 0 ;
// const int tailLeftValue = 0 ;

// // Set

// void setup() {

//     BT.begin(boatName) ;

//     pinMode(LEDPinR, OUTPUT) ;
//     pinMode(LEDPinG, OUTPUT) ;
//     pinMode(LEDPinB, OUTPUT) ;

//     pinMode(motorPinFL, OUTPUT) ;
//     pinMode(motorPinBL, OUTPUT) ;
//     pinMode(motorPinFR, OUTPUT) ;
//     pinMode(motorPinBR, OUTPUT) ;

//     ledcSetup(headPin, freq, resolution) ;
//     ledcAttachPin(headPin, headPin) ;

//     ledcSetup(tailPin, freq, resolution) ;
//     ledcAttachPin(tailPin, headPin) ;
    
//     digitalWrite(motorPinFL, LOW) ;
//     digitalWrite(motorPinBL, LOW) ;
//     digitalWrite(motorPinFR, LOW) ;
//     digitalWrite(motorPinBR, LOW) ;
    
//     ledcWrite(headPin, headMinValue) ;
//     ledcWrite(tailPin, tailMiddleValue) ;
// }

// // Main

// void loop() {
    
//     if (!BT.available()){
        
//         return ;
//     }

//     switch (BT.read())
//     {
    
//     // Motor

//     case 'F':
//         digitalWrite(motorPinFL, HIGH) ;
//         digitalWrite(motorPinBL, LOW) ;
//         digitalWrite(motorPinFR, HIGH) ;
//         digitalWrite(motorPinBR, LOW) ;
//         break;

//     case 'B':
//         digitalWrite(motorPinFL, LOW) ;
//         digitalWrite(motorPinBL, HIGH) ;
//         digitalWrite(motorPinFR, LOW) ;
//         digitalWrite(motorPinBR, HIGH) ;
//         break;

//     case 'R':
//         digitalWrite(motorPinFL, HIGH) ;
//         digitalWrite(motorPinBL, LOW) ;
//         digitalWrite(motorPinFR, LOW) ;
//         digitalWrite(motorPinBR, HIGH) ;
//         break;

//     case 'L':
//         digitalWrite(motorPinFL, LOW) ;
//         digitalWrite(motorPinBL, HIGH) ;
//         digitalWrite(motorPinFR, HIGH) ;
//         digitalWrite(motorPinBR, LOW) ;
//         break;

//     case 'S':
//         digitalWrite(motorPinFL, LOW) ;
//         digitalWrite(motorPinBL, LOW) ;
//         digitalWrite(motorPinFR, LOW) ;
//         digitalWrite(motorPinBR, LOW) ;
//         break;
    
//     // Head

//     case 'C':
//         ledcWrite(headPin, headMinValue) ;
//         break ;

//     case 'O':
//         ledcWrite(headPin, headMaxValue) ;
//         break ;
    
//     // Tail

//     case 'r':
//         ledcWrite(tailPin, tailRightValue) ;
//         break ;

//     case 'm':
//         ledcWrite(tailPin, tailMiddleValue) ;
//         break ;

//     case 'l':
//         ledcWrite(tailPin, tailLeftValue) ;
//         break ;
    
//     // LED

//     case 'i': // r
//         digitalWrite(LEDPinR, HIGH) ;
//         digitalWrite(LEDPinG, LOW) ;
//         digitalWrite(LEDPinB, LOW) ;
//         break;

//     case 'j': // g
//         digitalWrite(LEDPinR, LOW) ;
//         digitalWrite(LEDPinG, HIGH) ;
//         digitalWrite(LEDPinB, LOW) ;
//         break;

//     case 'k': // b
//         digitalWrite(LEDPinR, LOW) ;
//         digitalWrite(LEDPinG, LOW) ;
//         digitalWrite(LEDPinB, HIGH) ;
//         break;

//     case 'n': // None
//         digitalWrite(LEDPinR, LOW) ;
//         digitalWrite(LEDPinG, LOW) ;
//         digitalWrite(LEDPinB, LOW) ;
//         break;

//     default:
//         break;
//     }
// }