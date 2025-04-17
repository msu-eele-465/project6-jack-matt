#ifndef ANALOGTEMP_H
#define ANALOGTEMP_H

void analog_temp_init(void);

void analog_temp_set_window(int size);

float analog_temp_get_temp();

#endif // ANALOGTEMP_H