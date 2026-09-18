#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int a;
    int b;
} tuple;

int max_aggregate(tuple* t, size_t len) {
    int max = INT_MIN;
    for(size_t i = 0; i != len; ++i) {
        int sum = t[i].a + t[i].b;
        if(sum < 0 && (INT_MAX + sum < t[i].a || INT_MAX + sum < t[i].b)) {
            printf("Integer overflow, aborting");
            abort();
        }
        if(sum > max) {
            max = sum;
        }
    }
    if (max == INT_MIN) {
        return -1; 
    }
    return max;
}

int main() {
    tuple tuples[] = { {1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10} };
    size_t len = sizeof(tuples) / sizeof(tuple);
    int result = max_aggregate(tuples, len);
    if (result == -1) {
        printf("No valid tuples found\n");
        return 1; 
    }
    printf("The maximum aggregate sum is: %d\n", result);
    return 0;
}