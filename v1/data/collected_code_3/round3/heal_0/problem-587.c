#include <stdio.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple convertToTuple(int arr[], int n) {
    Tuple t;
    if(n > 0) {
        t.first = arr[0];
    }
    if(n > 1) {
        t.second = arr[1];
    }
    return t;
}

int main() {
    int arr[] = {1, 2};
    Tuple t = convertToTuple(arr, 2);
    printf("Tuple: (%d, %d)\n", t.first, t.second);
    return 0;
}