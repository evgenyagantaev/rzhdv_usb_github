/*
 * diagnost_obj.h
 *
 *  Created on: Sep 18, 2016
 *      Author: root
 */

#ifndef INC_DIAGNOST_OBJ_H_
#define INC_DIAGNOST_OBJ_H_

#include "stdint.h"

//************************* constants ***************************************
static const uint16_t HARDBRADYTHRESHOLD = 40;
static const uint16_t BRADYTHRESHOLD = 50;
static const uint16_t HARDTACHYTHRESHOLD = 175;
static const uint16_t TACHYTHRESHOLD = 118;
static const uint16_t numberOfRepeatingStatesToSwitch = 15;
static const uint16_t RECREATIONPERIODLENGTH = 120; // in seconds


static const uint16_t timeToGetStartPulse = 20;      // time (seconds) to set start pulse after walking or running
static const uint16_t startPulseAdd = 5;             // add to start pullse
static const uint16_t tuningInterval = 10;           // floating tachicardia tuning interval

//*********************** end constants *************************************


//************************* variables ***************************************

// value reprezents operator condition
static int status;
// local copy of current heart rate value
//int pulse;

// floating tachicardia threshold
static int tachiThreshold;

static int greencounter;
static int yellowCounter;
static int redCounter;
static int blackCounter;

static int state, previousState;

// interval of diagnostics information output (in seconds)
static long DIAGNOSTICSINTERVAL;


static int lastDisplayedPulse; // last normal value of pulse which was displayed

// time marker which fixes the moment when running or walking stops
static long walkingRunningStopMarker;

// start pulse for recreation
static int startPulse;


//*********************** end variables ************************************



//*********************************************************************************

void diagnost_init();

int getStatus();
long getInterval();
void setInterval(long interval);
void setLastDisplayedPulse(int pulse);
int getLastDisplayedPulse();
int getTachiThreshold();
int getBadAdcRangeFlag();
void setBadAdcRangeFlag();
void resetBadAdcRangeFlag();
long getBadAdcRangeMarker();
void setBadAdcRangeMarker(long timer);


// Method performs diagnostics
void makeDiagnosis(int pulse, int walkingDetected, int runningDetected,
				 int position);



#endif /* INC_DIAGNOST_OBJ_H_ */
