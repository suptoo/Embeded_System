// Example 14-3: Pseudocode of wait-and-see software debouncing
bool is_button_pressed(){
    read button input;
    if (button is not pressed) return false;
    wait 50 ms;
    read button input again;
    if (button is not pressed) return false;
    return true;
}
