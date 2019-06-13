#!/usr/bin/env bash
echo 'Compiling all programs.'
gcc semaphores.c -o semaphores.out
gcc named_1.c -o named_1.out
gcc named_2.c -o named_2.out
gcc named_3.c -o named_3.out
gcc unnamed_pipes.c -o unnamed_pipes.out
