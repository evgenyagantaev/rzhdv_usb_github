/*
 * diagnost_obj.c
 *
 *  Created on: Sep 18, 2016
 *      Author: root
 */

#include "diagnost_obj.h"



void diagnost_init()
{
	status = 0;
	DIAGNOSTICSINTERVAL = 2;
	tachiThreshold = TACHYTHRESHOLD;

	yellowCounter = redCounter = blackCounter = 0;
	state = previousState = 0;

	recreationPeriodPending = 0;

	recreationPeriodTimer = 0;

	badAdcRange = 1;
	adcRangeTimer = 0;

	lastDisplayedPulse = 444;

	recreationRatio1 = 0.1;
	recreationRatio2 = 0.2;
	recreationRatio3 = 0.3;

	walkingRunningStopMarker = 0;

	startPulse = 0;

	lastTachycardiaTuningMarker = 0;
	tachycardiaThresholdTuned = 0;

	badAdcRangeFlag = 0;
	badAdcRangeMarker = 0;

}//end diagnost_init


//************************ properties ***************************************

   int getStatus()
   {return status;}

   long getInterval()
   {return DIAGNOSTICSINTERVAL;}

   void setInterval(long interval)
   {DIAGNOSTICSINTERVAL = interval;}

   void setLastDisplayedPulse(int pulse)
   {
      lastDisplayedPulse = pulse;
   }

   int getLastDisplayedPulse()
   {return lastDisplayedPulse;}

   int getTachiThreshold()
   {return tachiThreshold;}

   int getBadAdcRangeFlag()
   { return badAdcRangeFlag; }

   void setBadAdcRangeFlag()
   { badAdcRangeFlag = 1; }

   void resetBadAdcRangeFlag()
   { badAdcRangeFlag = 0; }

   long getBadAdcRangeMarker()
   { return badAdcRangeMarker; }

   void setBadAdcRangeMarker(long timer)
   { badAdcRangeMarker = timer1hz_get_tick(); }
   //********************** end properties *************************************



//---------------------------------------------------------------------------
// Method performs diagnostics
void makeDiagnosis(int pulse, int walkingDetected, int runningDetected,
				 int position)
{

	if(walkingDetected || runningDetected || (position == 8))
	{
		walkingRunningStopMarker = timer1hz_get_tick();
	}
	else // no walking, no running
	{
		long noLocomotionPeriod = timer1hz_get_tick() - walkingRunningStopMarker;
		//if(noLocomotionPeriod < RECREATIONPERIODLENGTH)
		if(1)
		{

		   // during start pulse set period, set start pulse
		   //if((noLocomotionPeriod < timeToGetStartPulse) && (startPulse < lastDisplayedPulse))
		   if((noLocomotionPeriod < timeToGetStartPulse) && (tachiThreshold < lastDisplayedPulse))
		   {
			  tachiThreshold = lastDisplayedPulse + startPulseAdd;
			  startPulse = lastDisplayedPulse;

			  if(recreationRatio != recreationRatio1)
				 recreationRatio = recreationRatio1;

		   }
		   else if((noLocomotionPeriod >= timeToGetStartPulse) && (startPulse < tachiThreshold))
			  startPulse += startPulseAdd;

		   if((tachiThreshold > TACHYTHRESHOLD) &&
			  ((timer1hz_get_tick() - lastTachycardiaTuningMarker) >= tuningInterval)) // tune only if floating threshold exceeds fixed one
		   {
			  // подстраиваем в моменты времени кратные 10 секундам
			  if(noLocomotionPeriod > timeToGetStartPulse)
			  {
				 // choose a recreation curve slope
				 if((noLocomotionPeriod > 60) && (noLocomotionPeriod < 120) && (recreationRatio != recreationRatio2))
					recreationRatio = recreationRatio2;
				 else if((noLocomotionPeriod > 120) && (recreationRatio != recreationRatio3))
					recreationRatio = recreationRatio3;

				 if(!tachycardiaThresholdTuned)
				 {
					tachiThreshold -= (int)(recreationRatio * tuningInterval);
					lastTachycardiaTuningMarker = timer1hz_get_tick();
					tachycardiaThresholdTuned = 1;
				 }
			  }

		   }

		   if(tachycardiaThresholdTuned && (timer1hz_get_tick() - lastTachycardiaTuningMarker) >= tuningInterval)
			  tachycardiaThresholdTuned = 0;


		}
	}// end if(walkingDetected || runningDetected || (position == 8))

	/*
	if(walkingDetected || runningDetected || (position == 8))
	{
		status = 1;
	}
	else
	//*/
	if(pulse == 0) // asistoly
	{
		//printf ("OPERATOR_CONDITION %d\r\n", 3);	// hard wounded
		status = 4;
	}
	else if(pulse < HARDBRADYTHRESHOLD) // hard bradycardia
	{
		//printf ("OPERATOR_CONDITION %d\r\n", 3);	// hard wounded
		status = 3;
	}
	else if(pulse < BRADYTHRESHOLD) // light bradycardia
	{
		//printf ("OPERATOR_CONDITION %d\r\n", 2);	// light wounded
		status = 2;
	}
	else if(pulse < 300)
	{
		if(pulse > tachiThreshold) // tachycardia
		{
		   if(pulse > HARDTACHYTHRESHOLD) // hard tachycardia
		   {
				 //printf ("OPERATOR_CONDITION %d\r\n", 3);	// hard wounded
				 status = 3;
		   }
		   else     // light tachycardia
		   {
				 //printf ("OPERATOR_CONDITION %d\r\n", 2);	// light wounded
				 status = 2;
		   }
		}
		else
		{
				//printf ("OPERATOR_CONDITION %d\r\n", 1);	// боеспособен
				status = 1;
		}
	}
	else // pulse >= 300
	status = 0;

	if(status == 4)
	{
		blackCounter++;
		redCounter = 0;
		yellowCounter = 0;
	}
	else if(status == 3)
	{
		blackCounter = 0;
		redCounter++;
		yellowCounter = 0;

	}
	else if(status == 2)
	{
		blackCounter = 0;
		redCounter = 0;
		yellowCounter++;
	}
	else
	{
		blackCounter = 0;
		redCounter = 0;
		yellowCounter = 0;
	}


	// меняем цвет маркера только если состояние повторяется заданное количество раз
	if(yellowCounter >= numberOfRepeatingStatesToSwitch)	// хочет пожелтеть
	{
		 yellowCounter = numberOfRepeatingStatesToSwitch;
		 state = 2;
	}
	else if(redCounter >= numberOfRepeatingStatesToSwitch)	// хочет покраснеть
	{
		 redCounter = numberOfRepeatingStatesToSwitch;
		 state = 3;
	}
	else if(blackCounter >= numberOfRepeatingStatesToSwitch)	// хочет почернеть
	{
		blackCounter = numberOfRepeatingStatesToSwitch;
		state = 4;
	}
	else if(status == 1)
	{
		 state = 1;
	}
	else
		 state = previousState;

	previousState = state;
	status = state;


}

//--------------------------end----------------------------------------------


