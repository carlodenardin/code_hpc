# Instructions

To compile and run the codes use the following commands from the openmpi library

## Ring.c

The ring code is written in C. To compile and run the codes use the following commands. In the run command n is corresponds to the number of proccessor that you want to use

```
mpicc ./ring.c -o ring.x
mpirun -np n ./ring.x
```
