/*
 * histogram_obj.h
 *
 *  Created on: Aug 21, 2017
 *      Author: root
 */

#ifndef HISTOGRAM_OBJ_H_
#define HISTOGRAM_OBJ_H_

#define HISTOGRAM_LOW_BOUND 300 // miliseconds (200 bps)
#define HISTOGRAM_UP_BOUND 1500 // miliseconds (40 bps)
#define BIN_STEP 25 // miliseconds
#define NUMBER_OF_BINS 48

static int histogram_new_window_ready_flag;
void histogram_drop_new_window_ready_flag();
static int histogram[NUMBER_OF_BINS];

static double tension_index;
int histogram_get_tension_index(void);

//-------------------------------------------------

void histogram_new_window_ready_flag_set(int flag);
int histogram_new_window_ready_flag_get(void);

void histogram_clean(); // obnulyaem massiv gistogrammy
void histogram_fill(); //zapolnyaem massiv gistogrammy

void histogram_tension_index_calculate(); // calculate tension

#endif /* HISTOGRAM_OBJ_H_ */
