#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    const int *elements;
    size_t size;
} Sublist;

size_t count_sublists_with_element(const Sublist *sublists, size_t num_sublists, int target);

size_t count_sublists_with_element(const Sublist *sublists, size_t num_sublists, int target) {
    if (sublists == NULL || num_sublists == 0) {
        return 0;
    }

    size_t count = 0;

    for (size_t i = 0; i < num_sublists; ++i) {
        if (sublists[i].elements == NULL || sublists[i].size == 0) {
            continue;
        }

        for (size_t j = 0; j < sublists[i].size; ++j) {
            if (sublists[i].elements[j] == target) {
                count++;
                break;
            }
        }
    }

    return count;
}

int main(void) {
    const int arr1[] = {1, 5, 9, 12};
    const int arr2[] = {3, 7, 8};
    const int arr3[] = {9, 9, 9, 2};
    const int arr4[] = {4, 6, 9};
    const int arr5[] = {1};

    Sublist lists[5];

    lists[0].elements = arr1;
    lists[0].size = sizeof(arr1) / sizeof(arr1[0]);

    lists[1].elements = arr2;
    lists[1].size = sizeof(arr2) / sizeof(arr2[0]);

    lists[2].elements = arr3;
    lists[2].size = sizeof(arr3) / sizeof(arr3[0]);

    lists[3].elements = arr4;
    lists[3].size = sizeof(arr4) / sizeof(arr4[0]);

    lists[4].elements = arr5;
    lists[4].size = sizeof(arr5) / sizeof(arr5[0]);

    int target_element = 9;
    size_t num_sublists = sizeof(lists) / sizeof(lists[0]);
    
    size_t result = count_sublists_with_element(lists, num_sublists, target_element);

    printf("%zu\n", result);

    return 0;
}