#include "adas1000_get_save_frame.h"
#include "frame_ring_buffer.h"
#include "spi_low_level.h"
#include "gpio.h"


/**
  * @brief EXTI line detection callback.
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
/*
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == drdy_adas_exti9_Pin)
    {
    	new_frame_ready_flag = 1;

    }
}
*/

// message - massiv uint32_t slov soobscheniya, v kotoryh nas interesuyut mladshie 3 baita
// length - dlina soobsheniya (v uint32_t slovah)
uint32_t crc_calculation(uint32_t *message, int length_bytes, uint32_t polynomial, uint32_t preset, uint32_t extension)
{
	int i, j;

	uint32_t mask = 0x00ffffff;
	uint32_t crc_register;
	uint8_t crc_pred_register;

	//preliminary actions *****************************
	// load register with preset value (all ones)
	crc_register = preset;
	// copy message on local bytes array
	int length_words = length_bytes / 4;
	if(length_bytes%4 != 0)
	    length_words++;
	uint8_t bytearray[256];
	for(i=0; i<length_words; i++)
	{
	    bytearray[i*4 + 3] = (uint8_t)message[i];
	    bytearray[i*4 + 2] = (uint8_t)(message[i]>>8);
        bytearray[i*4 + 1] = (uint8_t)(message[i]>>16);
        bytearray[i*4]     = (uint8_t)(message[i]>>24);
	}


	// expand message with extension (on the right end)
	bytearray[length_bytes+2] = (uint8_t)extension;
	bytearray[length_bytes+1] = (uint8_t)(extension>>8);
    bytearray[length_bytes] = (uint8_t)(extension>>16);

	// crc calculation loop ***************************
	for(i=0;i<length_bytes+3;i++)
	{
		// load pred register with next word of message
		crc_pred_register = bytearray[i];

		// shift-xor loop
		for(j=0; j<8;j++)
		{
			crc_register <<=1;

			if((crc_pred_register & msb8_mask) != 0)
				crc_register += lsb_mask;
			crc_pred_register <<=1;
			if((crc_register & msb_mask) != 0)
				crc_register ^= CRC_POLYNOM;
		}
	}



	// zero ms byte
	crc_register &= (uint32_t)0x00ffffff;

	return crc_register;

}


// returns number of correct words in frame
int read_frame(uint32_t *frame_buffer)
{
	int i;

	uint32_t return_value = 0;

	synchronize();

	wait_for_drdy();

	// check if new fame ready flag is up
	//if(new_frame_ready_flag)
	if((drdy_adas_exti9_GPIO_Port->IDR & drdy_adas_exti9_Pin) == GPIO_PIN_RESET)
	{
		new_frame_ready_flag = 0;

		// check if drdy pin is low right now
		if((drdy_adas_exti9_GPIO_Port->IDR & drdy_adas_exti9_Pin) == GPIO_PIN_RESET)
		{
			// read register 0x40 (frame header), initiate frame reading
			write_4byte_word(((uint32_t)0x40) << 24);
			//frame_buffer[0] = read_4byte_word();
			// read frame in loop
			for(i=0; i<FRAME_LENGTH; i++)
			{
				frame_buffer[i] = read_4byte_word();
			}

			// check crc
			//uint32_t crc_received = frame_buffer[11];
			//crc_received = (~crc_received) & 0x00ffffff;
			//return_value = crc_calculation(&frame_buffer[1], 40, CRC_POLYNOM, ALL_ONES, ALL_ZEROS);

			// check correctness
			//if((frame_buffer[0]&((uint32_t)0xff000000)) == ADDRESS0)
				//return_value++;
			if((frame_buffer[1]&((uint32_t)0xff000000)) == ADDRESS1)
				return_value++;
			if((frame_buffer[2]&((uint32_t)0xff000000)) == ADDRESS2)
				return_value++;
			if((frame_buffer[3]&((uint32_t)0xff000000)) == ADDRESS3)
				return_value++;
			if((frame_buffer[4]&((uint32_t)0xff000000)) == ADDRESS4)
				return_value++;
			if((frame_buffer[5]&((uint32_t)0xff000000)) == ADDRESS5)
				return_value++;
			if((frame_buffer[6]&((uint32_t)0xff000000)) == ADDRESS6)
				return_value++;
			if((frame_buffer[7]&((uint32_t)0xff000000)) == ADDRESS7)
                return_value++;
			if((frame_buffer[8]&((uint32_t)0xff000000)) == ADDRESS8)
                return_value++;
			if((frame_buffer[9]&((uint32_t)0xff000000)) == ADDRESS9)
                return_value++;
			if((frame_buffer[10]&((uint32_t)0xff000000)) == ADDRESS10)
                return_value++;
			if((frame_buffer[11]&((uint32_t)0xff000000)) == ADDRESS11)
                return_value++;

		}
	}

	return return_value;
}

