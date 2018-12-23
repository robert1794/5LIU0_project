/*
 * adc_capture.c
 *
 *  Created on: Dec 19, 2018
 *      Author: robert
 */

// includes
#include "adc_capture.h"
//#include "stm32f4xx_hal_adc.h"
#include "adc.h"

// Global variables
int16_t 	adc_buffer_a[adc_buffer_size];
int16_t 	adc_buffer_b[adc_buffer_size];



// Static variables
static trigger_type_t 	trigger_mode 		= trigger_off;
static int16_t 		trigger_level 		= trigger_default;
static uint32_t		adc_buffer_index	= 0;

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

/// \brief read the current ADC index
uint32_t get_adc_index()
{
	return adc_buffer_index;
}

/// \brief resets the ADC buffer index to 0.
void reset_adc_index()
{
	adc_buffer_index = 0;
}

/// \brief ADC capture complete callback
/// Used to store the signal from the microphones in a buffer
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if (hadc == &hadc1)
	{
		if (adc_buffer_index < adc_buffer_size)
		{
			adc_buffer_a[adc_buffer_index] = HAL_ADC_GetValue(&hadc1);
		}
	} else if (hadc == &hadc2) {
		if (adc_buffer_index < adc_buffer_size)
		{
			adc_buffer_b[adc_buffer_index] = HAL_ADC_GetValue(&hadc2);
			adc_buffer_index++;
		}
	} else {// Else: something went seriously wrong here...
		printf("ERROR: ADC interrupt - unknown source\r\n");
	}
}




