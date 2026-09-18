#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple convertToTuple(int* arr, int n) {
    if (n < 2) {
        printf("Array should have at least 2 elements\n");
        exit(0);
    }
    Tuple t;
    t.first = arr[0];
    t.second = arr[1];
    return t;
}

int main() {
    int arr[2] = {1, 2};
    Tuple t = convertToTuple(arr, 2);
    printf("Tuple elements are %d and %d\n", t.first, t.second);
    return 0;
}