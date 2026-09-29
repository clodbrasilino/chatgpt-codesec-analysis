#include <stdio.h>
#include <stdlib.h>

int* get_first_elements(int** list, int size, int* sizes) {
    int *result = malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * UBSan: load of misaligned address 0x000200000001 for type 'int', which requires 4 byte alignment
         * ASan: SEGV
         */
        result[i] = list[i][0];
    }
    return result;
}

int main() {
    int size = 3;
    int *sizes = (int[]){3, 2, 4};
    int **list = (int**){
        (int[]){1, 2, 3},
        (int[]){4, 5},
        (int[]){6, 7, 8, 9}
    };
    
    int *first_elements = get_first_elements(list, size, sizes);
    if (first_elements != NULL) {
        for (int i = 0; i < size; i++) {
            printf("%d ", first_elements[i]);
        }
        free(first_elements);
    }
    return 0;
}