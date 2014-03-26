/*
The MIT License (MIT)

Copyright (c) 2014 Rasmus Backman

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

int SampleTime = 1000; //1 sec

//unsigned long lastTime;
float pidInput, pidOutput, pidSetpoint;
float ITerm, lastInput;
float kp, ki, kd;

float outMin, outMax;

char pidIsInAutoMode = 0;
int pidIsReversed = 0;

void pidUpdate()
{
   if(!pidIsInAutoMode) return;

  /*Compute all the working error variables*/
  float error = pidSetpoint - pidInput;
  ITerm += (ki * error);

  if( ITerm > outMax ) {
	  ITerm = outMax;
  } else if( ITerm < outMin ) {
	  ITerm = outMin;
  }

  float dInput = (pidInput - lastInput);

  /*Compute PID Output*/
  pidOutput = kp * error + ITerm- kd * dInput;
  if(pidOutput > outMax) pidOutput = outMax;
  else if(pidOutput < outMin) pidOutput = outMin;

  /*Remember some variables for next time*/
  lastInput = pidInput;
}

void pidSetTunings(float Kp, float Ki, float Kd)
{
   if (Kp<0 || Ki<0|| Kd<0) return;

  float SampleTimeInSec = ((float)SampleTime)/1000;
   kp = Kp;
   ki = Ki * SampleTimeInSec;
   kd = Kd / SampleTimeInSec;

  if(pidIsReversed)
   {
      kp = (0 - kp);
      ki = (0 - ki);
      kd = (0 - kd);
   }
}

void pidSetSampleTime(int NewSampleTime)
{
   if (NewSampleTime > 0)
   {
      float ratio  = (float)NewSampleTime
                      / (float)SampleTime;
      ki *= ratio;
      kd /= ratio;
      SampleTime = (unsigned long)NewSampleTime;
   }
}

void pidSetOutputLimits(float Min, float Max)
{
   if(Min > Max) return;
   outMin = Min;
   outMax = Max;

   if(pidOutput > outMax) pidOutput = outMax;
   else if(pidOutput < outMin) pidOutput = outMin;

   if(ITerm > outMax) ITerm= outMax;
   else if(ITerm < outMin) ITerm= outMin;
}

void pidSetMode(int Mode)
{
    char newMode = Mode;
    if(newMode == 1 && !pidIsInAutoMode)
    {  /*we just went from manual to auto*/
        pidInit();
    }
    pidIsInAutoMode = newMode;
}

void pidInit()
{
   lastInput = pidInput;
   ITerm = pidOutput;

   if( ITerm > outMax ) {
	   ITerm = outMax;
   } else if( ITerm < outMin ) {
	   ITerm = outMin;
   }
}

void pidSetDirection(int Direction)
{
   pidIsReversed = Direction;
}
