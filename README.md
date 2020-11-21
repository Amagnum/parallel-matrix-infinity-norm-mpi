# Calculating Matrix Infinity Norm MPI (Parallel Computing)
A simple MPI program to calculates infinity norm of a matrix using row-wise block-striped partitioning. 
<p>

<h3> What is infinity norm? </h3>

>A matrix norm is a number defined in terms of the entries of the matrix. The norm is a useful quantity which can give important information about a matrix.
> The infinity norm of a matrix is defined to be the maximum of sums of absolute values of elements in a row, over all rows.<p>
> ![alt inf norm](https://i.imgur.com/pHrwI2A.png)
> <p> we sum the absolute values along each row and then take the biggest answer. <p>
> A = <p>[ 1  −7 ]<p>
>     [-2  −3 ]<p>
> Infinity Norm = 8.
  
### Distribution of data:
The idea is that the matrix m x n is striped among p processors so that each processors stores m/p rows of the matrix. A typical column-wise and row-wise partitioning of the matrix

### Results:
Intel(R) Core(TM) i5-8250U CPU @ 1.60GHz <br>
CPU(s):              8 <br>
Thread(s) per core:  2 <br>
![alt results](https://github.com/Amagnum/Calculate-matrix-infinity-norm-mpi/blob/main/img/Matrix%20Inf.%20Norm.png)

### Compile & run the code:
```
$ mpic++ main.cpp -o exc
$ mpirun -np 4 exc < input.txt
```
## REFERENCES
1. Chandresh Kumar Maurya, Assisant professor, IIT Indore [link](https://chandu8542.github.io/)
2. Advanced Message Passing in MPI, Using MPI Datatypes with Opaque C++ Types, Paul Preney [pdf link](https://www.sharcnet.ca/help/images/f/fa/MPI_Datatypes_with_Opaque_Types_seminar_2014.pdf)
