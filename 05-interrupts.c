#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

void led_init()
{
    /* setup D13 led as output */
    DDRB |= (1 << DDB5);
}

void led_toggle()
{
    /* toggle on board LED */
    PINB |= (1 << PINB5);

    // can also use xor
    //PORTB ^= (1 << PORTB5);
}

// Initializes D2 as External Interrupt Request 0 (INT0)
void button_init()
{
    DDRD &= ~(1 << DDD2); // setup as input   
    //  External Interrupt Control Register A
    EICRA |= ((1 << ISC00) | (1 << ISC01)); //rising edge
    // External Interrupt Mask Register
    EIMSK |= (1 << INT0); // enable
}

ISR (INT0_vect)
{
    led_toggle();
}

int main(void) 
{
    led_init();
    button_init();
    sei(); // enable global interrupt
    
    set_sleep_mode(SLEEP_MODE_STANDBY);
    for(;;)
    { 
        sleep_mode();
    }

    return 0;
}