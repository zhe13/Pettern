#include "math.h"

#define PI    3.14159265358979323846
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define MIN(a,b) ((a) <= (b) ? (a) : (b))
#define MAX(a,b) ((a) >= (b) ? (a) : (b))

typedef struct {
	double r, i;
} complex;


extern  void lowpassfilter(double *data,double threshold,unsigned long dataLen);
extern  void  fft(complex *td, complex *fd, int r);
extern  void ifft(complex *fd, complex *td, int r);
extern  float MinFloat(float a,float b);
extern  float AbsFloat(float a);
extern  int  AbsInt(int a);