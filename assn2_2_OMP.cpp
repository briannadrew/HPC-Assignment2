// Name: assn2_1.cpp
// Author: Brianna Drew
// ID: #0622446
// Date Created: 2021-10-29
// Last Modified: 2021-10-31

// libraries
#include <stdio.h>
#include <omp.h>

// global variables
float y = 1, x0 = 0;

// a sample differential equation "dy/dx = (x - y) / 2"
float dydx(float x, float y)
{
  return((x - y) / 2);
}

// finds value of y for a given x using step size h and initial value y0 at x0
void rungeKutta(float x, float h, int n)
{
  #pragma omp parallel for ordered
  for (int i = 1; i <= n; i++) {
    float k1, k2, k3, k4;
    #pragma omp ordered
    {
    // apply runge kutta formulas to find next value of y
    k1 = h*dydx(x0, y);
    k2 = h*dydx(x0 + 0.5*h, y + 0.5*k1);
    k3 = h*dydx(x0 + 0.5*h, y + 0.5*k2);
    k4 = h*dydx(x0 + h, y + k3);
    }
    // update next value of y
    y = y + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);
    // update next value of x
    x0 = x0 + h;
  }
}

// driver method
int main()
{
  float x = 2, h = 0.01;

  // count number of iterations using step size or step height h
  int n = (int)((x - x0) / h);

  rungeKutta(x, h, n);

  #pragma omp parallel master
  printf("\nThe value of y at x is: %f", y);
  // answer should be approx. 1.103639
  return 0;
}
