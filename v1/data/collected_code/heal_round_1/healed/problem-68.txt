#include <stdbool.h>

bool isMonotonic(const int arr[], const int size) {
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

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    bool result = isMonotonic(arr, size);

    return result;
}