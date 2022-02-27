#define pulse_ip 7
#define pulse_stime 1000000 // 1 secund

float freq = 0.0;
long ontime = 0;
long offtime = 0;
long period = 0;
   
void setup() {

    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);

    Serial.println("Hiiii");
    Serial.println();

    // noInterrupt();
    
    pinMode(pulse_ip, INPUT);
}

void loop() {

    freq = pull_frec(pulse_ip, pulse_stime);
    Serial.println(freq);
    delay(1); // ms

}

// ----------------------------------------------------------------------------
long pulse_period(int pin, long stime) {

    ontime = pulseIn(pin, HIGH, stime);
    if (ontime == 0) { return 0; }
    offtime = pulseIn(pin, LOW, stime);
    if (offtime == 0) { return 0; }
    period = ontime + offtime;

    return period;
}

// ----------------------------------------------------------------------------
// compute the frec (Hz) of pulses on 'pin' during 'stime' time.

float pull_frec(int pin, long stime) {

    long acc = 0;
    long n = 1;

    while (true) {

        period = pulse_period(pin, stime);

        if (period == 0) { return 0.0; }

        acc = acc + period;

        // Time out
        if (acc > stime) {

            Serial.print(acc);
            Serial.print(" > ");
            Serial.print(stime);
            Serial.print(", n = ");
            Serial.println(n);

            // to secunds / ave period = ave frec (Hz)
            return 1000000.0 / (acc / n);
        }

        n++;
    }

    return 0.0;
}