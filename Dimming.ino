#include <TimerOne.h>           

volatile int i=0;               // counter
volatile boolean zero_cross=0;  // a "switch" to tell us if we have crossed zero
int AC_pin = 3;                 // Output to Opto Triac
int dim = 128;                  // Dimming level0 = on, 128 = 0ff
int freqStep = 75;    // This is the delay-per-brightness step in microseconds.
char incomingByte;  // incoming data from serial

void setup() { 
  Serial.begin(9600);
  pinMode(AC_pin, OUTPUT);                         
  attachInterrupt(0, zero_cross_detect, RISING);   
  Timer1.initialize(freqStep);                    
  Timer1.attachInterrupt(dim_check, freqStep);
}

void zero_cross_detect() {   
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i=0;
  digitalWrite(AC_pin, LOW);
}                                

// Turn on the TRIAC at the appropriate time
void dim_check() {                  
  if(zero_cross == true) {             
    if(i>=dim) {                    
      digitalWrite(AC_pin, HIGH);     
      i=0;  // reset time step counter                        
      zero_cross=false;    // reset zero cross detection
    }
    else {
      i++;                   
    }                               
  }   
}
void loop() { 
    incomingByte = Serial.read();
      switch (incomingByte) {
      case '0':
        dim=128;
        Serial.print("recieved :");
        Serial.println(dim);
        break;
      case '1':
        dim=110;
        Serial.print("recieved :");
        Serial.println(dim);
        break;
      case '2':
        dim=90;
        Serial.print("recieved :");
        Serial.println(dim);
        break;
      case '3':
        dim=70;
        Serial.print("recieved :");
        Serial.println(dim);
        break;
      case '4':
        dim=50;
        Serial.print("recieved :");
        Serial.println(dim);
        break;
      case '5':
        dim=40;
        Serial.print("recieved :");
        Serial.println(dim);
        break;
      case '6':
        dim=30;
        Serial.print("recieved :");
        Serial.println(dim);
        break;
      case '7':
        dim=20;
        Serial.print("recieved :");
        Serial.println(dim);
        break;
       case '8':
        dim=10;
        Serial.print("recieved :");
        Serial.println(dim);
        break; 
       case '9':
        dim=0;
        Serial.print("recieved :");
        Serial.println(dim);
        break; 
      
}

 delay (100);
}
