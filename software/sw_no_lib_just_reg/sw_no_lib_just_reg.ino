
#define ref  A0
#define sens A1
#define ctrl  A2
#define pump 6

#define halfpi 100


boolean interrupt = false;
unsigned long time1;
unsigned long time2;
long tau;

bool stato = 1;

ISR (ANALOG_COMP_vect)
  {
  interrupt = true;
digitalWrite(pump, LOW);
  }

void setup() {
  pinMode(ref, INPUT);
  pinMode(sens, INPUT);
  pinMode(ctrl, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(pump, OUTPUT);
  
  ADCSRB = 0;           // (Disable) ACME: Analog Comparator Multiplexer Enable
  ACSR =  bit (ACI)     // (Clear) Analog Comparator Interrupt Flag
        | bit (ACIE)    // Analog Comparator Interrupt Enable
        | bit (ACIS0); 

  digitalWrite(ctrl, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, HIGH);
  digitalWrite(pump, HIGH);
  
Serial.begin(9600);

  
}
void loop() {
  
time1 = micros();
while (micros() < time1 + halfpi){
  /* if (interrupt == true){
    digitalWrite(pump, LOW);
    time_final = micros();
tau =  time_final - time1;
Serial.println(tau);
  }*/
}
 digitalWrite(ctrl, stato);
 digitalWrite(A3, stato);
 digitalWrite(A4, !stato);

stato = !stato;


}
