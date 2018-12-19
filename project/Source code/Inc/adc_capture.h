/*
 * adc_capture.h
 *
 *  Created on: Dec 19, 2018
 *      Author: robert
 */

#ifndef ADC_CAPTURE_H_
#define ADC_CAPTURE_H_

// Includes
#include "stdint.h"
#include "stdbool.h"

// Defines
#define adc_buffer_size 	10000
#define trigger_stepsize	50
#define trigger_min		50
#define trigger_max		3300
#define trigger_default		1500

// Typedefs
typedef enum trigger_type_t {
	trigger_off = 0,
	trigger_rising,
	trigger_falling,
	trigger_any,
	nr_of_trigger_values
} trigger_type_t;



// Global variables
extern int16_t 	adc_buffer_a[adc_buffer_size];
extern int16_t 	adc_buffer_b[adc_buffer_size];


// Function prototypes


void 		set_trigger_mode(trigger_type_t new_trigger_mode);
trigger_type_t 	get_trigger_mode();
void 		set_trigger_level(int16_t new_trigger_level_mv);
int16_t		get_trigger_level();
uint32_t 	get_adc_index();



#endif /* ADC_CAPTURE_H_ */
