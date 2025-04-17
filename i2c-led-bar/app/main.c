#include <msp430fr2310.h>
#include <stdbool.h>

#include "heartbeat.h"
#include "LEDarray.h"
#include "i2c_slave.h"

int main(void)
{
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;
    i2c_slave_init();

    // heartbeat_init();
    ledarray_init();


    // Disable low-power mode / GPIO high-impedance
    PM5CTL0 &= ~LOCKLPM5;

    ledarray_select_pattern(PATTERN_NONE);
    while (true)
    {

    }
}
