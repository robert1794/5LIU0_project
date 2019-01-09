/*
 * dsp_algorithm.h
 *
 *  Created on: Dec 19, 2018
 *      Author: robert
 */

#ifndef DSP_ALGORITHMS_H_
#define DSP_ALGORITHMS_H_


#include "stdint.h"
#include "stdbool.h"
#include "math.h"
//mic distance in cm
#define MIC_DISTANCE 10
#define SAMPLEFREQ 1000
//speed of sound in m/s
#define SOUNDSPEED 343

//int16_t buffer_a, int16_t buffer_b, uint32_t buffersize, int32_t shift
uint16_t cross_correlate_test();
uint32_t cross_correlate(uint16_t buffer_a[], uint16_t buffer_b[], uint32_t bufferSize, uint32_t shift);
uint32_t next_binary_search_index(int32_t min_index, int32_t max_index, int32_t last_index);
uint32_t find_time_shift(uint16_t buffer_a, uint16_t buffer_b, uint32_t buffersize, uint32_t stepsize);
float calculate_angle(uint16_t sample_number);



#endif /* DSP_ALGORITHMS_H_ */

