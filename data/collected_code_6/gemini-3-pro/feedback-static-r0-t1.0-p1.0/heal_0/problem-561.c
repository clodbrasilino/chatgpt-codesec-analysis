#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int value;
} Pair;

typedef struct {
    int current_element;
    int* paired_elements;
    int paired_count;
} ResultElement;

ResultElement* assign_pair_elements(Pair* tuple, int size, int* out_size) {
    if (tuple == NULL || size <= 0 || out_size == NULL) {
        return NULL;
    }

    ResultElement* result = (ResultElement*)malloc(size * sizeof(ResultElement));
    if (result == NULL) {
        return NULL;
    }

    int unique_keys = 0;
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < unique_keys; j++) {
            if (result[j].current_element == tuple[i].key) {
                found = 1;
                int count = result[j].paired_count;
                int* new_paired = (int*)realloc(result[j].paired_elements, (count + 1) * sizeof(int));
                if (new_paired == NULL) {
                    for (int k = 0; k < unique_keys; k++) {
                        free(result[k].paired_elements);
                    }
                    free(result);
                    return NULL;
                }
                result[j].paired_elements = new_paired;
                result[j].paired_elements[count] = tuple[i].value;
                result[j].paired_count++;
                break;
            }
        }
        if (!found) {
            result[unique_keys].current_element = tuple[i].key;
            result[unique_keys].paired_elements = (int*)malloc(sizeof(int));
            if (result[unique_keys].paired_elements == NULL) {
                for (int k = 0; k < unique_keys; k++) {
                    free(result[k].paired_elements);
                }
                free(result);
                return NULL;
            }
            result[unique_keys].paired_elements[0] = tuple[i].value;
            result[unique_keys].paired_count = 1;
            unique_keys++;
        }
    }

    *out_size = unique_keys;
    return result;
}

int main() {
    Pair tuple[] = {
        {1, 2},
        {3, 4},
        {1, 5},
        {3, 6},
        {7, 8}
    };
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int out_size = 0;

    ResultElement* result = assign_pair_elements(tuple, size, &out_size);

    if (result != NULL) {
        for (int i = 0; i < out_size; i++) {
            printf("{%d, [", result[i].current_element);
            for (int j = 0; j < result[i].paired_count; j++) {
                printf("%d", result[i].paired_elements[j]);
                if (j < result[i].paired_count - 1) {
                    printf(", ");
                }
            }
            printf("]}\n");
        }

        for (int i = 0; i < out_size; i++) {
            free(result[i].paired_elements);
        }
        free(result);
    }

    return 0;
}