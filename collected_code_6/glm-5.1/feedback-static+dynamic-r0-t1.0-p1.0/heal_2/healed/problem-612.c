#include <stdio.h>
#include <stdlib.h>

int** merge_first_last(int** lists, const int* list_sizes, int num_lists, int* result_sizes, int* result_count) {
    if (num_lists == 0) {
        *result_count = 0;
        return NULL;
    }

    *result_count = num_lists;
    int** result = (int**)malloc(num_lists * sizeof(int*));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    for (int i = 0; i < num_lists; i++) {
        int current_size = list_sizes[i];
        int new_size = 0;

        if (current_size == 1) {
            new_size = 1;
        } else if (current_size > 1) {
            new_size = 2;
        }

        result_sizes[i] = new_size;
        
        if (new_size == 0) {
            result[i] = NULL;
            continue;
        }

        result[i] = (int*)malloc(new_size * sizeof(int));
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_count = 0;
            return NULL;
        }

        result[i][0] = lists[i][0];
        if (new_size == 2) {
            result[i][1] = lists[i][current_size - 1];
        }
    }

    return result;
}

int main(void) {
    int num_lists = 0;
    
    if (scanf("%d", &num_lists) != 1 || num_lists < 0) {
        return 1;
    }

    int** lists = (int**)malloc(num_lists * sizeof(int*));
    int* list_sizes = (int*)malloc(num_lists * sizeof(int));
    
    if (num_lists > 0 && (lists == NULL || list_sizes == NULL)) {
        free(lists);
        free(list_sizes);
        return 1;
    }

    for (int i = 0; i < num_lists; i++) {
        if (scanf("%d", &list_sizes[i]) != 1) {
            for (int j = 0; j < i; j++) free(lists[j]);
            free(lists);
            free(list_sizes);
            return 1;
        }
        lists[i] = (int*)malloc(list_sizes[i] * sizeof(int));
        if (lists[i] == NULL) {
            for (int j = 0; j < i; j++) free(lists[j]);
            free(lists);
            free(list_sizes);
            return 1;
        }
        for (int j = 0; j < list_sizes[i]; j++) {
            if (scanf("%d", &lists[i][j]) != 1) {
                for (int k = 0; k <= i; k++) free(lists[k]);
                free(lists);
                free(list_sizes);
                return 1;
            }
        }
    }

    int* result_sizes = (int*)malloc(num_lists * sizeof(int));
    int result_count = 0;

    int** result = merge_first_last(lists, list_sizes, num_lists, result_sizes, &result_count);

    if (result == NULL) {
        if (result_count == 0 && num_lists == 0) {
            for (int i = 0; i < num_lists; i++) free(lists[i]);
            free(lists);
            free(list_sizes);
            free(result_sizes);
            return 0;
        }
        for (int i = 0; i < num_lists; i++) free(lists[i]);
        free(lists);
        free(list_sizes);
        free(result_sizes);
        return 1;
    }

    for (int i = 0; i < num_lists; i++) {
        for (int j = 0; j < result_sizes[i]; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
        free(result[i]);
    }
    free(result);

    for (int i = 0; i < num_lists; i++) free(lists[i]);
    free(lists);
    free(list_sizes);
    free(result_sizes);

    return 0;
}