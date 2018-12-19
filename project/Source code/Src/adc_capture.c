/*
 * adc_capture.c
 *
 *  Created on: Dec 19, 2018
 *      Author: robert
 */

// includes
#include "adc_capture.h"


// Global variables
int16_t 	adc_buffer_a[adc_buffer_size];
int16_t 	adc_buffer_b[adc_buffer_size];


// Static variables
static trigger_type_t 	trigger_mode 		= trigger_off;
static int16_t 		trigger_level 	= trigger_default;


// Function implementation

void set_trigger_mode(trigger_type_t new_trigger_mode)
{
	if (new_trigger_mode < nr_of_trigger_values)
		trigger_mode = new_trigger_mode;
}
trigger_type_t 	get_trigger_mode()
{
	return trigger_mode;
}

void set_trigger_level(int16_t new_trigger_level_mv)
{
	if ((new_trigger_level_mv >= trigger_min) && (new_trigger_level_mv <= trigger_max))
		trigger_level = new_trigger_level_mv;
}

int16_t	get_trigger_level()
{
	return trigger_level;
}




