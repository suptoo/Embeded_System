const int LED=PC13; // Define LED for pin PC13

void setup()
{
   pinMode (LED, OUTPUT); 
   // Set the LED pin as an output
}

void loop()
{
   digitalWrite(LED, HIGH);
   delay(1000); // Time in milliseconds
   digitalWrite(LED, LOW);
   delay(1000);
}
