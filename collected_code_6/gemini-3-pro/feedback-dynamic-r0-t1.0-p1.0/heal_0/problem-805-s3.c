#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int* elements;
    size_t size;
} List;

typedef struct {
    List* lists;
    size_t count;
} ListOfLists;

List* findMaxSumList(const ListOfLists* lol) {
    if (lol == NULL || lol->count == 0 || lol->lists == NULL) {
        return NULL;
    }

    List* maxList = NULL;
    long long maxSum = LLONG_MIN;

    for (size_t i = 0; i < lol->count; ++i) {
        if (lol->lists[i].elements == NULL && lol->lists[i].size > 0) {
            continue;
        }

        long long currentSum = 0;
        for (size_t j = 0; j < lol->lists[i].size; ++j) {
            currentSum += lol->lists[i].elements[j];
        }

        if (maxList == NULL || currentSum > maxSum) {
            maxSum = currentSum;
            maxList = &lol->lists[i];
        }
    }

    return maxList;
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int arr3[] = {-1, 10, 2};

    List lists[3];
    lists[0].elements = arr1;
    lists[0].size = sizeof(arr1) / sizeof(arr1[0]);
    
    lists[1].elements = arr2;
    lists[1].size = sizeof(arr2) / sizeof(arr2[0]);
    
    lists[2].elements = arr3;
    lists[2].size = sizeof(arr3) / sizeof(arr3[0]);

    ListOfLists lol;
    lol.lists = lists;
    lol.count = 3;

    List* result = findMaxSumList(&lol);

    if (result != NULL) {
        printf("List with highest sum: ");
        for (size_t i = 0; i < result->size; ++i) {
            printf("%d ", result->elements[i]);
        }
        printf("\n");
    } else {
        printf("No valid list found.\n");
    }

    return 0;
}