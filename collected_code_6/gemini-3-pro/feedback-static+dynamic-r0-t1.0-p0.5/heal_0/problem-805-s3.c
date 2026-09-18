#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *elements;
    size_t size;
} List;

typedef struct {
    List *lists;
    size_t size;
} ListOfLists;

List* find_max_sum_list(ListOfLists *lol) {
    if (lol == NULL || lol->lists == NULL || lol->size == 0) {
        return NULL;
    }

    List *max_list = NULL;
    long long max_sum = LLONG_MIN;

    for (size_t i = 0; i < lol->size; i++) {
        List *current_list = &lol->lists[i];
        if (current_list->elements == NULL || current_list->size == 0) {
            continue;
        }

        long long current_sum = 0;
        for (size_t j = 0; j < current_list->size; j++) {
            current_sum += current_list->elements[j];
        }

        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_list = current_list;
        }
    }

    return max_list;
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int arr3[] = {-1, -2, -3};

    List lists[3];
    lists[0].elements = arr1;
    lists[0].size = sizeof(arr1) / sizeof(arr1[0]);
    
    lists[1].elements = arr2;
    lists[1].size = sizeof(arr2) / sizeof(arr2[0]);
    
    lists[2].elements = arr3;
    lists[2].size = sizeof(arr3) / sizeof(arr3[0]);

    ListOfLists lol;
    lol.lists = lists;
    lol.size = 3;

    List *max_list = find_max_sum_list(&lol);

    if (max_list != NULL) {
        printf("List with max sum: ");
        for (size_t i = 0; i < max_list->size; i++) {
            printf("%d ", max_list->elements[i]);
        }
        printf("\n");
    } else {
        printf("No valid list found.\n");
    }

    return 0;
}