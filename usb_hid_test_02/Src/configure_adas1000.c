#include "configure_adas1000.h"
#include "spi_low_level.h"
#include "gpio.h"


// returns reset pin port state
uint32_t reset_adas1000(void)
{
	// adas reset high
	HAL_GPIO_WritePin(GPIOA, reset_adas_Pin, GPIO_PIN_SET);
	HAL_Delay(3);
	// adas reset low (reset)
	HAL_GPIO_WritePin(GPIOA, reset_adas_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);
	// adas reset high
	HAL_GPIO_WritePin(GPIOA, reset_adas_Pin, GPIO_PIN_SET);
	HAL_Delay(3);

	return GPIOA->ODR;
}


uint32_t read_control_register(uint8_t address)
{
    uint32_t return_value = 0;

    synchronize();
    write_4byte_word(((uint32_t)address) << 24);
    return_value = read_4byte_word();

    return return_value;
}


uint32_t configure_register(uint8_t address, uint32_t configuration)
{
    uint32_t return_value = 0;

    // write configuration word in configuration register
    write_4byte_word((uint32_t)0x80000000 | (((uint32_t)address) << 24) | configuration);
    synchronize();
    // readback configuration word
    write_4byte_word(((uint32_t)address) << 24);
    return_value = read_4byte_word();

    // return readback configuration word
    return return_value;
}

// returns 1 if fault, 0 if success
uint32_t configure_adas1000(void)
{
	int correct_counter = 0;

	reset_adas1000();

	// for sinewave test
    //if(((((uint32_t)CALDAC_ADDRESS)<<24) | CALDAC_CONFIG) == configure_register(CALDAC_ADDRESS, CALDAC_CONFIG))
        //correct_counter++;
    //////////////
	if(((((uint32_t)RESPCTL_ADDRESS)<<24) | RESPCTL_CONFIG) == configure_register(RESPCTL_ADDRESS, RESPCTL_CONFIG))
        correct_counter++;
	if(((((uint32_t)CMREFCTL_ADDRESS)<<24) | CMREFCTL_CONFIG) == configure_register(CMREFCTL_ADDRESS, CMREFCTL_CONFIG))
        correct_counter++;
	// for sinewave test
	//if(((((uint32_t)TESTTONE_ADDRESS)<<24) | TESTTONE_CONFIG) == configure_register(TESTTONE_ADDRESS, TESTTONE_CONFIG))
        //correct_counter++;
	//if(((((uint32_t)FILTCTL_ADDRESS)<<24) | FILTCTL_CONFIG) == configure_register(FILTCTL_ADDRESS, FILTCTL_CONFIG))
        //correct_counter++;
	//////////////
	if(((((uint32_t)FRMCTL_ADDRESS)<<24) | FRMCTL_CONFIG) == configure_register(FRMCTL_ADDRESS, FRMCTL_CONFIG))
		correct_counter++;
	if(((((uint32_t)ECGCTL_ADDRESS)<<24) | ECGCTL_CONFIG) == configure_register(ECGCTL_ADDRESS, ECGCTL_CONFIG))
		correct_counter++;

	if(((((uint32_t)LOFFCTL_ADDRESS)<<24) | LOFFCTL_CONFIG) == configure_register(LOFFCTL_ADDRESS, LOFFCTL_CONFIG))
		correct_counter++;
	/*
	if(((((uint32_t)RESPCTL_ADDRESS)<<24) | RESPCTL_CONFIG) == configure_register(RESPCTL_ADDRESS, RESPCTL_CONFIG))
		correct_counter++;
	*/

	return correct_counter;

}
