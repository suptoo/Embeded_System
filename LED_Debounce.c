boolean debounce(boolean last)
{
    boolean current = digitalRead(BUTTON); // Read the button state
    if (last != current) // if it's different...
    {
        delay(5); //Wait 5ms
        current = digitalRead(BUTTON); //Read it again
    }
    return current; //Return the current value
}
void loop()
{
    currentButton = debounce(lastButton); //Read debounced state
    if (lastButton == LOW && currentButton == HIGH) //if it was pressed...
    {
        ledOn = !ledOn; //Toggle the LED value
    }
    lastButton = currentButton; //Reset button value
    digitalWrite(LED, ledOn); //Change the LED state
}
