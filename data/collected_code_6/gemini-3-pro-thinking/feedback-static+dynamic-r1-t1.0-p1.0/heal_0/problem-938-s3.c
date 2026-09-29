#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_minimum(int a, int b, int c);
int find_maximum(int a, int b, int c);
int find_three_closest(const int *arr1, size_t size1, 
                       const int *arr2, size_t size2, 
                       const int *arr3, size_t size3, 
                       int *res1, int *res2, int *res3);

int find_minimum(int a, int b, int c) {
    int min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}

int find_maximum(int a, int b, int c) {
    int max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

int find_three_closest(const int *arr1, size_t size1, 
                       const int *arr2, size_t size2, 
                       const int *arr3, size_t size3, 
                       int *res1, int *res2, int *res3) {
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    long long min_diff = LLONG_MAX;

    if (!arr1 || !arr2 || !arr3 || !res1 || !res2 || !res3) {
        return -1;
    }
    if (size1 == 0 || size2 == 0 || size3 == 0) {
        return -1;
    }

    while (i < size1 && j < size2 && k < size3) {
        int current_min = find_minimum(arr1[i], arr2[j], arr3[k]);
        int current_max = find_maximum(arr1[i], arr2[j], arr3[k]);
        long long diff = (long long)current_max - (long long)current_min;

        if (diff < min_diff) {
            min_diff = diff;
            *res1 = arr1[i];
            *res2 = arr2[j];
            *res3 = arr3[k];
        }

        if (arr1[i] == current_min) {
            i++;
        } else if (arr2[j] == current_min) {
            j++;
        } else {
            k++;
        }
    }
    
    return 0;
}

int main(void) {
    const int arr1[] = {1, 4, 10, 20, 25, 40};
    const int arr2[] = {15, 23, 30, 42};
    const int arr3[] = {10, 16, 24, 32};
    
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    
    int res1 = 0;
    int res2 = 0;
    int res3 = 0;
    
    if (find_three_closest(arr1, size1, arr2, size2, arr3, size3, &res1, &res2, &res3) == 0) {
        printf("%d %d %d\n", res1, res2, res3);
    } else {
        fprintf(stderr, "Invalid input or empty arrays.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}