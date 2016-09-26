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
static const uint16_t HARDTACHYTHRESHOLD = 185;
static const uint16_t TACHYTHRESHOLD = 125;
static const uint16_t numberOfRepeatingStatesToSwitch = 15;
static const uint16_t RECREATIONPERIODLENGTH = 120; // in seconds


static const uint16_t timeToGetStartPulse = 20;      // time (seconds) to set start pulse after walking or running
static const uint16_t startPulseAdd = 5;             // add to start pullse
static const uint16_t tuningInterval = 10;           // floating tachicardia tuning interval

//*********************** end constants *************************************


//************************* variables ***************************************

// value reprezents operator condition
int status;
// local copy of current heart rate value
//int pulse;

// floating tachicardia threshold
int tachiThreshold;

int yellowCounter;
int redCounter;
int blackCounter;

int state, previousState;

// interval of diagnostics information output (in seconds)
static long DIAGNOSTICSINTERVAL = 2;

// flag that indicates that recreation period after walking or running
// not finished yet
int recreationPeriodPending;

// timer (counter) that counts recreation period
int recreationPeriodTimer;

int lastDisplayedPulse; // last normal value of pulse which was displayed

double recreationRatio;      // текущий темп восстановления после нагрузки
double recreationRatio1;     // темп восстановления после нагрузки ([удары в минуту]/секунды) на первом участке (1 минута)
double recreationRatio2;	// темп восстановления после нагрузки ([удары в минуту]/секунды) на втором участке (2 минута)
double recreationRatio3;	// темп восстановления после нагрузки ([удары в минуту]/секунды) на третьем участке

// time marker which fixes the moment when running or walking stops
long walkingRunningStopMarker;

// start pulse for recreation
int startPulse;

// time marker of last tachicardia tuning moment
long lastTachycardiaTuningMarker;
// flag; indicates that floating tachicardia threshold is tuned yet
int tachycardiaThresholdTuned;

int badAdcRangeFlag;
long badAdcRangeMarker;

//*********************** end variables ************************************


static const uint16_t LOWBOUNDADCDIAPAZONE = 500;
static const uint16_t UPPERBOUNDADCDIAPAZONE = 65500;
static const uint16_t ADCRANGEPERIOD = 1; // in seconds

// flag; when set, signals that input of adc is out of range
int badAdcRange;

int adcRangeTimer;

int badIsoline;



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
