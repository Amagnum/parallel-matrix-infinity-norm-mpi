/*
* Adarsh Baghel
*/

#include <mpi.h>
#include <bits/stdc++.h>
using namespace std;

double *createMatrix(int n,int m){
    double *matrix;
    matrix = new double[n*m];

	// Adding random data into the matrix
    for (int h=0; h<n*m; h++) {
        matrix[h] = h+1;
    }

    return matrix;
}

int main(int argc, char *argv[])
{
	int pid, nProc, ierr;
	double mytime, maxtime, mintime, avgtime;
	ierr = MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    
    //#####################################

    double infNorm;
    int m=8,n=8;
    double *a;
    
	// Process 0 is reading data from input
    if(pid==0){ 
    	cin>>m>>n;
	    
	    // checking number of rows is a multiple of no. of processes used
        assert(m>=nProc);
	    
        a = createMatrix(m,n);
        
	// Take matrix from input file
	if(false){
            a = new double[m*n];
        	for(int i=0; i<m; i++){
                for(int j=0; j<n; j++)
            		cin>>a[i*m+j];
            }
        }
    }

    mytime = MPI_Wtime(); /*get time just before work section */
    MPI_Bcast(&n, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double data[m/nProc][n];
    int size=(n*m)/nProc;

    MPI_Scatter(a,size ,MPI_DOUBLE, data, size, MPI_DOUBLE, 0, MPI_COMM_WORLD); //Scatter the Matrix
    

    double rowSum=0;
    for(int i=0; i<m/nProc; i++){
        double sum=0;
        for(int j=0; j<n; j++){
            sum+=abs(data[i][j]);
        }
        rowSum=max(sum,rowSum);
    }

    MPI_Reduce(&rowSum, &infNorm, 1, MPI_DOUBLE, MPI_MAX, 0,MPI_COMM_WORLD);

    if (pid == 0) {
        printf("INF Norm: %lf\n", infNorm);
    }

	//#####################################

    mytime = MPI_Wtime() - mytime; /*get time just after work section*/
	
	// time calculation
    MPI_Reduce(&mytime, &maxtime, 1, MPI_DOUBLE,MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Reduce(&mytime, &mintime, 1, MPI_DOUBLE, MPI_MIN, 0,MPI_COMM_WORLD);
	MPI_Reduce(&mytime, &avgtime, 1, MPI_DOUBLE, MPI_SUM, 0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if (pid == 0) 
   	{
  		avgtime /= nProc;
		printf("Min: %lf Max: %lf Avg: %lf\n", mintime, maxtime, avgtime);
    }

    MPI_Finalize();
	return 0;
}
