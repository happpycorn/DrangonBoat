// #include "BluetoothSerial.h"

// BluetoothSerial BT ;

// // Const

// const char* boatName = "Myboat" ;

// const int headpin = 0 ;
// const int headMinAngle = 0 ;
// const int headMaxAngle = 180 ;
// const int headOrginAngle = 0 ;

// const int tailpin = 0 ;
// const int tailMinAngle = 0 ;
// const int tailMaxAngle = 180 ;
// const int tailOrginAngle = 0 ;

// const int tailLeft = 0 ;
// const int tailmidd = 90 ;
// const int tailrigh = 180 ;

// // Class

// class LEDController {
// private:

//     const int PinR = 12 ;
//     const int PinG = 13 ;
//     const int PinB = 14 ;

// public:

//     LEDController(){

//         pinMode(PinR, OUTPUT) ;
//         pinMode(PinG, OUTPUT) ;
//         pinMode(PinB, OUTPUT) ;
//     }

//     void setColor(bool r = false, bool g = false, bool b = false){

//         digitalWrite(PinR, r) ;
//         digitalWrite(PinG, g) ;
//         digitalWrite(PinB, b) ;
//     }
// } ;

// class MotorController {
// private:

//     const int motorPinFL = 25 ;
//     const int motorPinBL = 26 ;
//     const int motorPinFR = 32 ;
//     const int motorPinBR = 33 ;

// public:

//     MotorController(){

//         pinMode(motorPinFL, OUTPUT) ;
//         pinMode(motorPinBL, OUTPUT) ;
//         pinMode(motorPinFR, OUTPUT) ;
//         pinMode(motorPinBR, OUTPUT) ;
//     }

//     void stop(){

//         digitalWrite(motorPinFL, LOW) ;
//         digitalWrite(motorPinBL, LOW) ;
//         digitalWrite(motorPinFR, LOW) ;
//         digitalWrite(motorPinBR, LOW) ;
//     }

//     void move(bool left, bool right){

//         digitalWrite(motorPinFL, left) ;
//         digitalWrite(motorPinBL, !left) ;
//         digitalWrite(motorPinFR, right) ;
//         digitalWrite(motorPinBR, !right) ;
//     }
// } ;

// class ServoController {
// private:

//     int pin ;
//     int minAngle ;
//     int maxAngle ;

//     const int freq = 50 ; // 50 hz (20 ms)
//     const int resolution = 16 ; // 16 unit

//     // 2^n function
//     int pow(int exp) {
//         int result = 1 ;
//         for (int i = 0; i < exp; i++){
//             result *= 2 ;
//         }
//         return result ;
//     }

//     // 0.5 ms(min servo delay) / 20 ms(total delay) * 2^16(max value)
//     const int minValue = static_cast<int>(0.5 * (freq / 1000) * pow(resolution)) ;

//     // 2.4 ms(max servo delay) / 20 ms(total delay) * 2^16(max value)
//     const int maxValue = static_cast<int>(2.4 * (freq / 1000) * pow(resolution)) ;

// public:

//     ServoController(int pin, int minAngle = 0, int maxAngle = 180) : 
//         pin(pin), minAngle(minAngle), maxAngle(maxAngle){

//         ledcSetup(pin, freq, resolution) ;
//         ledcAttachPin(pin, pin) ;
//     }

//     void moveTo(int angle){
//         if (angle < minAngle) angle = minAngle ;
//         if (angle > maxAngle) angle = maxAngle ;

//         int duty = map(angle, 0, 180, minValue, maxValue) ;
//         ledcWrite(pin, duty) ;
//     }
// } ;

// // Setup

// LEDController ledController ;
// MotorController motorController ;
// ServoController headController(headpin, headMinAngle, headMaxAngle) ;
// ServoController tailController(tailpin, tailMinAngle, tailMaxAngle) ;

// // Use to make head shake

// bool isHeadShakeing = false ;

// void HeadShake(){

//     static int angle = headOrginAngle ;
//     static int next = 1 ;

//     if (angle <= headMinAngle || angle >= headMaxAngle) next = -next ;

//     angle = angle + next ;
//     headController.moveTo(angle) ;
// }

// void setup(){

//     BT.begin(boatName) ;

//     headController.moveTo(headOrginAngle) ;
//     tailController.moveTo(tailOrginAngle) ;
// }

// void loop(){

//     motorController.stop() ;

//     if (!BT.available()){
        
//         return ;
//     }

//     switch (BT.read())
//     {
    
//     // Motor

//     case 'F':
//         motorController.move(HIGH, HIGH) ;
//         break ;

//     case 'B':
//         motorController.move(LOW, LOW) ;
//         break ;

//     case 'R':
//         motorController.move(HIGH, LOW) ;
//         break ;

//     case 'L':
//         motorController.move(LOW, HIGH) ;
//         break ;

//     case 'S':
//         motorController.stop() ;
//         break ;

//     // Head

//     case 'O': // Open
//         isHeadShakeing == true ;
//         break ;

//     case 'C': // Close
//         isHeadShakeing == false ;
//         break ;

//     // Tail

//     case 'l': // Left
//         tailController.moveTo(tailLeft) ;
//         break ;

//     case 'm': // middle
//         tailController.moveTo(tailmidd) ;
//         break ;

//     case 'r': // right
//         tailController.moveTo(tailrigh) ;
//         break ;
    
//     default:
//         break ;
//     }
// }