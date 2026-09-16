#include <stdio.h>
#include <stdlib.h>

int* get_last_elements(int** sublists, const int* sublist_sizes, int num_sublists, int* out_size) {
    if (sublists == NULL || sublist_sizes == NULL || num_sublists <= 0 || out_size == NULL) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    int* last_elements = malloc(num_sublists * sizeof(int));
    if (last_elements == NULL) {
        *out_size = 0;
        return NULL;
    }

    for (int i = 0; i < num_sublists; i++) {
        if (sublists[i] != NULL && sublist_sizes[i] > 0) {
            last_elements[i] = sublists[i][sublist_sizes[i] - 1];
        } else {
            last_elements[i] = 0;
        }
    }

    *out_size = num_sublists;
    return last_elements;
}

int main(void) {
    int sub1[] = {1, 2, 3};
    int sub2[] = {4, 5};
    int sub3[] = {6, 7, 8, 9};
    
    int* sublists[] = {sub1, sub2, sub3};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    int sizes[] = {3, 2, 4};
    int num_sublists = 3;
    int out_size = 0;

    int* result = get_last_elements(sublists, sizes, num_sublists, &out_size);

    if (result != NULL) {
        for (int i = 0; i < out_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}