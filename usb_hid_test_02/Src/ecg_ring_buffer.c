#include "ecg_ring_buffer.h"

int ecg_ring_buffer_initialization(void)
{
    int i;
    for(i=0; i<ECGBUFFERLENGTH; i++)
        ecg_ring_buffer[i] = 0;;

    current_ecg_push_index = 1;
    current_ecg_pop_index = 0;

    uint32_t summ = 0;
    for(i=0; i<ECGBUFFERLENGTH; i++)
        summ += ecg_ring_buffer[i];


    return summ + current_ecg_push_index - 1 + current_ecg_pop_index;
}


int ecg_ring_buffer_push(uint32_t sample)
{
    // copy sample into bufer
    int index_mod_bufferlength = (current_ecg_push_index%ECGBUFFERLENGTH);
    ecg_ring_buffer[index_mod_bufferlength] = sample;

    // increment index
    current_ecg_push_index++;
    // increment counter of received samples
    received_ecg_samples_counter++;

    // check overflow situation
    if((current_ecg_push_index - current_ecg_pop_index) >= ECGBUFFERLENGTH)
    {
        // protyagivaem current_pop_index
        current_ecg_pop_index++;

        ecg_overflow_flag = 1;
    }


    return ecg_ring_buffer[(current_ecg_push_index-1)%ECGBUFFERLENGTH] - sample;


}


int ecg_ring_buffer_pop(uint32_t *sample)
{
    // clear overflow flag
    ecg_overflow_flag = 0;

    // check bottom situation
    uint32_t old_ecg_pop_index = current_ecg_pop_index;
    if(current_ecg_pop_index < current_ecg_push_index)
    {
        int index_mod_bufferlength = (current_ecg_pop_index%ECGBUFFERLENGTH);
        *sample = ecg_ring_buffer[index_mod_bufferlength];

        current_ecg_pop_index++;
    }
    else // current_ecg_pop_index >= current_ecg_push_index
    {
        // pop out old value
        int index_mod_bufferlength = ((current_ecg_pop_index - 1)%ECGBUFFERLENGTH);
        *sample = ecg_ring_buffer[index_mod_bufferlength];
    }





    return (ecg_ring_buffer[old_ecg_pop_index%ECGBUFFERLENGTH] - *sample);

}


uint32_t get_received_ecg_samples_counter()
{
    return received_ecg_samples_counter;
}








