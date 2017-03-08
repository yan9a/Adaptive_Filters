// Generate input signal
// Author: Yan Naing Aye
// http://coolemerald.blogspot.sg/
// Date: 2016 April 21
//-----------------------------------------------------
//Define amplitude
#define A1 50
#define A2 100
//-----------------------------------------------------
//Define angular frequency
#define V1 (2*PI*2) 
#define V2 (2*PI*4)
//-----------------------------------------------------
//Define interval for the first part
#define T1 15
//-----------------------------------------------------
//External variables
float ah=0; //for high pass filter
float al=0; //for low pass filter
//-----------------------------------------------------
float Displacement(float t)
{
  float y;
  if(t<T1) { y=A1*sin(V1*t);} 
  else {y=A2*sin(V2*t);}
  return y;
}
//-----------------------------------------------------
float Acceleration(float t)
{
  float y;
  if(t<T1) { y=-A1*sin(V1*t)*(V1*V1);} 
  else {y=-A2*sin(V2*t)*(V2*V2);}
  return y;
}
//--------------------------------------------------------
//initialize low pass filter
//input: (T: sampling period, fc: cutoff frequency)
void InitLowPass(float T,float fc) {al=exp(-T*2*PI*fc);}
//-----------------------------------------------------
//Low Pass Filter
float LowPass(float x){static float yl=0; yl=x+al*(yl-x); return yl;}
//--------------------------------------------------------
//initialize high pass filter
//input: (T: sampling period, fc: cutoff frequency)
void InitHighPass(float T,float fc) {ah=exp(-T*2*PI*fc);}
//-----------------------------------------------------
//High Pass Filter
float HighPass(float x) {static float yh=0,xh=0; yh=ah*(x-xh+yh); xh=x; return yh;}
//-----------------------------------------------------
