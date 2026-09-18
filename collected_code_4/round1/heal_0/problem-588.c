#include <stdio.h>
#include <limits.h>

int findDifference(int array[], int size) {
    if (size == 0)
        return 0;

    int minimum = INT_MAX;
    int maximum = INT_MIN;
  
    for(int i = 0; i < size; i++) {
        if(array[i] > maximum) 
            maximum = array[i];
          
        if(array[i] < minimum) 
            minimum = array[i]; 
    }
    return (maximum - minimum);
}

int main() {
  int array[] = {12, 23, 34, 45, 56, 67, 78, 89, 90};
  int size = sizeof(array) / sizeof(array[0]);
  
  printf("%d", findDifference(array, size));

  return 0;
}