#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int rank, size;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//printf("Hello world from %d of %d ranks\n", rank, size);
	int messageN = 10;
	int messageTag = 999;

	/*if(rank==0){
		int *messageOut = (int*) malloc(messageN*sizeof(int));
		int *messageIn = (int*) malloc(messageN*sizeof(int));
                int messageSource = 15;
		int messageDest = 1;
		for(int n=0;n<messageN;++n){
			messageOut[n] =n;
		}
		MPI_Recv(messageIn,
                        messageN,
                        MPI_INT,
                        messageSource,
                        messageTag,
                        MPI_COMM_WORLD,
                        &status);

		MPI_Send(messageOut,
			messageN,
			MPI_INT,
			messageDest,
			messageTag,
			MPI_COMM_WORLD);
	}
	if(rank==1){*/
	MPI_Status status;
	int *messageIn = (int*) malloc(messageN*sizeof(int));
	int messageSource =rank-1;
	int messageDest = rank+1;
	if(rank ==0){

		MPI_Send(messageIn,
                        messageN,
                        MPI_INT,
                        messageDest,
                        messageTag,
                        MPI_COMM_WORLD);
		MPI_Recv(messageIn,
			messageN,
			MPI_INT,
			size-1,
			messageTag,
			MPI_COMM_WORLD,
			&status);
		printf("Hello World\n");
		
	}
	else if (rank ==size-1){
		MPI_Recv(messageIn,
                        messageN,
                        MPI_INT,
                        messageSource,
                        messageTag,
                        MPI_COMM_WORLD,
			&status);
                MPI_Send(messageIn,
                        messageN,
                        MPI_INT,
                        0,
                        messageTag,
                        MPI_COMM_WORLD);

	}
	else{
		MPI_Recv(messageIn,
                        messageN,
                        MPI_INT,
                        messageSource,
                        messageTag,
                        MPI_COMM_WORLD,
                        &status);
                MPI_Send(messageIn,
                        messageN,
                        MPI_INT,
                        messageDest,
                        messageTag,
                        MPI_COMM_WORLD);
		printf("%d\n", rank);
	}
	
	MPI_Finalize();
	return 0;
}
