#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    const int *data;
    size_t length;
} SubList;

const SubList* find_max_length_sublist(const SubList *sublists, size_t count);

const SubList* find_max_length_sublist(const SubList *sublists, size_t count) {
    if (sublists == NULL || count == 0) {
        return NULL;
    }

    const SubList *max_sublist = &sublists[0];

    for (size_t i = 1; i < count; i++) {
        if (sublists[i].length > max_sublist->length) {
            max_sublist = &sublists[i];
        }
    }

    return max_sublist;
}

int main(void) {
    const int arr1[] = {1, 2, 3};
    const int arr2[] = {4, 5, 6, 7, 8};
    const int arr3[] = {9, 10};

    SubList sublists[3];

    sublists[0].data = arr1;
    sublists[0].length = sizeof(arr1) / sizeof(arr1[0]);

    sublists[1].data = arr2;
    sublists[1].length = sizeof(arr2) / sizeof(arr2[0]);

    sublists[2].data = arr3;
    sublists[2].length = sizeof(arr3) / sizeof(arr3[0]);

    const SubList *max_sublist = find_max_length_sublist(sublists, 3);

    if (max_sublist == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < max_sublist->length; i++) {
        printf("%d ", max_sublist->data[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}