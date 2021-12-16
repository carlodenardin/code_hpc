# Instructions

To compile and run the codes use the following commands from the openmpi library

## Ring.c

The ring code is written in C. To compile and run the codes use the following commands with this params:
 - n: number of processors;

```
mpicc ./ring.c -o ring.x
mpirun -np n ./ring.x
```

## Matrix.c

The ring code is written in C++. To compile and run the codes use the following commands with this params:
 - n: number of processors;
 - X: x axis size of the big matrix;
 - Y: y axis size of the big matrix;
 - Z: z axis size of the big matrix;
 - x: x axis size of the small matrix;
 - y: y axis size of the small matrix;
 - z: z axis size of the small matrix;
```
mpic++ ./ring.c -o matrix.x
mpirun -np n ./matrix.x "X" "Y" "Z" "x" "y" "z"
```
Some matrix case:
```
mpic++ ./ring.c -o matrix.x
mpirun -np 24 ./matrix.x "2400" "100" "100" "100" "100" "100"
mpirun -np 24 ./matrix.x "1200" "200" "100" "100" "200" "50"
mpirun -np 24 ./matrix.x "800" "300" "100" "400" "100" "25"
```

