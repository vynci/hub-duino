
int ledPin13 = 13; 
int ledPin12 = 12; 
int ledPin11 = 11; 
int ledPin10 = 10;
int incomingByte;               
 
int ledState = LOW;
long previousMillis = 0;
long interval = 1000;
int blinkEnable = 0;

void setup() {
 
 Serial.begin(9600); 

 pinMode(ledPin13, OUTPUT);  
 pinMode(ledPin12, OUTPUT);  
 pinMode(ledPin11, OUTPUT);  
 pinMode(ledPin10, OUTPUT);  
}
 
void loop() {
  
 unsigned long currentMillis = millis();
  
// if (Serial.available() > 0) {
   
  incomingByte = Serial.read(); 
   
  if (incomingByte == '0') {
    digitalWrite(ledPin13, HIGH); 
  }
  
  else if (incomingByte == '1') {
    digitalWrite(ledPin13, LOW); 
  }
 
  else if (incomingByte == '2') {
    digitalWrite(ledPin12, HIGH); 
  } 
 
 
  else if (incomingByte == '3') {
    digitalWrite(ledPin12, LOW); 
  }

  else if (incomingByte == '4') {
    digitalWrite(ledPin11, HIGH); 
  }  

  else if (incomingByte == '5') {
     digitalWrite(ledPin11, LOW); 
  }

  else if (incomingByte == '6') {
     digitalWrite(ledPin13, HIGH); 
     digitalWrite(ledPin12, HIGH); 
     digitalWrite(ledPin11, HIGH); 
     digitalWrite(ledPin10, HIGH); 
  } 

  else if (incomingByte == '7') {
     digitalWrite(ledPin13, LOW); 
     digitalWrite(ledPin12, LOW); 
     digitalWrite(ledPin11, LOW); 
     digitalWrite(ledPin10, LOW); 
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
     blinkEnable = 1;
  }

  else if (incomingByte == 'b') {
     blinkEnable = 0;
     digitalWrite(ledPin12, LOW);
  }  
  
  if(blinkEnable == 1){
    if(currentMillis - previousMillis > interval) {
        // save the last time you blinked the LED 
        previousMillis = currentMillis;   
    
        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW)
          ledState = HIGH;
        else
          ledState = LOW;
    
        // set the LED with the ledState of the variable:
        digitalWrite(ledPin12, ledState);
      }  
  }
 //}
}
