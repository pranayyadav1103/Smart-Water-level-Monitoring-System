//#include <Servo.h>
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLlj7Bx464"
#define BLYNK_DEVICE_NAME "IOT water monitor and control"
//#define BLYNK_AUTH_TOKEN "RFxtfSD6EfsysvN-FpplX32DSj1eNGSj"

#include <BlynkSimpleEsp8266.h>
const int pingPin = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 14; // Echo Pin of Ultrasonic Sensor
const int buzzPin = 4; //buzzer pin of ultrasonic sensor
const int Relay1 = 2;
//Servo servo;
char auth[]="RFxtfSD6EfsysvN-FpplX32DSj1eNGSj";
char ssid[] = "4 (2G) -VIJAYA BOYS @ HK-NET";
char pass[] = "vijaya4444";
void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(12,OUTPUT);
   pinMode(4,OUTPUT);
   pinMode(14,INPUT);
   pinMode(2,OUTPUT);
   //servo.attach(2); //D4

   //servo.write(0);
  Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);

   delay(500);
  
}
void loop() {
   long duration, distanceInch,distanceCm,distanceft ,Waterccm ,Waterlitre,Waterft, ECm,Eft,Wft;
   int wper,WCm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   distanceInch = microsecondsToInches(duration);
   distanceCm = microsecondsToCentimeters(duration);
   //Serial.print(distanceCm);
   //Serial.print("cm");
   //Serial.print(distanceInch);
   //Serial.print("Inch");
   distanceft = distanceInch/12;  
   ECm = (distanceCm-2);
   Serial.print("Empty space");
   Serial.print(ECm);
   Serial.print("cm");  
   WCm = (20-ECm);
   Serial.print("\nwater occupied");
   Serial.print(WCm);
   Serial.print("cm");
   if(WCm<10)
   {
    digitalWrite(Relay1, LOW );
    delay(50000);
    digitalWrite(Relay1, HIGH );
    
   }
    if(WCm>=15)
    { 
      digitalWrite(buzzPin, HIGH);
       delay(1000);
       noTone(buzzPin);
    }
    if(WCm<=15)
    { 
      digitalWrite(buzzPin, HIGH);
     delay(100);
       noTone(buzzPin);
    }
 //  }
//  }
//else
//{
 //   digitalWrite(Relay1, LOW); // turn relay off
  //  delay(1000);
 //};
    
 Eft = (distanceft-0.06);  
 Wft = (0.65-Eft);  
 Waterccm = WCm *201.15;   
 Waterlitre = Waterccm*0.001;  
 Serial.print("\nwater in litres: ");  
 Serial.print(Waterlitre);    
 Serial.println("litre");   
 wper=(WCm*1.21);
 Serial.print("water percentage:");
   Serial.print(wper);
   Serial.print("%");
   Blynk.virtualWrite(V4,WCm);
   Blynk.virtualWrite(V5,Waterlitre);
   Blynk.virtualWrite(V2,ECm);
   Blynk.virtualWrite(V3,wper);
   Serial.println();
   delay(2500);
   Blynk.run();
  // servo.write(90);

}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
