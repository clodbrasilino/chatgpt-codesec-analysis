#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple convertToTuple(int arr[], int n) {
    Tuple t;
    if(n >= 2) {
        t.a = arr[0];
        t.b = arr[1];
    }
    return t;
}

int main() {
    int arr[] = {1, 2};
    Tuple t = convertToTuple(arr, 2);
    printf("Tuple: (%d, %d)\n", t.a, t.b);
    return 0;
}