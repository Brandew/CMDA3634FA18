#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char **argv){

  long long int Ninside = 0; // number of random points inside 1/4 circle
  long long int Ntests = 1000000000;
  long long n;
  int Nthreads = atoi(argv[1]);
  omp_set_num_threads(Nthreads);
  double estpi = 0;

  double stime = omp_get_wtime();

#pragma omp parallel reduction(+:Ninside) 
  {
  struct drand48_data buffer;
  srand48_r(omp_get_thread_num(), &buffer);
#pragma omp for
  for(n=0;n<Ntests;++n){
    double x,y;
    drand48_r(&buffer, &x);
    drand48_r(&buffer, &y);

    if(x*x+y*y<1){
      ++Ninside;
    }
  }
  }
  estpi = 4.*(Ninside/(double)Ntests);
  double etime = omp_get_wtime();
  double time = etime - stime;
 printf("estimate of Pi = %lf\ntime : %f seconds\n", estpi, time);

  return 0;
//Running with four threads produces a result slightly quicker than using one thread. The result produced is also slightly different.
}

