#include <stdbool.h>

bool isMonotonic(int arr[], int size) {
    bool increasing = true;
    bool decreasing = true;
      
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            increasing = false;
        }
        if (arr[i] > arr[i - 1]) {
            decreasing = false;
        }
    }
      
    return increasing || decreasing;
}