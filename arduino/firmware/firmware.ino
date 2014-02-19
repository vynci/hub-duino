
int ledPin13 = 13; 
int ledPin12 = 12; 
int ledPin11 = 11; 
int ledPin10 = 10;
int ledPin9 = 9; 
int ledPin8 = 8; 
int ledPin7 = 7; 
int ledPin6 = 6;
int ledPin5 = 5; 
int ledPin4 = 4; 
int ledPin3 = 3; 
int ledPin2 = 2;

int buzzer = A0;

int incomingByte;
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
 
int ledState = LOW;
long previousMillis = 0;
long interval = 1000;

int notifEnable = 0;
int notifDisable = 0;

void setup() {
 
 Serial.begin(9600); 

 pinMode(ledPin13, OUTPUT);  
 pinMode(ledPin12, OUTPUT);  
 pinMode(ledPin11, OUTPUT);  
 pinMode(ledPin10, OUTPUT);  
 pinMode(ledPin9, OUTPUT);  
 pinMode(ledPin8, OUTPUT);  
 pinMode(ledPin7, OUTPUT);  
 pinMode(ledPin6, OUTPUT); 
 pinMode(ledPin5, OUTPUT);  
 pinMode(ledPin4, OUTPUT);  
 pinMode(ledPin3, OUTPUT);  
 pinMode(ledPin2, OUTPUT); 
 pinMode(buzzer, OUTPUT); 

}

void ledsOff(){
 digitalWrite(ledPin13, LOW); 
 digitalWrite(ledPin12, LOW); 
 digitalWrite(ledPin11, LOW); 
 digitalWrite(ledPin10, LOW);  
 digitalWrite(ledPin9, LOW); 
 digitalWrite(ledPin8, LOW); 
 digitalWrite(ledPin7, LOW); 
 digitalWrite(ledPin6, LOW);
 digitalWrite(ledPin5, LOW); 
 digitalWrite(ledPin4, LOW); 
 digitalWrite(ledPin3, LOW); 
 digitalWrite(ledPin2, LOW);   
}

void ledsOn(){
 digitalWrite(ledPin13, HIGH); 
 digitalWrite(ledPin12, HIGH); 
 digitalWrite(ledPin11, HIGH); 
 digitalWrite(ledPin10, HIGH);  
 digitalWrite(ledPin9, HIGH); 
 digitalWrite(ledPin8, HIGH); 
 digitalWrite(ledPin7, HIGH); 
 digitalWrite(ledPin6, HIGH);
 digitalWrite(ledPin5, HIGH); 
 digitalWrite(ledPin4, HIGH); 
 digitalWrite(ledPin3, HIGH); 
 digitalWrite(ledPin2, HIGH);   
}

void buzzerOn1(){
 digitalWrite(buzzer, HIGH); 
 delay(250);
 digitalWrite(buzzer, LOW);
 delay(100);  
 digitalWrite(buzzer, HIGH); 
 delay(250);
 digitalWrite(buzzer, LOW);
 delay(100);
 digitalWrite(buzzer, HIGH);
 delay(250);
 digitalWrite(buzzer, LOW);
}

void buzzerOn2(){
 digitalWrite(buzzer, HIGH); 
 delay(250);
 digitalWrite(buzzer, LOW);
 delay(100);  
}


void loop() {
  
 unsigned long currentMillis = millis();
  
// if (Serial.available() > 0) {
   
  incomingByte = Serial.read(); 

  if (incomingByte == '6') {
     ledsOn();
  } 

  else if (incomingByte == '7') {
     ledsOff();
  }
 
  else if (incomingByte == '0') {
     buzzerOn1();
  } 

  else if (incomingByte == '1') {
     buzzerOn2();
  }   

  else if (incomingByte == '9') {
     digitalWrite(ledPin10, HIGH);
     delay(250);
     digitalWrite(ledPin10, LOW);
     delay(100);
     digitalWrite(ledPin10, HIGH);
     delay(250);
     digitalWrite(ledPin10, LOW);      
  } 

  else if (incomingByte == 'a') {
     notifEnable = 1;
  }

  else if (incomingByte == 'b') {
     notifEnable = 0;
     ledsOff();
  }  

  else if (incomingByte == 'c') {
     notifDisable = 1;
  }

  else if (incomingByte == 'd') {
     notifDisable = 0;
     ledsOff();
  }

  ////LED INDIVIDUAL CONTROL////

  else if (incomingByte == ',') {
    digitalWrite(ledPin13, HIGH); 
  }  

  else if (incomingByte == '.') {
    digitalWrite(ledPin13, LOW);
  }

  else if (incomingByte == 'e') {
    digitalWrite(ledPin12, HIGH);
  } 

  else if (incomingByte == 'f') {
    digitalWrite(ledPin12, LOW);
  }  

  else if (incomingByte == 'g') {
    digitalWrite(ledPin11, HIGH);
  }

  else if (incomingByte == 'h') {
    digitalWrite(ledPin11, LOW);
  }

  else if (incomingByte == 'i') {
    digitalWrite(ledPin10, HIGH); 
  }  

  else if (incomingByte == 'j') {
    digitalWrite(ledPin10, LOW);
  }

  else if (incomingByte == 'k') {
    digitalWrite(ledPin9, HIGH);
  } 

  else if (incomingByte == 'l') {
    digitalWrite(ledPin9, LOW);
  }  

  else if (incomingByte == 'm') {
    digitalWrite(ledPin8, HIGH);
  }

  else if (incomingByte == 'n') {
    digitalWrite(ledPin8, LOW);
  }

  else if (incomingByte == 'o') {
    digitalWrite(ledPin7, HIGH); 
  }  

  else if (incomingByte == 'p') {
    digitalWrite(ledPin7, LOW);
  }

  else if (incomingByte == 'q') {
    digitalWrite(ledPin6, HIGH);
  } 

  else if (incomingByte == 'r') {
    digitalWrite(ledPin6, LOW);
  }  

  else if (incomingByte == 's') {
    digitalWrite(ledPin5, HIGH);
  }

  else if (incomingByte == 't') {
    digitalWrite(ledPin5, LOW);
  }    

  else if (incomingByte == 'u') {
    digitalWrite(ledPin4, HIGH); 
  }  

  else if (incomingByte == 'v') {
    digitalWrite(ledPin4, LOW);
  }

  else if (incomingByte == 'w') {
    digitalWrite(ledPin3, HIGH);
  } 

  else if (incomingByte == 'x') {
    digitalWrite(ledPin3, LOW);
  }  

  else if (incomingByte == 'y') {
    digitalWrite(ledPin2, HIGH);
  }

  else if (incomingByte == 'z') {
    digitalWrite(ledPin2, LOW);
  }   

  ////PWM BLINK LOGIC////     
  
  if(notifEnable == 1){
    analogWrite(ledPin13, brightness);
    analogWrite(ledPin11, brightness);    

    analogWrite(ledPin10, brightness);
    analogWrite(ledPin8, brightness);    

    analogWrite(ledPin7, brightness);
    analogWrite(ledPin5, brightness);    

    analogWrite(ledPin4, brightness);
    analogWrite(ledPin2, brightness);
  
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;
  
    // reverse the direction of the fading at the ends of the fade: 
    if (brightness == 0 || brightness == 255) {
      if(brightness == 0){
        ledsOff();
      }      
      fadeAmount = -fadeAmount ; 
      delay(150);
    }     
    // wait for 30 milliseconds to see the dimming effect    
    delay(15);
  }

  if(notifDisable == 1){
    analogWrite(ledPin12, brightness);

    analogWrite(ledPin9, brightness);

    analogWrite(ledPin6, brightness);

    analogWrite(ledPin3, brightness);
  
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;
  
    // reverse the direction of the fading at the ends of the fade: 
    if (brightness == 0 || brightness == 255) {
      if(brightness == 0){
        ledsOff();
      }
      fadeAmount = -fadeAmount ; 
      delay(150);
    }     
    // wait for 30 milliseconds to see the dimming effect    
    delay(15);
  }


}
