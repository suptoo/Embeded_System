// Example 14-4: Pseudocode of counter-debouncer software debouncing
bool is_button_pressed(){
    read button input;
    if (button is not pressed)
        return false;

    counter = 0;

    for(i = 0; i < 10; i++){
        wait 5 ms;
        read button input;
        if (button is not pressed) {
            counter = 0; // bounce, reset counter
        } else {
            counter = counter + 1; // stable, increase counter
            if (counter >= 4) // require 4 consecutive positive readings
                return true;
        }
    }
    return false;
}
