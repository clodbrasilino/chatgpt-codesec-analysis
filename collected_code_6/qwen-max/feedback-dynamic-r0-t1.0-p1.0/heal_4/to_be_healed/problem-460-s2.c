#include <stdio.h>
#include <stdlib.h>

int* get_first_elements(int **sublists, int sublist_count, int *sizes) {
    int *firsts = malloc(sublist_count * sizeof(int));
    for (int i = 0; i < sublist_count; ++i) {
        firsts[i] = sizes[i] > 0 ? sublists[i][0] : 0;
    }
    return firsts;
}

void free_sublists(int **sublists, int sublist_count, int *sizes, int *firsts) {
    for (int i = 0; i < sublist_count; ++i) {
        if (sublists[i] != NULL) {
            free(sublists[i]);
        }
    }
    /* Possible weaknesses found:
     * ASan: attempting
     */
    free(sizes);
    free(firsts);
    free(sublists);
}

int main() {
    int sublist_count = 3;
    int sizes[3] = {3, 0, 4};
    int **sublists = (int **)malloc(sublist_count * sizeof(int *));
    
    sublists[0] = (int *)malloc(sizes[0] * sizeof(int));
    sublists[1] = sizes[1] > 0 ? (int *)malloc(sizes[1] * sizeof(int)) : NULL;
    sublists[2] = (int *)malloc(sizes[2] * sizeof(int));
    
    sublists[0][0] = 1; sublists[0][1] = 2; sublists[0][2] = 3;
    sublists[2][0] = 4; sublists[2][1] = 5; sublists[2][2] = 6; sublists[2][3] = 7;
    
    int *firsts = get_first_elements(sublists, sublist_count, sizes);

    for (int i = 0; i < sublist_count; ++i) {
        printf("First of sublist %d: %d\n", i, firsts[i]);
    }

    free_sublists(sublists, sublist_count, sizes, firsts);
    return 0;
}