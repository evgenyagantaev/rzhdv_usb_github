/*
 * isoline.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#include "isoline.h"


void isoline_add_new_sample(uint32_t new_sample)
{
	shift_array(isoline_buffer, ISOLINE_BUFFER_LENGTH);
	isoline_buffer[ISOLINE_BUFFER_LENGTH-1] = new_sample;
	copy_array(isoline_buffer, isoline_buffer_sorted, ISOLINE_BUFFER_LENGTH);
	sort(isoline_buffer_sorted, ISOLINE_BUFFER_LENGTH);

	new_sample_added_flag = 1;
}


void calculate_isoline_value()
{
	int i;
	current_isoline = 0;
	for(i=CUT_EDGES; i<(ISOLINE_BUFFER_LENGTH-CUT_EDGES); i++)
	{
		current_isoline += isoline_buffer_sorted[i];
	}
	current_isoline /= (ISOLINE_BUFFER_LENGTH-2*CUT_EDGES);
}

uint32_t get_isoline_value()
{
	return current_isoline;
}
uint32_t get_last_sample()
{
	return isoline_buffer[ISOLINE_BUFFER_LENGTH-1];
}
//****************************************************************

int get_new_sample_flag()
{
	return new_sample_added_flag;
}
void set_new_sample_flag(int flag)
{
	new_sample_added_flag = flag;
}


//****************************************************************
// sluzhebnye funkcii

void shift_array(uint32_t *array, int LENGTH)
{
	int i;
	for(i=0; i<(LENGTH-1); i++)
		array[i] = array[i+1];
}
void copy_array(uint32_t *array_from, uint32_t *array_to, int LENGTH)
{
	int i;
	for(i=0; i<LENGTH; i++)
		array_to[i] = array_from[i];
}

// puzyrkovaya sortirovka
void sort(uint32_t *array, int LENGTH)
{
	int i, j;

	for(i=LENGTH; i>0; i--)
	{
		for(j=1; j<i; j++)
		{
			if(array[j]<array[j-1])	// gonim maksimalnyi vverh
			{
				uint32_t aux = array[j];
				array[j] = array[j-1];
				array[j-1] = aux;
			}
		}
	}
}
