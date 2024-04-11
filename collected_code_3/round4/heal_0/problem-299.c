#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

int maxAggregate(Tuple arr[], int n) {
    int max = arr[0].a + arr[0].b;
    for(int i = 1; i < n; i++) {
        int sum = arr[i].a + arr[i].b;
        if(sum > max) {
            max = sum;
        }
    }
    return max;
}

int main() {
    Tuple arr[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum aggregate is %d\n", maxAggregate(arr, n));
    return 0;
}