#if !defined(BUTTON_H)
#define BUTTON_H

#include "Arduino.h"

class Button{
private:
    bool state;
    bool invert;
    bool pullup;
    uint64_t last_change_time;
    uint16_t long_press_time;
    uint8_t dead_time;
    uint8_t pin;
    void (*down_handler_ptr)(); 
    void (*press_handler_ptr)(); 
    void (*long_press_handler_ptr)(); 
    // void (*double_press_handler_ptr)(); 


public:
    Button(uint8_t pin, bool pullup=false, bool invert=false, uint8_t dead_time=0);
    void init();

    void set_press_handler(void(*f)());
    void set_down_handler(void(*f)());
    void set_long_press_handler(void(*f)());
    // void set_double_press_handler(void(*f)());

    bool get_state(bool read);
    uint64_t get_last_change_time();
    uint64_t get_time_from_last_change();

    void tick();

};



#endif // BUTTON_H
