# Compile-Run guide

These are the command lines needed to compile and run the codes:

## First, we submit a job
- to run on thin nodes:
```
qsub -l nodes=1:ppn=24 -q dssc -l walltime=3:00:00 -I
```

- to run on GPU nodes
```
qsub -l nodes=1:ppn=24 -q dssc_gpu -l walltime=3:00:00 -I
```

## To run Serial code:
- to compile C++ code
```
g++ ./serialfinal.cpp -o serialfinal
```
- to run code and get output
```
./serialcode
```

## To run OpenMP code:
- to compile C++ code
```
g++ -fopenmp -O3 ./openmpfinal.cpp -o openmpfinal
```
- to run code and get output:vary N to the number of OMP threads required
```
OMP_NUM_THREADS=N ./openmpfinal
```

## To run OpenMPI code:
- Use the following command to load the openMPI module
```
module load openmpi-4.1.1+gnu-9.3.0
```
- to compile C++ code
```
mpicc -O3 ./mpifinal.cpp -o mpifinal
```
- to run code and get output:vary N to the number of MPI processors required
```
mpirun -np N ./mpifinal
```

