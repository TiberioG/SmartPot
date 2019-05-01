#include "analogComp.h" //library used to control analog comparator of microcontroller
// definistions of pins

#define ctrl 8
#define ref1 9
#define ref2 5
#define ref  7
#define pump A3
#define sens 6
#define halfpi 100
boolean interrupt = false;
unsigned long time1;
unsigned long time2;
int tau;
bool state = 1;

void setup() {
  
  //pinMode(ref, INPUT);
  //pinMode(sens, INPUT);
  pinMode(ctrl, OUTPUT);
  pinMode(ref1, OUTPUT);
  pinMode(ref2, OUTPUT);
  pinMode(pump, OUTPUT);
  
  digitalWrite(ctrl, LOW);
  digitalWrite(ref1, HIGH);
  digitalWrite(ref2, LOW);
  digitalWrite(pump, LOW); 
  
  analogComparator.setOn(); //we instruct the lib to use voltages on the default pins AIN0 AIN1
  analogComparator.enableInterrupt(changeStatus, CHANGE); //CHANGE when A0 ref is smaller tha A1 sensor or opposite, the interrupt function will be called
  Serial.begin(9600); // for debug purposes
}
void loop() {
time1 = micros();  // save inistial time
// half-period square wave generation
while (micros() < time1 + halfpi){ 
} 
 digitalWrite(ctrl, state);
 digitalWrite(ref1, state);
 digitalWrite(ref2, !state);
// invert state for second-half part of square wave
state = !state;
delay (1000); // sampling time of soil
Serial.println(tau); // show the time cosntsnt
if( tau > 180){
  digitalWrite(pump, LOW); // turn pump off
  } else{
  digitalWrite(pump, HIGH);
  }
}
// interrupt function
void changeStatus() {
    interrupt = true; //let's inform the main loop that the condition has been reached by the analog comparator
    time2 = micros(); // save time
    tau = time2 - time1; // calculate tau 
}
