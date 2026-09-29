#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} List;

List* findMaxSumList(List lists[], size_t n) {
    if (n == 0) return NULL;

    List *maxList = &lists[0];
    int maxSum = 0;

    for (size_t i = 0; i < n; ++i) {
        int sum = 0;
        for (size_t j = 0; j < lists[i].size; ++j) {
            sum += lists[i].elements[j];
        }
        if (sum > maxSum) {
            maxSum = sum;
            maxList = &lists[i];
        }
    }

    return maxList;
}

int main() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6, 7};
    int arr3[] = {-1, -2, -3};
    int arr4[] = {8, 9};

    List lists[] = {
        {arr1, 3},
        {arr2, 4},
        {arr3, 3},
        {arr4, 2}
    };

    size_t n = sizeof(lists) / sizeof(lists[0]);

    List *maxList = findMaxSumList(lists, n);

    if (maxList != NULL) {
        printf("Max Sum List: ");
        for (size_t i = 0; i < maxList->size; ++i) {
            printf("%d ", maxList->elements[i]);
        }
        printf("\n");
    } else {
        printf("No list found.\n");
    }

    return 0;
}