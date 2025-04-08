#ifndef LEDARRAY_H_
#define LEDARRAY_H_

#include <msp430.h>

// LED array pins (assuming 8 consecutive pins on Port 5)
#define LED_PIN0 BIT0    // P5.0
#define LED_PIN1 BIT1    // P5.1
#define LED_PIN2 BIT6    // P5.2
#define LED_PIN3 BIT7    // P5.3
#define LED_PIN4 BIT4    // P5.4
#define LED_PIN5 BIT5    // P5.5
#define LED_PIN6 BIT6    // P5.6
#define LED_PIN7 BIT7    // P5.7
#define LED_PINSA (LED_PIN0 | LED_PIN1 | LED_PIN4 | LED_PIN5 | LED_PIN6 | LED_PIN7)
#define LED_PINSB (LED_PIN2 | LED_PIN3)
#define LED_DIR P1DIR;
#define LED_OUT P1OUT;
#define LED_PINA_MASK 0x11110011b;
#define LED_PINB_MASK 0x11000000b;

// Pattern definitions
typedef enum {
    PATTERN_NONE = -1,
    PATTERN_0_STATIC = 0,    // 10101010 static
    PATTERN_1_TOGGLE = 1,        // Toggle pattern
    PATTERN_2_UP_COUNT = 2,      // Count up
    PATTERN_3_IN_OUT = 3,        // In and out pattern
    PATTERN_4_DOWN_COUNT = 4,
    PATTERN_5_RLA = 5,
    PATTERN_6_RRC = 6,
    PATTERN_7_FILL = 7,
    NUM_PATTERNS
} led_pattern_t;

// Function prototypes
void ledarray_init(void);
void ledarray_set_pattern(int pattern);
void ledarray_update(void);
void ledarray_select_pattern(led_pattern_t pattern);
void ledarray_all_off(void);
void ledarray_set_transition_period(float period);
float ledarray_get_transition_period(void);
void ledarray_decrease_period(void);
void ledarray_increase_period(void);

#endif /* LEDARRAY_H_ */