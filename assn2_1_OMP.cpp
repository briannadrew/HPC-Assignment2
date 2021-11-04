// Name: assn2_1.cpp
// Author: Brianna Drew
// ID: #0622446
// Date Created: 2021-10-29
// Last Modified: 2021-10-31

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <omp.h>

int main () {
  // size of array (number of columns and number of rows)
  int arr_size = 100;
  // create 2D array
  float *arr = new float[arr_size * arr_size];

  #pragma omp parallel for
  // initialize all array values to 0
  for (int i = 0; i < arr_size; i++) {
    for (int j = 0; j < arr_size; j++) {
      arr[i*arr_size+j] =  0;
    }
  }

  // START OF SIMULATION
  int mid_row = round(arr_size/2) - 1; // calculate position of middle row
  arr[mid_row*arr_size+0] = 10000000000000000000000000000000; // jump value of middle leftmost edge of the array to 100,000
  float max = 0; // largest number in array
  int count = 0, i = mid_row, j = 0, max_i = mid_row, max_j = 0; // count for each iteration of the simulation

  // repeat simulation until no cell has a number larger than 12 starting at the cell with the largest value
  // DO-WHILE LOOPS CANNOT BE PARALLELIZED AS # OF ITERATIONS ARE UNKNOWN...
  do {
    do {
      int neighbours = 0;
      float neighbour_sum = 0, neighbour_avg = 0, new_vals = 0;

      // top left corner
      if (i == 0 && j == 0) {
        // determine # of neighbours and sum their values
        neighbours = 3;
        neighbour_sum += arr[i*arr_size+(j+1)];
        neighbour_sum += arr[(i+1)*arr_size+j];
        neighbour_sum += arr[(i+1)*arr_size+(j+1)];

        // calculate average of neighbours
        neighbour_avg = neighbour_sum / neighbours;
        // calculate new values for neighbours (5% of the difference between current cell and average of neighbours)
        new_vals = abs(0.05 * (arr[i*arr_size+j] - neighbour_avg));

        // change values of neighbours to new value
        arr[i*arr_size+(j+1)] = new_vals;
        arr[(i+1)*arr_size+j] = new_vals;
        arr[(i+1)*arr_size+(j+1)] = new_vals;
      }

      // bottom left corner
      else if (i == arr_size - 1 && j == 0) {
        // determine # of neighbours and sum their values
        neighbours = 3;
        neighbour_sum += arr[i*arr_size+(j+1)];
        neighbour_sum += arr[(i-1)*arr_size+(j+1)];
        neighbour_sum += arr[(i-1)*arr_size+j];

        // calculate average of neighbours
        neighbour_avg = neighbour_sum / neighbours;
        // calculate new values for neighbours (5% of the difference between current cell and average of neighbours)
        new_vals = abs(0.05 * (arr[i*arr_size+j] - neighbour_avg));

        // change values of neighbours to new value
        arr[i*arr_size+(j+1)] = new_vals;
        arr[(i-1)*arr_size+(j+1)] = new_vals;
        arr[(i-1)*arr_size+j] = new_vals;
      }

      // top right corner
      else if (i == 0 && j == arr_size - 1) {
        // determine # of neighbours and sum their values
        neighbours = 3;
        neighbour_sum += arr[i*arr_size+(j-1)];
        neighbour_sum += arr[(i+1)*arr_size+(j-1)];
        neighbour_sum += arr[(i+1)*arr_size+j];

        // calculate average of neighbours
        neighbour_avg = neighbour_sum / neighbours;
        // calculate new values for neighbours (5% of the difference between current cell and average of neighbours)
        new_vals = abs(0.05 * (arr[i*arr_size+j] - neighbour_avg));

        // change values of neighbours to new value
        arr[i*arr_size+(j-1)] = new_vals;
        arr[(i+1)*arr_size+(j-1)] = new_vals;
        arr[(i+1)*arr_size+j] = new_vals;
      }

      // bottom right corner
      else if (i == arr_size - 1 && j == arr_size - 1) {
        // determine # of neighbours and sum their values
        neighbours = 3;
        neighbour_sum += arr[i*arr_size+(j-1)];
        neighbour_sum += arr[(i-1)*arr_size+(j-1)];
        neighbour_sum += arr[(i-1)*arr_size+j];

        // calculate average of neighbours
        neighbour_avg = neighbour_sum / neighbours;
        // calculate new values for neighbours (5% of the difference between current cell and average of neighbours)
        new_vals = abs(0.05 * (arr[i*arr_size+j] - neighbour_avg));

        // change values of neighbours to new value
        arr[i*arr_size+(j-1)] = new_vals;
        arr[(i-1)*arr_size+(j-1)] = new_vals;
        arr[(i-1)*arr_size+j] = new_vals;
      }

      // left side
      else if (i > 0 && i < arr_size - 1 && j == 0) {
        // determine # of neighbours and sum their values
        neighbours = 5;
        neighbour_sum += arr[(i-1)*arr_size+j];
        neighbour_sum += arr[(i-1)*arr_size+(j+1)];
        neighbour_sum += arr[(i)*arr_size+(j+1)];
        neighbour_sum += arr[(i+1)*arr_size+j];
        neighbour_sum += arr[(i+1)*arr_size+(j+1)];

        // calculate average of neighbours
        neighbour_avg = neighbour_sum / neighbours;
        // calculate new values for neighbours (5% of the difference between current cell and average of neighbours)
        new_vals = abs(0.05 * (arr[i*arr_size+j] - neighbour_avg));

        // change values of neighbours to new value
        arr[(i-1)*arr_size+j] = new_vals;
        arr[(i-1)*arr_size+(j+1)] = new_vals;
        arr[i*arr_size+(j+1)] = new_vals;
        arr[(i+1)*arr_size+j] = new_vals;
        arr[(i+1)*arr_size+(j+1)] = new_vals;
      }

      // right side
      else if (i < arr_size - 1 && i > 0 && j == arr_size - 1) {
        // determine # of neighbours and sum their values
        neighbours = 5;
        neighbour_sum += arr[(i-1)*arr_size+j];
        neighbour_sum += arr[(i-1)*arr_size+(j-1)];
        neighbour_sum += arr[i*arr_size+(j-1)];
        neighbour_sum += arr[(i+1)*arr_size+j];
        neighbour_sum += arr[(i+1)*arr_size+(j-1)];

        // calculate average of neighbours
        neighbour_avg = neighbour_sum / neighbours;
        // calculate new values for neighbours (5% of the difference between current cell and average of neighbours)
        new_vals = abs(0.05 * (arr[i*arr_size+j] - neighbour_avg));

        // change values of neighbours to new value
        arr[(i-1)*arr_size+j] = new_vals;
        arr[(i-1)*arr_size+(j-1)] = new_vals;
        arr[i*arr_size+(j-1)] = new_vals;
        arr[(i+1)*arr_size+j] = new_vals;
        arr[(i+1)*arr_size+(j-1)] = new_vals;
      }

      // top side
      else if (i == 0 && j < arr_size - 1 && j > 0) {
        // determine # of neighbours and sum their values
        neighbours = 5;
        neighbour_sum += arr[i*arr_size+(j-1)];
        neighbour_sum += arr[i*arr_size+(j+1)];
        neighbour_sum += arr[(i+1)*arr_size+(j-1)];
        neighbour_sum += arr[(i+1)*arr_size+j];
        neighbour_sum += arr[(i+1)*arr_size+(j+1)];

        // calculate average of neighbours
        neighbour_avg = neighbour_sum / neighbours;
        // calculate new values for neighbours (5% of the difference between current cell and average of neighbours)
        new_vals = abs(0.05 * (arr[i*arr_size+j] - neighbour_avg));

        // change values of neighbours to new value
        arr[i*arr_size+(j-1)] = new_vals;
        arr[i*arr_size+(j+1)] = new_vals;
        arr[(i+1)*arr_size+(j-1)] = new_vals;
        arr[(i+1)*arr_size+j] = new_vals;
        arr[(i+1)*arr_size+(j+1)] = new_vals;
      }

      // bottom side
      else if (i == arr_size - 1 && j > 0 && j < arr_size - 1) {
        // determine # of neighbours and sum their values
        neighbours = 5;
        neighbour_sum += arr[i*arr_size+(j-1)];
        neighbour_sum += arr[i*arr_size+(j+1)];
        neighbour_sum += arr[(i-1)*arr_size+(j-1)];
        neighbour_sum += arr[(i-1)*arr_size+j];
        neighbour_sum += arr[(i-1)*arr_size+(j+1)];

        // calculate average of neighbours
        neighbour_avg = neighbour_sum / neighbours;
        // calculate new values for neighbours (5% of the difference between current cell and average of neighbours)
        new_vals = abs(0.05 * (arr[i*arr_size+j] - neighbour_avg));

        // change values of neighbours to new value
        arr[i*arr_size+(j-1)] = new_vals;
        arr[i*arr_size+(j+1)] = new_vals;
        arr[(i-1)*arr_size+(j-1)] = new_vals;
        arr[(i-1)*arr_size+j] = new_vals;
        arr[(i-1)*arr_size+(j+1)] = new_vals;
      }

      // inner cells
      else {
        // determine # of neighbours and sum their values
        neighbours = 8;
        neighbour_sum += arr[(i-1)*arr_size+(j-1)];
        neighbour_sum += arr[(i-1)*arr_size+j];
        neighbour_sum += arr[(i-1)*arr_size+(j+1)];
        neighbour_sum += arr[i*arr_size+(j-1)];
        neighbour_sum += arr[i*arr_size+(j+1)];
        neighbour_sum += arr[(i+1)*arr_size+(j-1)];
        neighbour_sum += arr[(i+1)*arr_size+j];
        neighbour_sum += arr[(i+1)*arr_size+(j+1)];

        // calculate average of neighbours
        neighbour_avg = neighbour_sum / neighbours;
        // calculate new values for neighbours (5% of the difference between current cell and average of neighbours)
        new_vals = abs(0.05 * (arr[i*arr_size+j] - neighbour_avg));

        // change values of neighbours to new value
        arr[(i-1)*arr_size+(j-1)] = new_vals;
        arr[(i-1)*arr_size+j] = new_vals;
        arr[(i-1)*arr_size+(j+1)] = new_vals;
        arr[i*arr_size+(j-1)] = new_vals;
        arr[i*arr_size+(j+1)] = new_vals;
        arr[(i+1)*arr_size+(j-1)] = new_vals;
        arr[(i+1)*arr_size+j] = new_vals;
        arr[(i+1)*arr_size+(j+1)] = new_vals;
      }

      // if at the end of a row, go to the next row
      if (i != arr_size - 1 && j == arr_size - 1) {
        i++;
        j = 0;
      }

      // if at the end of the matrix, go to the beginning
      else if (i == arr_size - 1 && j == arr_size - 1) {
        i = 0;
        j = 0;
      }

      // go to the next column
      else {
        j++;
      }
    } while (i != max_i || j != max_j);

    // determine largest number in array
    max = arr[0*arr_size+0];
    #pragma omp parallel for
    for (int m = 0; m < arr_size; m++) {
      for (int n = 0; n < arr_size; n++) {
        if (arr[m*arr_size+n] > max) {
          max = arr[m*arr_size+n];
          i = m;
          max_i = m;
          j = n;
          max_j = n;
        }
        printf("%f ", arr[m*arr_size+n]);
      }
      printf("\n");
    }
    printf("\n\n");
    count += 1;
  } while (max > 12);

  printf("\nIterations: %d\n", count);
  // delete 2D array and exit
  delete [] arr;
  return 0;
}
