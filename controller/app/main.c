#include "app/analog_temp.h"
#include "heartbeat.h"
#include "intrinsics.h"
#include "keypad.h"
#include "RGB.h"
#include "i2c_master.h"
#include "analog_temp.h"
#include <msp430fr2355.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer
    i2c_master_init();
    analog_temp_init();
    analog_temp_get_temp();
    analog_temp_get_temp();

    // Disable low-power mode / GPIO high-impedance
    PM5CTL0 &= ~LOCKLPM5;
    heartbeat_init();
    keypad_init();
    // i2c_master_transmit(0x68, "hi");
    char previous = " ";
    char keypressed = " ";
    int already_unlocked = 0;
    int first_unlock = 0;
    char window_size = 'A';
    int window = 3;
    char buff[2];
    int farenheit = 0;

    // float temp = 0.0;
    char holding [5];
    char* temp_string = "hello";
    while(1) {
        // Main loop
        if (keypressed != previous && keypressed != 0 && first_unlock && keypad_is_unlocked()){
            i2c_master_transmit(0x40, "G", 1);
            switch(keypressed){
                case '1':
                    i2c_master_transmit(0x40, "1", 1);
                    i2c_master_transmit(0x42, "1", 1);
                    break;
                case '2':
                    i2c_master_transmit(0x40, "2", 1);
                    i2c_master_transmit(0x42, "2", 1);
                    break;
                case '3':
                    i2c_master_transmit(0x40, "3", 1);
                    i2c_master_transmit(0x42, "3", 1);
                    break;
                case 'A':
                    i2c_master_transmit(0x40, "A", 1);
                    i2c_master_transmit(0x42, "A", 1);
                    break;
                case '4':
                    i2c_master_transmit(0x40, "4", 1);
                    i2c_master_transmit(0x42, "4", 1);
                    break;
                case '5':
                    i2c_master_transmit(0x40, "5", 1);
                    i2c_master_transmit(0x42, "5", 1);
                    break;
                case '6':
                    i2c_master_transmit(0x40, "6", 1);
                    i2c_master_transmit(0x42, "6", 1);
                    break;
                case 'B':
                    i2c_master_transmit(0x40, "B", 1);
                    i2c_master_transmit(0x42, "B", 1);
                    break;
                case '7':
                    i2c_master_transmit(0x40, "7", 1);
                    // i2c_master_transmit(0x42, "7", 1);
                    break;
                case '8':
                    i2c_master_transmit(0x40, "8", 1);
                    i2c_master_transmit(0x42, "8", 1);
                    break;
                case '9':
                    i2c_master_transmit(0x40, "9", 1);
                    i2c_master_transmit(0x42, "9", 1);
                    break;
                case 'C':
                    i2c_master_transmit(0x40, "C", 1);
                    i2c_master_transmit(0x42, "C", 1);
                    break;
                case '*':
                    farenheit = !farenheit;
                    break;
                case '0':
                    i2c_master_transmit(0x40, "0", 1);
                    i2c_master_transmit(0x42, "0", 1);
                    break;
                case '#':
                    i2c_master_transmit(0x40, "T", 1);
                    float temp = analog_temp_get_temp();
                    if (farenheit) temp = (temp*9/5)+32;
                    itoa((int)temp, holding, 10);
                    i2c_master_transmit(0x40, holding, 2);
                    i2c_master_transmit(0x40, ".", 1);
                    temp = 100*(temp-(int)temp);
                    itoa((int)temp, holding, 10);
                    i2c_master_transmit(0x40, holding, 1);
                    if(farenheit) i2c_master_transmit(0x40, "F", 1);
                    else  i2c_master_transmit(0x40, "C", 1);
                    buff[0] = window_size;
                    i2c_master_transmit(0x40, buff, 1);
                    break;
                case 'D':
                    i2c_master_transmit(0x40, "D", 1);
                    i2c_master_transmit(0x42, "D", 1);
                    break;
            }
        } else if (first_unlock == 0 && keypad_is_unlocked()){
            already_unlocked = 1;
            first_unlock = 1;
            i2c_master_transmit(0x40, "R", 1);
            char window_key = 'J';
            while (window_key == 'J'){
              window_key = keypad_scan();
              switch (window_key){
                case '1':
                  window = 1;
                  window_size = '1';
                  break;
                case '2':
                  window = 2;
                  window_size = '2';
                  break;
                case '3':
                  window = 3;
                  window_size = '3';
                  break;
                case '4':
                  window = 4;
                  window_size = '4';
                  break;
                case '5':
                  window = 5;
                  window_size = '5';
                  break;
                case '6':
                  window = 6;
                  window_size = '6';
                  break;
                case '7':
                  window = 7;
                  window_size = '7';
                  break;
                case '8':
                  window = 8;
                  window_size = '8';
                  break;
                case '9':
                  window = 9;
                  window_size = '9';
                  break;
                default:
                  window_key = 'J';
              }
            }
          analog_temp_set_window(window);
            
        } else if (!keypad_is_unlocked() && keypressed=='D'){
            i2c_master_transmit(0x40, "D", 1);
            i2c_master_transmit(0x42, "D", 1);
            first_unlock = 0;
            i2c_master_transmit(0x40, "H", 1);
            i2c_master_transmit(0x40, "G", 1);
        }else {
            already_unlocked = 0;
        }
        keypressed = keypad_scan();
        
        // i2c_master_transmit(0x40, "0", 1);
        
        
        // __delay_cycles(1000000);
    }
}

void itoa(int value, char* result, int base)
	{
	  // check that the base if valid
	  if (base < 2 || base > 36) { *result = '\0';}

	  char* ptr = result, *ptr1 = result, tmp_char;
	  int tmp_value;

	  do {
	    tmp_value = value;
	    value /= base;
	    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	  } while ( value );

	  // Apply negative sign
	  if (tmp_value < 0) *ptr++ = '-';
	  *ptr-- = '\0';
	  while(ptr1 < ptr) {
	    tmp_char = *ptr;
	    *ptr--= *ptr1;
	    *ptr1++ = tmp_char;
	  }

	}