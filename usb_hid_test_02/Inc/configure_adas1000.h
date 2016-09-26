

#ifndef INC_CONFIGURE_ADAS1000_H_
#define INC_CONFIGURE_ADAS1000_H_

#include "stdint.h"

#define CALDAC_ADDRESS 0x09
#define CALDAC_RESET (uint32_t)0x002000
#define CALDAC_CONFIG (uint32_t)0x003a00

#define CMREFCTL_ADDRESS 0x05
#define CMREFCTL_RESET (uint32_t)0xe00000
//#define CMREFCTL_CONFIG (uint32_t)0x00000b // datasheet example; no common mode
#define CMREFCTL_CONFIG (uint32_t)0xa0000b // datasheet example; la, ra common mode


#define TESTTONE_ADDRESS 0x08
#define TESTTONE_RESET (uint32_t)0x000000
#define TESTTONE_CONFIG (uint32_t)0xf8001d  // 1 hz square

#define FILTCTL_ADDRESS 0x0b
#define FILTCTL_RESET (uint32_t)0x000000
#define FILTCTL_CONFIG (uint32_t)0x000008

#define FRMCTL_ADDRESS 0x0a
#define FRMCTL_RESET (uint32_t)0x079000
//#define FRMCTL_CONFIG (uint32_t)0x079600  // datasheet example
#define FRMCTL_CONFIG (uint32_t)0x078000  // datasheet example, resp phase included, 12 words frame

#define ECGCTL_ADDRESS 0x01
#define ECGCTL_RESET (uint32_t)0x000000
//#define ECGCTL_CONFIG (uint32_t)0xa0028e    // 2.8 amplifier gain
//#define ECGCTL_CONFIG (uint32_t)0xf800ae   // 1.4 amplifier gain;  for sine wave test
#define ECGCTL_CONFIG (uint32_t)0xf804ae   // datasheet example

#define LOFFCTL_ADDRESS 0x02
#define LOFFCTL_RESET (uint32_t)0x000000
//#define LOFFCTL_CONFIG (uint32_t)0x03f003
#define LOFFCTL_CONFIG (uint32_t)0x000001

#define RESPCTL_ADDRESS 0x03
#define RESPCTL_RESET (uint32_t)0x000000
#define RESPCTL_CONFIG (uint32_t)0x002199   // external capacitors

// returns current content of control register
uint32_t read_control_register(uint8_t address);
// returns written and back read value of register
uint32_t configure_register(uint8_t address, uint32_t configuration);
// returns 1 if fault, 0 if success
uint32_t configure_adas1000(void);

// returns reset pin port state
uint32_t reset_adas1000(void);

#endif /* INC_CONFIGURE_ADAS1000_H_ */
