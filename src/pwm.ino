//Initializing LED Pin
int gate_pin = 3;

void setup() {
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    //Declaring LED pin as output
    pinMode(gate_pin, OUTPUT);
}

void loop() {
    //Fading the LED
    for(int i=0; i<255; i++){
        analogWrite(gate_pin, i);
        Serial.println(i);
        delay(100);
    }

    delay(1000);

    for(int i=255; i>0; i--){
        analogWrite(gate_pin, i);
        Serial.println(i);
        delay(100);
    }

    delay(250);
}