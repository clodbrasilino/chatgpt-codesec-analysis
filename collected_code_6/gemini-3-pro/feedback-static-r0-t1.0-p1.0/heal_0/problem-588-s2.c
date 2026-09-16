#include <stdio.h>
#include <limits.h>

int find_difference(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return -1; 
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;

    for (size_t i = 0; i < size; ++i) {
        if (array[i] < min_val) {
            min_val = array[i];
        }
        if (array[i] > max_val) {
            max_val = array[i];
        }
    }

    if (max_val < 0 && min_val > 0) {
        if (max_val - INT_MAX > min_val) {
            return -1;
        }
    } else if (max_val > 0 && min_val < 0) {
        if (max_val > INT_MAX + min_val) {
            return -1;
        }
    }

    return max_val - min_val;
}

int main(void) {
    int arr[] = {12, 9, 30, 4, 15, 7};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int difference = find_difference(arr, size);

    if (difference != -1) {
        printf("The difference between the largest and smallest value is: %d\n", difference);
    } else {
        printf("Invalid array or arithmetic overflow occurred.\n");
    }

    return 0;
}