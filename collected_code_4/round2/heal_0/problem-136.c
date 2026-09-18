#include <stdio.h>

#define RATE1 0.5
#define RATE2 0.75
#define RATE3 1.20
#define RATE4 1.50

double calculateElectricityBill(int units)
{
  double cost;
  if(units <= 50)
  {
    cost = units * RATE1;
  }
  else if(units <= 150)
  {
    cost = 50*RATE1 + (units-50)*RATE2;
  }
  else if(units <= 250)
  {
    cost = 50*RATE1 + 100*RATE2 + (units-150)*RATE3;
  }
  else
  {
    cost = 50*RATE1 + 100*RATE2 + 100*RATE3 + (units-250)*RATE4;
  }
  return cost + 0.2*cost;
}

int main(void)
{
  int units;
  printf("Enter the number of units consumed: ");
  scanf("%d",&units);
  if(units < 0)
  {
    printf("Invalid input, please enter a positive integer");
    return 1;
  }
  double cost = calculateElectricityBill(units);
  printf("The total electricity bill is: %.2lf", cost);
  return 0;
}