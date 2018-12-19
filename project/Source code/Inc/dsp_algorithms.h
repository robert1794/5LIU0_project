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

uint32_t cross_correlate(int16_t buffer_a, int16_t buffer_b, uint32_t buffersize, int32_t shift);
uint32_t next_binary_search_index(int32_t min_index, int32_t max_index, int32_t last_index);
uint32_t find_time_shift(uint16_t buffer_a, uint16_t buffer_b, uint32_t buffersize, uint32_t stepsize);


#endif /* DSP_ALGORITHMS_H_ */
