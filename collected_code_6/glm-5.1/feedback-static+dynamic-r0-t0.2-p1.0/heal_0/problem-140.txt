#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int* extract_singly(Tuple* tuples, int tuple_count, int* result_count) {
    int* elements = (int*)malloc(tuple_count * 2 * sizeof(int));
    if (!elements) {
        *result_count = 0;
        return NULL;
    }

    int elem_count = 0;
    for (int i = 0; i < tuple_count; i++) {
        elements[elem_count++] = tuples[i].first;
        elements[elem_count++] = tuples[i].second;
    }

    int* counts = (int*)calloc(elem_count, sizeof(int));
    if (!counts) {
        free(elements);
        *result_count = 0;
        return NULL;
    }

    for (int i = 0; i < elem_count; i++) {
        for (int j = 0; j < elem_count; j++) {
            if (elements[i] == elements[j]) {
                counts[i]++;
            }
        }
    }

    int* result = (int*)malloc(elem_count * sizeof(int));
    if (!result) {
        free(elements);
        free(counts);
        *result_count = 0;
        return NULL;
    }

    int res_idx = 0;
    for (int i = 0; i < elem_count; i++) {
        if (counts[i] == 1) {
            result[res_idx++] = elements[i];
        }
    }

    free(elements);
    free(counts);

    *result_count = res_idx;
    if (res_idx == 0) {
        free(result);
        return NULL;
    }

    int* final_result = (int*)realloc(result, res_idx * sizeof(int));
    if (!final_result) {
        *result_count = res_idx;
        return result;
    }

    return final_result;
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 2}, {6, 7}};
    int tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    int result_count = 0;

    int* singly_elements = extract_singly(tuples, tuple_count, &result_count);

    if (singly_elements != NULL) {
        for (int i = 0; i < result_count; i++) {
            printf("%d ", singly_elements[i]);
        }
        printf("\n");
        free(singly_elements);
    } else {
        printf("No singly occurring elements found.\n");
    }

    return 0;
}