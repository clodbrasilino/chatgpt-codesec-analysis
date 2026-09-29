#include <stdio.h>
#include <stdlib.h>

int* get_last_elements(int** sublists, const int* sizes, int num_sublists) {
    if (sublists == NULL || sizes == NULL || num_sublists <= 0) {
        return NULL;
    }

    int* last_elements = (int*)malloc((size_t)num_sublists * sizeof(int));
    if (last_elements == NULL) {
        return NULL;
    }

    for (int i = 0; i < num_sublists; i++) {
        if (sublists[i] == NULL || sizes[i] <= 0) {
            free(last_elements);
            return NULL;
        }
        last_elements[i] = sublists[i][sizes[i] - 1];
    }

    return last_elements;
}

int main(void) {
    int num_sublists = 3;
    int** sublists = (int**)malloc((size_t)num_sublists * sizeof(int*));
    if (sublists == NULL) {
        return 1;
    }

    int sizes[] = {3, 2, 4};
    int allocation_failed = 0;

    for (int i = 0; i < num_sublists; i++) {
        sublists[i] = (int*)malloc((size_t)sizes[i] * sizeof(int));
        if (sublists[i] == NULL) {
            allocation_failed = 1;
            for (int j = 0; j < i; j++) {
                free(sublists[j]);
            }
            break;
        }
    }

    if (allocation_failed != 0) {
        free(sublists);
        return 1;
    }

    sublists[0][0] = 10; 
    sublists[0][1] = 20; 
    sublists[0][2] = 30;

    sublists[1][0] = 40; 
    sublists[1][1] = 50;

    sublists[2][0] = 60; 
    sublists[2][1] = 70; 
    sublists[2][2] = 80; 
    sublists[2][3] = 90;

    int* last_elements = get_last_elements(sublists, sizes, num_sublists);

    if (last_elements != NULL) {
        for (int i = 0; i < num_sublists; i++) {
            printf("%d\n", last_elements[i]);
        }
        free(last_elements);
    }

    for (int i = 0; i < num_sublists; i++) {
        free(sublists[i]);
    }
    free(sublists);

    return 0;
}