#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

int maxAggregate(Tuple* arr, int size) {
    int max = arr[0].a + arr[0].b;
    for(int i = 1; i < size; i++) {
        int sum = arr[i].a + arr[i].b;
        if(sum > max) {
            max = sum;
        }
    }
    return max;
}

int main() {
    Tuple arr[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int size = sizeof(arr) / sizeof(arr[0]);
    int max = maxAggregate(arr, size);
    printf("Maximum aggregate is %d\n", max);
    return 0;
}