#include "Arduino.h"
#include "Button.h"


Button::Button(uint8_t pin, bool pullup, bool invert, uint8_t dead_time){
    this->pin = pin;
    this->invert = invert;
    this->dead_time = dead_time;
    this->pullup = pullup;
}

void Button::init(){
    pinMode(pin, pullup? INPUT_PULLUP : INPUT);
    this->state = digitalRead(pin);
}

void Button::set_press_handler       (void(*f)()) { this->press_handler_ptr =        f; }
void Button::set_down_handler        (void(*f)()) { this->down_handler_ptr =         f; }
void Button::set_long_press_handler  (void(*f)()) { this->long_press_handler_ptr =   f; }
// void Button::set_double_press_handler(void(*f)()) { this->double_press_handler_ptr = f; }

uint64_t Button::get_last_change_time(){ return last_change_time; }
uint64_t Button::get_time_from_last_change(){ return millis() - last_change_time; }

bool Button::get_state(bool read){
    if(read) tick;
    return state; 
}

void Button::tick(){
    bool s = digitalRead(pin);

    if(s != state){
        state = s;
        last_change_time = millis();
        if(invert? state: !state)
            down_handler_ptr();
        else if(get_time_from_last_change() >= long_press_time)
            long_press_handler_ptr();
        else
            press_handler_ptr();

    }
}