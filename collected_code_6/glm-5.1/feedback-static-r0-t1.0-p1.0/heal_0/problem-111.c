#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} InnerList;

typedef struct {
    InnerList *lists;
    int size;
} NestedList;

int *find_common_elements(NestedList nested, int *result_size) {
    if (nested.size == 0) {
        *result_size = 0;
        return NULL;
    }

    int max_val = 0;
    for (int i = 0; i < nested.size; i++) {
        for (int j = 0; j < nested.lists[i].size; j++) {
            if (nested.lists[i].data[j] > max_val) {
                max_val = nested.lists[i].data[j];
            }
        }
    }

    int *counts = (int *)calloc(max_val + 1, sizeof(int));
    if (counts == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < nested.size; i++) {
        int *seen = (int *)calloc(max_val + 1, sizeof(int));
        if (seen == NULL) {
            free(counts);
            *result_size = 0;
            return NULL;
        }
        for (int j = 0; j < nested.lists[i].size; j++) {
            int val = nested.lists[i].data[j];
            if (seen[val] == 0) {
                counts[val]++;
                seen[val] = 1;
            }
        }
        free(seen);
    }

    int capacity = 10;
    int *result = (int *)malloc(capacity * sizeof(int));
    if (result == NULL) {
        free(counts);
        *result_size = 0;
        return NULL;
    }

    *result_size = 0;
    for (int i = 0; i <= max_val; i++) {
        if (counts[i] == nested.size) {
            if (*result_size >= capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(result, capacity * sizeof(int));
                if (temp == NULL) {
                    free(counts);
                    free(result);
                    *result_size = 0;
                    return NULL;
                }
                result = temp;
            }
            result[*result_size] = i;
            (*result_size)++;
        }
    }

    free(counts);

    if (*result_size == 0) {
        free(result);
        return NULL;
    }

    int *final_result = (int *)realloc(result, *result_size * sizeof(int));
    if (final_result != NULL) {
        return final_result;
    }
    
    return result;
}

int main() {
    int a1[] = {1, 2, 3, 4, 5};
    int a2[] = {4, 5, 6, 1};
    int a3[] = {1, 5, 9, 4};

    InnerList lists[] = {
        {a1, 5},
        {a2, 4},
        {a3, 4}
    };
    NestedList nested = {lists, 3};

    int result_size = 0;
    int *common = find_common_elements(nested, &result_size);

    for (int i = 0; i < result_size; i++) {
        printf("%d ", common[i]);
    }
    printf("\n");

    free(common);

    return 0;
}