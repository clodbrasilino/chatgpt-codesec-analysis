#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>

typedef struct {
    int *elements;
    size_t size;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

const IntList* find_highest_sum_list(const ListOfLists *list_of_lists);

const IntList* find_highest_sum_list(const ListOfLists *list_of_lists) {
    if (list_of_lists == NULL || list_of_lists->lists == NULL || list_of_lists->count == 0) {
        return NULL;
    }

    const IntList *max_list = NULL;
    long long max_sum = LLONG_MIN;

    for (size_t i = 0; i < list_of_lists->count; i++) {
        const IntList *current_list = &list_of_lists->lists[i];
        
        if (current_list->elements == NULL && current_list->size > 0) {
            continue;
        }

        long long current_sum = 0;
        for (size_t j = 0; j < current_list->size; j++) {
            current_sum += current_list->elements[j];
        }

        if (max_list == NULL || current_sum > max_sum) {
            max_sum = current_sum;
            max_list = current_list;
        }
    }

    return max_list;
}

int main(void) {
    int data1[] = {1, 5, 9};
    int data2[] = {-10, 50, 2};
    int data3[] = {7, 8, 9, 10};
    int data4[] = {0};

    IntList lists[4];
    
    lists[0].elements = data1;
    lists[0].size = sizeof(data1) / sizeof(data1[0]);
    
    lists[1].elements = data2;
    lists[1].size = sizeof(data2) / sizeof(data2[0]);
    
    lists[2].elements = data3;
    lists[2].size = sizeof(data3) / sizeof(data3[0]);
    
    lists[3].elements = data4;
    lists[3].size = sizeof(data4) / sizeof(data4[0]);

    ListOfLists list_of_lists;
    list_of_lists.lists = lists;
    list_of_lists.count = 4;

    const IntList *highest_sum_list = find_highest_sum_list(&list_of_lists);

    if (highest_sum_list != NULL && highest_sum_list->elements != NULL) {
        for (size_t i = 0; i < highest_sum_list->size; i++) {
            printf("%d ", highest_sum_list->elements[i]);
        }
        printf("\n");
    }

    return 0;
}