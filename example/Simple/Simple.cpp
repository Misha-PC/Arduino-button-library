#include <Button.h>

#define BTN_PIN 12
#define LED_PIN 13
        
Button b1(BTN_PIN, true, false, 50);

void blink_led(int time=150){
    digitalWrite(LED_PIN, HIGH);
    delay(time);
    digitalWrite(LED_PIN, LOW);

}

void setup(){
    b1.init();

    b1.set_press_handler([](){
        blink_led();
    });

    b1.set_long_press_handler([](){
        blink_led();
        delay(150);
        blink_led();
    });

    pinMode(LED_PIN, OUTPUT);

}

void loop(){
    b1.tick();
}