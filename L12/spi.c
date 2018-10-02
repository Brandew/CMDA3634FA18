#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv){

  long long int Ninside = 0; // number of random points inside 1/4 circle
  long long int Ntests = 1000000000;
  long long n;
  //use mpi reduce function for help
  
  double estpi = 0;
  /*
  for(n=0;n<Ntests;++n){
    double x = drand48();
    double y = drand48();
    
    if(x*x+y*y<1.0){
      ++Ninside;
    }
  }

  estpi = 4.*(Ninside/(double)Ntests);

  printf("estPi = %lf\n", estpi);

  return 0;
*/
	int rank, size, dec, res,sum=0;
	double x,y;
	dec = MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	srand48(rank);
	for (n=rank;n<Ntests;n+=size){
		x = drand48();
		y = drand48();
		if (((x*x)+(y*y))<1.0){
			Ninside++;
		}
	}
	MPI_Reduce(&Ninside,
		&sum,
		1,
		MPI_INT,
		MPI_SUM,
		0,
		MPI_COMM_WORLD);
	if(rank==0){
		estpi =4.*(Ninside/(double)Ntests);
	       printf("PI = %0.6f\n", estpi);	
	}

	dec =MPI_Finalize();
	return 0;
//Running with four processes does not seem to slow or quicken the converge time//

}
