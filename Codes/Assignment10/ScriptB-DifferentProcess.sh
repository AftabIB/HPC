#!/bin/bash

sizes=(1 2 3 4 5 6)

for i in "${sizes[@]}"
do 
    mpirun -np $i ./assiB 256 
done