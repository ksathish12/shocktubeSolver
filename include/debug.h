/* 
 * File:   debug.h
 * Author: Sourabh Bhat
 *
 * Created on 3 February, 2017, 5:47 PM
 */

#ifndef DEBUG_H
#define DEBUG_H


#include <stdlib.h>
#include <stdio.h>
#include "data.h"

void printPrimitiveVariables(Cell cell, int rkStep) {
    double primVar[NUM_VARS];
    conservativeToPrimitive(cell.U[rkStep], primVar);
    
    printArray(primVar, NUM_VARS);
}

void printArray(double array[], int size) {
    printf("\n");
    int i;
    for (i = 0; i < size; i++) {
        printf("%f,  ", array[i]);
    }
}

#endif /* DEBUG_H */

