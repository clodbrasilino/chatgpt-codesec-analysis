#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

int findMax(Tuple* arr, int size) {
    int max = arr[0].a > arr[0].b ? arr[0].a : arr[0].b;
    for(int i = 1; i < size; i++) {
        if(arr[i].a > max) {
            max = arr[i].a;
        }
        if(arr[i].b > max) {
            max = arr[i].b;
        }
    }
    return max;
}

int main() {
    Tuple arr[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int size = sizeof(arr) / sizeof(arr[0]);
    int max = findMax(arr, size);
    printf("The maximum element is %d\n", max);
    return 0;
}