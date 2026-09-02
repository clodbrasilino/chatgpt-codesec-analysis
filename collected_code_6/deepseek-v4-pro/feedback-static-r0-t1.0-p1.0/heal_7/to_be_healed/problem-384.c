#include <stdio.h>
#include <stdlib.h>

int frequency_of_smallest(const int *arr, size_t n, int *smallest) {
    if (arr == NULL || n == 0 || smallest == NULL) {
        return -1;
    }

    int min_val = arr[0];
    size_t count = 1;

    for (size_t i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            count = 1;
        } else if (arr[i] == min_val) {
            count++;
        }
    }

    *smallest = min_val;
    return (int)count;
}

int main(void) {
    int arr1[] = {5, 3, 1, 4, 1, 2, 1};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    int smallest1;
    int freq1 = frequency_of_smallest(arr1, n1, &smallest1);
    if (freq1 >= 0) {
        printf("Smallest: %d, Frequency: %d\n", smallest1, freq1);
    }

    int arr2[] = {10, 10, 10};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    int smallest2;
    int freq2 = frequency_of_smallest(arr2, n2, &smallest2);
    if (freq2 >= 0) {
        printf("Smallest: %d, Frequency: %d\n", smallest2, freq2);
    }

    int arr3[] = {42};
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    int smallest3;
    int freq3 = frequency_of_smallest(arr3, n3, &smallest3);
    if (freq3 >= 0) {
        printf("Smallest: %d, Frequency: %d\n", smallest3, freq3);
    }

    /* Possible weaknesses found:
     *  Assignment 'result=frequency_of_smallest(NULL,0,NULL)', assigned value is -1
     *  Calling function 'frequency_of_smallest' returns -1
     */
    int result = frequency_of_smallest(NULL, 0, NULL);
    /* Possible weaknesses found:
     *  Condition 'result==-1' is always true [knownConditionTrueFalse]
     *  Condition 'result==-1' is always true
     */
    if (result == -1) {
        printf("Invalid input handled\n");
    } else {
        printf("Invalid input not handled properly\n");
    }

    return 0;
}