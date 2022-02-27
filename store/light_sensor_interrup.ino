const int sensor1Pin = 2; //Button to perform interrupt
const int sensor2Pin = 3; //Button to perform interrupt

//variables to keep track of the timing of recent interrupts
volatile long s1events = 0;
volatile long s2events = 0;

void setup() {

    pinMode(sensor1Pin, INPUT_PULLUP);
    pinMode(sensor2Pin, INPUT_PULLUP);

    Serial.begin(9600);

    // Sensor 1
    attachInterrupt(
        digitalPinToInterrupt(sensor1Pin), 
        sensor1_ISR, 
        RISING
    );

    // Sensor 2
    attachInterrupt(
        digitalPinToInterrupt(sensor2Pin), 
        sensor2_ISR, 
        RISING
    );
}

void loop(){

    // read (atomic)
    noInterrupts();
    float s1events_ = float(s1events);
    float s2events_ = float(s2events);
    interrupts();

    // Use measurement
    Serial.print(s1events);
    Serial.print(" / ");
    Serial.print(s2events);
    Serial.print(" = ");
    float diff = (s1events - s2events) / (s1events + s2events);
    Serial.println(diff);
    
    // reset
    s1events = 0; 
    s2events = 0; 
    
    // do stuff
    delay(1000);
}

void sensor1_ISR() { 
    s1events++; 
}
void sensor2_ISR() { s2events++; }