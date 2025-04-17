#include "LEDarray.h"
#include "msp430fr2310.h"

// Pattern timing control
static float base_transition_period = 1.0;  // Default 1.0s
static unsigned int pattern_step1 = 0;
static unsigned int pattern_step2 = 0;
static unsigned int pattern_step3 = 0;
static unsigned int pattern_step4 = 255;
static unsigned int pattern_step5 = 1;
static unsigned int pattern_step6 = 128;
static unsigned int pattern_step7 = 1;
static unsigned int pattern_count7 = 1;
static unsigned int pattern_step8 = 8;
static unsigned int pattern_count8 = 8;


static led_pattern_t current_pattern = PATTERN_NONE;
static int pattern_active = 0;

// Pattern definitions
static const unsigned char STATIC_PATTERN = 0xAA;  // 10101010

static const unsigned char TOGGLE_PATTERN[2] = {
    0xAA,   // 10101010
    0x55    // 01010101
};

static const unsigned char IN_OUT_PATTERN[6] = {
    0x18,   // 00011000
    0x24,   // 00100100
    0x42,   // 01000010
    0x81,   // 10000001
    0x42,   // 01000010
    0x24    // 00100100
};

static const unsigned char DOWN_FILL[8] = {
    0x00000001b,
    0x00000011b,
    0x00000111b,
    0x00001111b,
    0x00011111b,
    0x00111111b,
    0x01111111b,
    0x11111111b
};

// Timer initialization for pattern updates
static void init_timer(void) {
    //-- SETUP TIMER -------------------------------------------------------
    TB0CTL |= TBCLR;
    TB0CTL |= TBSSEL__SMCLK;     // Source SMCLK
    TB0CTL |= MC__UP;
    TB0CTL |= CNTL_0;

    TB0CCR0 = 65535;

    TB0EX0 |= TBIDEX__7;        // setting divider D2

    TB0CCTL0 |= CCIE;           // Clear ISR flag
    TB0CCTL0 &= ~CCIFG;         // Enable timer interrupt

    __enable_interrupt();       // Enable Maskable IRQs
}

void ledarray_init(void) {
    // Configure LED pins as outputs
    P1DIR |= LED_PINSA;
    P1OUT &= ~LED_PINSA;  // All LEDs off initially
    P2DIR |= LED_PINSB;
    P2OUT &= ~LED_PINSB;
    
    
    init_timer();
}

void ledarray_select_pattern(led_pattern_t pattern) {
    if (pattern == current_pattern) {
        switch(current_pattern){
            // *Note* ran out of memory
            case PATTERN_7_FILL:
                current_pattern = PATTERN_7_FILL;
                pattern_step7 = 1;
                break;
            case PATTERN_8_FILL_DOWN:
                current_pattern = PATTERN_8_FILL_DOWN;
                pattern_step8 = 8;
                break;
        }
    } else {
        current_pattern = pattern;
    }
    pattern_active = 1;
}

void ledarray_set_transition_period(float period) {
    TB0CCTL0 |= CCIFG;         // Disable timer interrupt
    base_transition_period = period;
    
    // Update timer period
    unsigned int timer_counts = (unsigned int)(period * 65535); // Assuming 1MHz SMCLK
    TB0CCR0 = timer_counts;
    TB0CCTL0 |= CCIE;           // Clear ISR flag
    TB0CCTL0 &= ~CCIFG;         // Enable timer interrupt
}

float ledarray_get_transition_period(void) {
    return base_transition_period;
}

void ledarray_decrease_period(void) {
    if (base_transition_period > 0) {
        ledarray_set_transition_period(base_transition_period - 0.25);
    }
}

void ledarray_increase_period(void) {
    if(base_transition_period < 1){
        ledarray_set_transition_period(base_transition_period + 0.25);
    }
}

void ledarray_set_pattern(int pattern){
    int led_group_a;
    int led_group_b;
    led_group_a = pattern & LED_PINSA;
    led_group_b = (pattern<<4) & LED_PINSB;
    P1OUT &= ~ LED_PINSA;
    P2OUT &= ~ LED_PINSB;
    P1OUT |= led_group_a;
    P2OUT |= led_group_b;
}

void ledarray_update(void) {
    if (!pattern_active) return;
    
    switch (current_pattern) {

        // *Note* Commented out for the sake of memory (ran out)
        case PATTERN_7_FILL:
            ledarray_set_pattern(pattern_step7);
            if (pattern_count7==8)
                pattern_count7 = 0;
            pattern_step7 = 2;
            int i;
            for (i = 0; i<pattern_count7; i++){
                pattern_step7 *= 2;
            }
            pattern_step7--;
            pattern_count7++;
            break;
        case PATTERN_8_FILL_DOWN:
            ledarray_set_pattern(pattern_step8);
            pattern_step8 = pattern_step8>>1 | pattern_step8;
            if(pattern_step8 > 64) pattern_step8 = 1;
            break;
            
        default:
            P1OUT &= ~LED_PINSA;
            P2OUT &= ~LED_PINSB;
            break;
    }
}

// Timer A1 interrupt handler
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer1_A0_ISR(void) {
    // Update LED pattern
    ledarray_update();
}