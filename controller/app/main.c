#include "app/analog_temp.h"
#include "heartbeat.h"
#include "intrinsics.h"
#include "keypad.h"
#include "RGB.h"
#include "i2c_master.h"
#include "analog_temp.h"
#include <msp430fr2355.h>

char buff[2];
int farenheit = 0;
char window_size = 'A';
int timer_counter = 0;
char temperature[2];
char topdec[5];
char botdec[5];
int first_unlock = 0;
int already_unlocked = 0;
char temp_char = ' ';
int temp_max = 24;
int temp_min = 23;
int temp_mode = 0;
int temperature_receive_flag = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer
    P1DIR |= BIT6; // configure LED2
    P1OUT &= ~BIT6;

    // -- config of mosfet control pins
    P4DIR |= BIT3;
    P4DIR |= BIT2;
    P4OUT |= BIT3;
    P4OUT |= BIT2;

    //-- SETUP TIMER -------------------------------------------------------
    TB1CTL |= TBCLR;
    TB1CTL |= TBSSEL__SMCLK;     // Source SMCLK
    TB1CTL |= MC__UP;
    TB1CTL |= CNTL_0;

    TB1CCR0 = 65535/2;

    TB1EX0 |= TBIDEX__7;        // setting divider D2

    TB1CCTL0 |= CCIE;           // Clear ISR flag
    TB1CCTL0 &= ~CCIFG;         // Enable timer interrupt

    i2c_master_init();
    analog_temp_init();
    analog_temp_get_temp();
    analog_temp_get_temp();

    __enable_interrupt();       // Enable Maskable IRQs

    // Disable low-power mode / GPIO high-impedance
    PM5CTL0 &= ~LOCKLPM5;
    // heartbeat_init();
    keypad_init();
    char previous = " ";
    char keypressed = " ";
    int window = 3;
    char line[16];

    // float temp = 0.0;
    char holding [5];
    char* temp_string = "hello";
    char temp_top2 = ' ';
    while(1) {
        // Main loop
        if (keypressed != previous && keypressed != 0 && keypad_is_unlocked()){
            switch(keypressed){
                case '1':
                    write_toplin("Greetings!     :");
                    write_bottom("Matt/Jack.      ");
                    
                    i2c_master_transmit(0x42, "1", 1);
                    break;
                case '2':
                    // temperature[0] = (temperature[0]<<1);
                    // temp_top2 = ((temperature[1]>>7)&1);
                    // temp_char = temperature[0]+temp_top2;
                    // itoa(temp_char, topdec, 10);
                    // itoa((int)(((temperature[1]>>3)&15)*6.25), botdec, 10);
                    // write_temperature(topdec, botdec);
                    break;
                case '#':
                    // i2c_master_transmit(0x40, "G", 1);
                    // i2c_master_transmit(0x40, "t", 1);
                    // float temp = analog_temp_get_temp();
                    // itoa((int)temp, holding, 10);
                    // i2c_master_transmit(0x40, holding, 2);
                    // i2c_master_transmit(0x40, ".", 1);
                    // temp = 100*(temp-(int)temp);
                    // itoa((int)temp, holding, 10);
                    // i2c_master_transmit(0x40, holding, 1);
                    // if(farenheit) i2c_master_transmit(0x40, "F", 1);
                    // else  i2c_master_transmit(0x40, "C", 1);
                    // buff[0] = window_size;
                    // i2c_master_transmit(0x40, buff, 1);
                    break;
                case 'D':
                    i2c_master_transmit(0x40, "D", 1);
                    i2c_master_transmit(0x42, "D", 1);
                    temp_mode = 0;
                    break;
                case 'A':
                    temp_mode = 1;
                    break;
                case 'B':
                    temp_mode = 2;
                    break;
                case 'C':
                    temp_mode = 3;
                    break;
            }
        }  else if (!keypad_is_unlocked() && keypressed=='D'){
            i2c_master_transmit(0x40, "D", 1);
            i2c_master_transmit(0x42, "D", 1);
            first_unlock = 0;
            i2c_master_transmit(0x40, "H", 1);
            i2c_master_transmit(0x40, "G", 1);
            temp_mode = 0;
        }
        keypressed = keypad_scan();

      if(temperature_receive_flag==1 && keypad_is_unlocked()){
        // i2c_master_recieve(0x48, 0x00, 3, temperature);
        if (timer_counter%2==0) {
          update_screen();
          temperature_receive_flag = 0;
        }
        
      }
    }
}

void update_screen(){
  __disable_interrupt();
  TB1CCTL0 |= CCIFG;
  __enable_interrupt();

  // ----- update top line -----
  char holding [5];
  switch (temp_mode){
    case 1:
      write_string("GTHeat     A:", 13);
      break;
    case 2:
      write_string("GTCool     A:", 13);
      break;
    case 3:
      write_string("GTMatch    A:", 13);
      break;
    case 0:
      write_string("GTOff      A:", 13);
      break;
  }
  float temp = analog_temp_get_temp();
  itoa((int)temp, holding, 10);
  i2c_master_transmit(0x40, holding, 2);
  i2c_master_transmit(0x40, ".", 1);
  temp = 100*(temp-(int)temp);
  itoa((int)temp, holding, 10);
  i2c_master_transmit(0x40, holding, 1);
  i2c_master_transmit(0x40, "C", 1);
  // ----- ----- ----- -----

  // ----- update bottom line -----
  char temp_top2 = ' ';
  write_string("HBN ", 4);
  // time in seconds
  itoa(timer_counter/4, holding, 10);
  if ((timer_counter/4)>100) write_string(holding, 3);
  else if(timer_counter/4>9) {
    write_string("0", 1);
    write_string(holding, 2);
  } else{
    write_string("00", 2);
    write_string(holding, 1);
  }
  write_string("s   P:", 6);
  // i2c temp
  float val = i2c_master_recieve(0x48, 0x00, 3);
  itoa((int)(val), topdec, 10);
  itoa((int)(val*100), botdec, 10);
  if (val>9.99) write_string(topdec, 2);
  else{
    write_string("0", 1);
    write_string(topdec, 1);
  }
  write_string(".", 1);
  write_string(botdec, 1);
  write_string("C", 1);
  
  __disable_interrupt();
  TB1CCTL0 &= ~CCIFG;
  __enable_interrupt();
}

void write_toplin(char line[16]){
  i2c_master_transmit(0x40, "GT", 2);
  i2c_master_transmit(0x40, line, 16);
}

void write_bottom(char line[16]){
  i2c_master_transmit(0x40, "HB", 2);
  i2c_master_transmit(0x40, line, 16);
}

void write_string(char line[], int size){
  i2c_master_transmit(0x40, line, size);
}

void write_temperature(char top[5], char bottom[5]){
  i2c_master_transmit(0x40, "H", 1);
  i2c_master_transmit(0x40, "t", 1);
  i2c_master_transmit(0x40, top, 2);
  i2c_master_transmit(0x40, ".", 1);
  i2c_master_transmit(0x40, bottom, 1);
  i2c_master_transmit(0x40, "C", 1);
  buff[0] = window_size;
  i2c_master_transmit(0x40, buff, 1);
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


// This is the interrupt in which will controll most aspects of the project.
  #pragma vector = TIMER1_B0_VECTOR
__interrupt void temperature_update(void)
{
    timer_counter++;
    if (timer_counter%2==0){
      P1OUT ^= BIT6;
    } 
    if (timer_counter%4==0){
      temperature_receive_flag = 1;
    }
    if(timer_counter<1600){
      switch (temp_mode) {
        case 0:
          // off
          P4OUT |= BIT2 | BIT3;
          break;
        case 1:
          //heat
          P4OUT |= BIT2;
          if(temp_char<temp_max){
            // start/keep heating
            P4OUT &= ~BIT3;
          } else {
            P4OUT |= BIT3;
          }
          break;
        case 2:
          // cool
          P4OUT |= BIT3;
          if(temp_char>temp_min){
            // start/keep cooling
            P4OUT &= ~BIT2;
          } else {
            P4OUT |= BIT2;
          }
          break;
      }
      // P4OUT ^= BIT3;
      // P4OUT ^= BIT2;
    }
    if(timer_counter>1200){
      P4OUT &= ~BIT3;
      P4OUT &= ~BIT2;
    }
    TB0CTL &= ~TBIFG;
    return;
}