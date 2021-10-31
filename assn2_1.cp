// Name: assn2_1.cpp
// Author: Brianna Drew
// ID: #0622446
// Date Created: 2021-10-29
// Last Modified: 2021-10-29

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <omp.h>

int main (int argc, char** argv) {
  // size of array (number of columns and number of rows)
  int arr_size = 5;
  // create 2D array
  float *arr = new float[arr_size * arr_size];

  // initialize all array values to 0
  for (int i = 0; i < arr_size; i++) {
    for (int j = 0; j < arr_size; j++) {
      arr[i*arr_size+j] =  0;
    }
  }

  // START OF SIMULATION
  // jump value of middle leftmost edge of the array to 100,000
  arr[0*arr_size+(round(arr_size/2))] = 100000;

  for (int i = 0; i < arr_size; i++) {
    for (int j = 0; j < arr_size; j++) {
      int neighbours;
      float neighbour_sum = 0;
      // determine # of neighbours and their values
      if (i == 0 && j == 0) {
        neighbours = 3;
        neighbour_sum += arr[i*arr_size+(j+1)];
        neighbour_sum += arr[(i+1)*arr_size+j];
        neighbour_sum += arr[(i+1)*arr_size+(j+1)];
      }
      else if (i == 0 && j == arr_size - 1) {
        neighbours = 3;
        neighbour_sum += arr[i*arr_size+(j-1)];
        neighbour_sum += arr[(i+1)*arr_size+(j-1)];
        neighbour_sum += arr[(i+1)*arr_size+j];
      }
      else if (i == arr_size - 1 && j == 0) {
        neighbours = 3;
        neighbour_sum += arr[i*arr_size+(j+1)];
        neighbour_sum += arr[(i-1)*arr_size+(j+1)];
        neighbour_sum += arr[(i-1)*arr_size+j];
      }
      else if (i == arr_size - 1 && j == arr_size - 1) {
        neighbours = 3;
        neighbour_sum += arr[i*arr_size+(j-1)];
        neighbour_sum += arr[(i-1)*arr_size+(j-1)];
        neighbour_sum += arr[(i-1)*arr_size+j];
      }
      else if (i == 0 && j > 0 && j < arr_size - 1) {
        neighbours = 5;
      }
      else if (i == arr_size - 1 && j > 0 && j < arr_size - 1) {
        neighbours = 5;
      }
      else if (i > 0 && i < arr_size - 1 && j == 0) {
        neighbours = 5;
      }
      else if (i > 0 && i < arr_size - 1 && j == arr_size - 1) {
        neighbours = 5;
      }
      else {
        neighbours = 8;
      }
    }
  }

  // delete 2D array
  delete [] arr;

  return 0;
}
