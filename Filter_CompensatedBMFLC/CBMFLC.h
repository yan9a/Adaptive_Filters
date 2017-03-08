// Compensated BMFLC filter
// An implementation of an adaptive filter called 
// Compensated Band-limited Multiple Fourier Linear Combiner
// Author: Yan Naing Aye
// http://coolemerald.blogspot.sg/
// Date: 2016 April 16

// Credit: Based on code and papers of Ko Win Tun Latt
// Reference: 
// W. T. Latt, K. C. Veluvolu, and W. T. Ang, 
// "Drift-free position estimation of periodic or quasi-periodic motion using inertial sensors," 
// Sensors, vol. 11, no. 6, pp. 5931-5951, 2011.
//--------------------------------------------------------
//Constants
//#define PI 3.141592654   // π (predefined)
#define N 3         // number of dominant frequency components
#define F0 2      // starting frequency
#define dF 1      // ΔF: frequency step (spacing between the dominant components)
#define MU 0.01    // μ: adaptive gain parameter
//i.e. 2 Hz to 4 Hz band
//--------------------------------------------------------
//External variables
float v[N];//array of angular frequencies
float x[2][N];//reference input vector, 1st row for sin and 2nd row for cos
float w[2][N];//weight vector, 1st row for sin and 2nd row for cos
float p[N];//array of phase shift for compensation (*to add)
float g[N];//array of gain for compensation (*to multiply)
//--------------------------------------------------------
//initialize Compensated BMFLC filter
//Get angular velocities and initialize weights
void InitCBMFLC()
{
  int i;
  float v1=2*PI*1;//cutoff frequency for high pass filter
  float v2=2*PI*10;//cutoff frequency for low pass filter
  for (i=0;i<N; i++) {
    v[i]=2*PI*(F0+dF*i); //assign a band of frequencies
    w[0][i]=0; w[1][i]=0;//init weights
    g[i]=sqrt(1+(v[i]/v2)*(v[i]/v2))*sqrt(1+(v1/v[i])*(v1/v[i]));
    p[i]=atan(v[i]/v2)-atan(v1/v[i]);
  }
}
//--------------------------------------------------------
//Compensated BMFLC filter
//input (k: time instant, s: reference signal)
//output (yc: compensated estimated signal)
float CBMFLC(float k,float s)
{
  int i; float err,y,yc;
  //-----------------------------------------------------------------
  //find reference input vector
  for(i=0;i<N; i++){ 
    x[0][i]=sin(v[i]*k);
    x[1][i]=cos(v[i]*k);
  }
  //-----------------------------------------------------------------
  //find estimated signal, y
  for(i=0,y=0;i<N;i++){y+=w[0][i]*x[0][i]+ w[1][i]*x[1][i];}
  //-----------------------------------------------------------------
  //adapt the weights   
  for(i=0,err=s-y;i<N;i++){
    w[0][i]+=2*MU*x[0][i]*err;
    w[1][i]+=2*MU*x[1][i]*err;
  }
  //-----------------------------------------------------------------
  //find uncompensated estimated displacement, y
  for(i=0,y=0;i<N;i++){y-=(w[0][i]*x[0][i]+ w[1][i]*x[1][i])/(v[i]*v[i]);}
  //-----------------------------------------------------------------
  //find phase compensated reference input vector
  for(i=0;i<N; i++){ 
    x[0][i]=sin(v[i]*k+p[i]);
    x[1][i]=cos(v[i]*k+p[i]);
  }
  //-----------------------------------------------------------------
  //find compensated estimated integrated displacemet, yc
  for(i=0,yc=0;i<N;i++){yc-=(g[i]/(v[i]*v[i]))*(w[0][i]*x[0][i]+w[1][i]*x[1][i]);}
  //-----------------------------------------------------------------
  return yc;
}
//--------------------------------------------------------
