#include "frame_ring_buffer.h"

int frame_ring_buffer_initialization(void)
{
    current_push_index = 1;
    current_pop_index = 0;

    overflow_flag = 0;

    int i, j;
    for(i=1; i<RAWS; i++)
    {
        for(j=0; j<COLUMNS; j++)
        {
            frame_ring_buffer[i][j] = 0;
        }
    }

    for(j=0; j<COLUMNS; j++)
    {
        secondary_buffer[j] = 1;
    }
    for(j=0; j<COLUMNS; j++)
    {
        primary_buffer[j] = 0;
    }

    int summ = 0;
    for(i=0; i<RAWS; i++)
    {
        for(j=0; j<COLUMNS; j++)
        {
            summ += frame_ring_buffer[i][j];
        }
    }

    int summ1 = 0;
    for(j=0; j<COLUMNS; j++)
    {
        summ1 += secondary_buffer[j];
    }

    // return value for test
    return current_push_index - 1 + current_pop_index + summ + summ1 - COLUMNS;
}


int frame_ring_buffer_push(uint32_t *frame, int length)
{

    // esli length > COLUMNS - eto kakoi-to globalnyi kapec; sidim, nichego ne delaem
    if(length <= COLUMNS)
    {
        // copy frame into bufer
        int i;
        int index_mod_raws = (current_push_index%RAWS);
        for(i=0; i<length; i++)
        {
            frame_ring_buffer[index_mod_raws][i] = frame[i];
        }

        // increment index
        current_push_index++;
        // increment counter of received frames
        received_frames_counter++;

        // check overflow situation
        if((current_push_index - current_pop_index) >= RAWS)
        {
            // protyagivaem current_pop_index
            current_pop_index++;

            overflow_flag = 1;
        }

        int summ = 0;

        for(i=0; i<length; i++)
        {
            summ += (frame_ring_buffer[(current_push_index - 1)%RAWS][i] - frame[i]);
        }

        return summ;
    }
    else
        return 999;
}



int frame_ring_buffer_pop(uint32_t *frame, int length)
{

    // esli length > COLUMNS - eto kakoi-to globalnyi kapec; sidim, nichego ne delaem
    if(length <= COLUMNS)
    {
        // clear overflow flag
        overflow_flag = 0;

        if(current_pop_index < current_push_index)
        {
            // copy content of ring buffer
            int i;
            int index_mod_raws = (current_pop_index%RAWS);
            for(i=0; i<length; i++)
            {
                 frame[i] = frame_ring_buffer[index_mod_raws][i];
            }
            current_pop_index++;
        }
        else
        {
            // pop out old value
            int i;
            int index_mod_raws = ((current_pop_index - 1)%RAWS);
            for(i=0; i<length; i++)
            {
                 frame[i] = frame_ring_buffer[index_mod_raws][i];
            }
        }


        // check bottom situation
        uint32_t old_pop_index = current_pop_index;


        int summ = 0;
        int i;
        for(i=0; i<length; i++)
        {
            summ += (frame_ring_buffer[old_pop_index%RAWS][i] - frame[i]);
        }

        return summ;
    }
    else
        return 999;

}

uint32_t get_received_frames_counter()
{
    return received_frames_counter;
}





