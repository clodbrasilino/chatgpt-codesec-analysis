#include <stdio.h>
#include <stdlib.h>

void generate_sublists(const int *list, int size, int **sublists, int *sublist_sizes, int *count) {
    if (list == NULL || sublists == NULL || sublist_sizes == NULL || count == NULL || size < 0) {
        return;
    }

    int total_sublists = 1 << size;
    *count = 0;

    for (int i = 0; i < total_sublists; i++) {
        int current_size = 0;
        for (int j = 0; j < size; j++) {
            if ((i & (1 << j)) != 0) {
                current_size++;
            }
        }

        sublist_sizes[*count] = current_size;
        
        if (current_size > 0) {
            sublists[*count] = (int *)malloc(current_size * sizeof(int));
            if (sublists[*count] == NULL) {
                for (int k = 0; k < *count; k++) {
                    free(sublists[k]);
                }
                *count = 0;
                return;
            }

            int index = 0;
            for (int j = 0; j < size; j++) {
                if ((i & (1 << j)) != 0) {
                    sublists[*count][index++] = list[j];
                }
            }
        } else {
            sublists[*count] = NULL;
        }
        (*count)++;
    }
}

int main(void) {
    int list[] = {1, 2, 3};
    int size = sizeof(list) / sizeof(list[0]);
    int total_sublists = 1 << size;
    
    int **sublists = (int **)malloc(total_sublists * sizeof(int *));
    if (sublists == NULL) {
        return 1;
    }
    
    int *sublist_sizes = (int *)malloc(total_sublists * sizeof(int));
    if (sublist_sizes == NULL) {
        free(sublists);
        return 1;
    }
    
    int count = 0;
    
    generate_sublists(list, size, sublists, sublist_sizes, &count);
    
    if (count == 0 && total_sublists > 0) {
        free(sublists);
        free(sublist_sizes);
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("[");
        for (int j = 0; j < sublist_sizes[i]; j++) {
            printf("%d%s", sublists[i][j], (j < sublist_sizes[i] - 1) ? ", " : "");
        }
        printf("]\n");
    }
    
    for (int i = 0; i < count; i++) {
        free(sublists[i]);
    }
    free(sublists);
    free(sublist_sizes);
    
    return 0;
}