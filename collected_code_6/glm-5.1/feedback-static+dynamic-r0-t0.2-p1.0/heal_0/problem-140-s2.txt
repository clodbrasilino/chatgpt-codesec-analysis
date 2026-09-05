#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int* extract_singly(Tuple* tuples, int tuple_count, int* result_count) {
    int total_elements = tuple_count * 2;
    int* elements = (int*)malloc(total_elements * sizeof(int));
    if (!elements) {
        *result_count = 0;
        return NULL;
    }

    for (int i = 0; i < tuple_count; i++) {
        elements[i * 2] = tuples[i].first;
        elements[i * 2 + 1] = tuples[i].second;
    }

    int* singly = (int*)malloc(total_elements * sizeof(int));
    if (!singly) {
        free(elements);
        *result_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < total_elements; i++) {
        int freq = 0;
        for (int j = 0; j < total_elements; j++) {
            if (elements[i] == elements[j]) {
                freq++;
            }
        }
        if (freq == 1) {
            singly[count++] = elements[i];
        }
    }

    free(elements);

    int* final_result = (int*)malloc(count * sizeof(int));
    if (!final_result) {
        free(singly);
        *result_count = 0;
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        final_result[i] = singly[i];
    }

    free(singly);
    *result_count = count;
    return final_result;
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {2, 5}, {6, 1}};
    int tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    int result_count = 0;

    int* singly_elements = extract_singly(tuples, tuple_count, &result_count);

    if (singly_elements) {
        for (int i = 0; i < result_count; i++) {
            printf("%d ", singly_elements[i]);
        }
        printf("\n");
        free(singly_elements);
    }

    return 0;
}