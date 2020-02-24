#!/bin/bash

pwd

# echo "Starting 0d tests..."
# for i in {7..18}; do
#     ./randmst 0 $((2**i)) 5 0 >> "test0.txt";
# done

# echo "Starting 2d tests..."
# for i in {7..18}; do
#     ./randmst 0 $((2**i)) 5 2 >> "test0.txt";
# done

# echo "Starting 3d tests..."
# for i in {7..18}; do
#     ./randmst 0 $((2**i)) 5 3 >> "test0.txt";
# done

# echo "Starting 4d tests..."
# for i in {7..16}; do
#     ./randmst 0 $((2**i)) 5 4 >> "test0.txt";
# done


# Last tests must be single-threaded, otherwise they eat up all my RAM and take forever
for i in {17..18}; do
    for j in {1..5}; do
        ./randmst 0 $((2**i)) 1 4 >> "test0.txt";
    done
done