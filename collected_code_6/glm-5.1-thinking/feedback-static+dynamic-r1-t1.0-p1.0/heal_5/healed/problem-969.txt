#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *t1 = (const Tuple *)a;
    const Tuple *t2 = (const Tuple *)b;
    if (t1->first < t2->first) return -1;
    if (t1->first > t2->first) return 1;
    return 0;
}

int join_tuples(const Tuple *input, int input_size, Tuple **output) {
    if (input == NULL || output == NULL || input_size <= 0) {
        return 0;
    }

    if ((size_t)input_size > SIZE_MAX / sizeof(Tuple)) {
        return 0;
    }

    size_t alloc_size = (size_t)input_size * sizeof(Tuple);

    Tuple *sorted = malloc(alloc_size);
    if (sorted == NULL) {
        return 0;
    }

    memcpy(sorted, input, alloc_size);
    qsort(sorted, input_size, sizeof(Tuple), compare_tuples);

    Tuple *result = malloc(alloc_size);
    if (result == NULL) {
        free(sorted);
        return 0;
    }

    int count = 0;
    result[0].first = sorted[0].first;
    result[0].second = sorted[0].second;

    for (int i = 1; i < input_size; i++) {
        if (sorted[i].first == result[count].first) {
            result[count].second += sorted[i].second;
        } else {
            count++;
            result[count].first = sorted[i].first;
            result[count].second = sorted[i].second;
        }
    }
    count++;

    free(sorted);

    Tuple *trimmed = realloc(result, (size_t)count * sizeof(Tuple));
    if (trimmed != NULL) {
        result = trimmed;
    }

    *output = result;
    return count;
}

int main() {
    Tuple input[] = {
        {1, 2},
        {3, 4},
        {1, 5},
        {2, 6},
        {3, 7},
        {2, 8}
    };
    int input_size = sizeof(input) / sizeof(input[0]);
    Tuple *output = NULL;
    int output_size = join_tuples(input, input_size, &output);

    if (output != NULL) {
        for (int i = 0; i < output_size; i++) {
            printf("(%d, %d)\n", output[i].first, output[i].second);
        }
        free(output);
    }

    return 0;
}