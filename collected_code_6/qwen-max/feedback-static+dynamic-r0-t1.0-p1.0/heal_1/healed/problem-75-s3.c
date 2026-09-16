#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
} Tuple;

int isDivisibleByK(int num, int k) {
    return num % k == 0;
}

int isTupleDivisibleByK(Tuple t, int k) {
    for (int i = 0; i < t.size; ++i) {
        if (!isDivisibleByK(t.arr[i], k)) {
            return 0;
        }
    }
    return 1;
}

void freeTuple(Tuple t) {
    free(t.arr);
}

int main() {
    int arr1[] = {3, 6, 9};
    int arr2[] = {2, 4, 8, 16};
    int arr3[] = {5, 10, 15, 20, 25};
    int arr4[] = {1, 2, 3, 4, 5};

    Tuple tuples[] = {
        {arr1, 3},
        {arr2, 4},
        {arr3, 5},
        {arr4, 5}
    };

    int n = sizeof(tuples) / sizeof(tuples[0]);
    int k = 5;

    for (int i = 0; i < n; ++i) {
        if (isTupleDivisibleByK(tuples[i], k)) {
            for (int j = 0; j < tuples[i].size; ++j) {
                printf("%d ", tuples[i].arr[j]);
            }
            printf("\n");
        }
    }

    return 0;
}