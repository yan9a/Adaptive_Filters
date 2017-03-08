// BMFLC filter
// An implementation of an adaptive filter called 
// Band-limited Multiple Fourier Linear Combiner
// Author: Yan Naing Aye
// http://coolemerald.blogspot.sg/
// Date: 2016 April 15
//--------------------------------------------------------
//Constants
//#define PI 3.141592654   // π (predefined)
#define N 4         // number of dominant frequency components
#define F0 1      // starting frequency
#define dF 1      // ΔF: frequency step (spacing between the dominant components)
#define MU 0.01    // μ: adaptive gain parameter
//i.e. 1 Hz to 4 Hz band
//--------------------------------------------------------
//External variables
float v[N];//array of angular frequencies
float x[2][N];//reference input vector, 1st row for sin and 2nd row for cos
float w[2][N];//weight vector, 1st row for sin and 2nd row for cos
//--------------------------------------------------------
//initialize BMFLC filter
//Get angular velocities and initialize weights
void InitBMFLC()
{
  int i;
  for (i=0;i<N; i++) {v[i]=2*PI*(F0+dF*i);} //assign a band of frequencies
  for (i=0;i<N; i++) {w[0][i]=0; w[1][i]=0;}//init weights
}
//--------------------------------------------------------
//BMFLC filter
//input (k: time instant, s: reference signal)
//output (y: estimated signal)
float BMFLC(float k,float s)
{
  int i; float err,y;
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
  return y;
}
//--------------------------------------------------------
