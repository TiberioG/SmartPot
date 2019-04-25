#include "analogComp.h" //library used to control analog comparator of microcontroller
// definistions of pins
#define ref  A0
#define sens A1
#define ctrl A2
#define pump 5
#define halfpi 100
boolean interrupt = false;
unsigned long time1;
unsigned long time2;
int tau;
bool state = 1;

void setup() {
  
  pinMode(ref, INPUT);
  pinMode(sens, INPUT);
  pinMode(ctrl, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(pump, OUTPUT);
  
  digitalWrite(ctrl, LOW);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, LOW);
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
 digitalWrite(A3, state);
 digitalWrite(A4, !state);
// invert state for second-half part of square wave
state = !state;
delay (1000); // sampling time of soil
Serial.println(tau); // show the time cosntsnt
if( tau > 200){
  digitalWrite(pump, HIGH); // turn pump on
  } else{
  digitalWrite(pump, LOW);
  }
}
// interrupt function
void changeStatus() {
    interrupt = true; //let's inform the main loop that the condition has been reached by the analog comparator
    time2 = micros(); // save time
    tau = time2 - time1; // calculate tau 
}
