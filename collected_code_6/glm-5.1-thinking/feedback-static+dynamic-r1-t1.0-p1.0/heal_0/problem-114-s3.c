#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} TupleWithFrequency;

int tuples_equal(Tuple t1, Tuple t2) {
    return t1.a == t2.a && t1.b == t2.b;
}

TupleWithFrequency* assign_frequencies(Tuple* tuples, int count, int* result_count) {
    if (tuples == NULL || count <= 0 || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    TupleWithFrequency* result = (TupleWithFrequency*)malloc((size_t)count * sizeof(TupleWithFrequency));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    int* visited = (int*)calloc((size_t)count, sizeof(int));
    if (visited == NULL) {
        free(result);
        *result_count = 0;
        return NULL;
    }

    int result_idx = 0;
    for (int i = 0; i < count; i++) {
        if (visited[i]) {
            continue;
        }
        int freq = 1;
        for (int j = i + 1; j < count; j++) {
            if (!visited[j] && tuples_equal(tuples[i], tuples[j])) {
                freq++;
                visited[j] = 1;
            }
        }
        result[result_idx].tuple = tuples[i];
        result[result_idx].frequency = freq;
        result_idx++;
    }

    *result_count = result_idx;
    free(visited);

    TupleWithFrequency* trimmed = (TupleWithFrequency*)realloc(result, (size_t)result_idx * sizeof(TupleWithFrequency));
    if (trimmed != NULL) {
        result = trimmed;
    }

    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {1, 2}, {5, 6}, {7, 8}
    };
    int count = (int)(sizeof(tuples) / sizeof(tuples[0]));
    int result_count = 0;

    TupleWithFrequency* result = assign_frequencies(tuples, count, &result_count);
    if (result == NULL) {
        fprintf(stderr, "Error assigning frequencies\n");
        return 1;
    }

    for (int i = 0; i < result_count; i++) {
        printf("(%d, %d) -> frequency: %d\n",
               result[i].tuple.a, result[i].tuple.b, result[i].frequency);
    }

    free(result);

    return 0;
}