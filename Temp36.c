// Temperature Alert!
const int BLED=PB0; // Blue LED Cathode on Pin B0
const int GLED=PB1; // Green LED Cathode on Pin B1
const int RLED=PB2; // Red LED Cathode on Pin B2
const int TEMP=PA0; // Temp Sensor is on pin A0
const int LOWER_BOUND=139; // Lower Threshold
const int UPPER_BOUND=147; // Upper Threshold
int val = 0; // Variable to hold analog reading

void setup() {
	pinMode (TEMP, INPUT);
pinMode (BLED, OUTPUT); // Set Blue LED as Output
pinMode (GLED, OUTPUT); // Set Green LED as Output
pinMode (RLED, OUTPUT); // Set Red LED as Output
}
void loop() {
val = analogRead(TEMP);
if (val < LOWER_BOUND) { // LED is Blue
digitalWrite(RLED, HIGH);
digitalWrite(GLED, HIGH);
digitalWrite(BLED, LOW);
}
else if (val > UPPER_BOUND) { // LED is Red
digitalWrite(RLED, LOW);
digitalWrite(GLED, HIGH);
digitalWrite(BLED, HIGH);
}
else { // LED is Green
digitalWrite(RLED, HIGH);
digitalWrite(GLED, LOW);
digitalWrite(BLED, HIGH);
}
}