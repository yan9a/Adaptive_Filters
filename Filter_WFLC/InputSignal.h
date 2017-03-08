// Generate input signal
// Author: Yan Naing Aye
// http://coolemerald.blogspot.sg/
// Date: 2016 April 15
//-----------------------------------------------------
//Define amplitude
#define A1 100
#define A2 5
#define A3 80
#define A4 0
//-----------------------------------------------------
//Define angular frequency
#define V1 (2*PI*2) 
#define V2 (2*PI*4)
#define V3 (2*PI*3)
#define V4 (2*PI*6)
//-----------------------------------------------------
//Define phase
#define P1 (PI/2)
#define P2 (PI)
#define P3 (PI/6)
#define P4 (PI/4)
//-----------------------------------------------------
//Define interval for the first part
#define T1 15
//-----------------------------------------------------
float GenerateInput(float t)
{
  float y;
  //Define input
  if(t<T1) { //for the first interval
    y=A1*sin(V1*t+P1)+ A2*sin(V2*t+P2);
  } 
  else {
    y=A3*sin(V3*t+P3)+ A4*sin(V4*t+P4);
  }

  //add noise
  y+=(float(analogRead(A0)&0x0F)-7.5)*0.5;
  return y;
}
