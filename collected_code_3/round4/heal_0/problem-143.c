#include <stdio.h>

struct Tuple {
    int arr1[10];
    int arr2[10];
    int arr3[10];
};

int count_arrays_in_tuple() {
    return sizeof(struct Tuple) / sizeof(int[10]);
}

int main() {
    printf("Number of arrays in tuple: %d\n", count_arrays_in_tuple());
    return 0;
}