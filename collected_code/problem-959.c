
#include <stdio.h>

float findAverage(int list[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += list[i];
  }
  float average = (float)sum / size;
  return average;
}

int main() {
  int list[] = {1, 2, 3, 4, 5};
  int size = sizeof(list) / sizeof(list[0]);
  float average = findAverage(list, size);
  printf("The average is: %.2f\n", average);
  return 0;
}