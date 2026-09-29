#include <stdio.h>
#include <stdlib.h>

struct InputTuple {
    int first;
    int second;
};

struct OutputTuple {
    int first;
    int *seconds;
    size_t count;
};

struct OutputTupleArray {
    struct OutputTuple *tuples;
    size_t count;
};

struct OutputTupleArray join_tuples(const struct InputTuple *inputs, size_t input_count) {
    struct OutputTupleArray result = {NULL, 0};

    if (!inputs || input_count == 0) {
        return result;
    }

    result.tuples = malloc(input_count * sizeof(struct OutputTuple));
    if (!result.tuples) {
        return result;
    }

    for (size_t i = 0; i < input_count; i++) {
        int found = 0;
        for (size_t j = 0; j < result.count; j++) {
            if (result.tuples[j].first == inputs[i].first) {
                int *new_seconds = realloc(result.tuples[j].seconds, (result.tuples[j].count + 1) * sizeof(int));
                if (!new_seconds) {
                    goto error_cleanup;
                }
                result.tuples[j].seconds = new_seconds;
                result.tuples[j].seconds[result.tuples[j].count] = inputs[i].second;
                result.tuples[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            result.tuples[result.count].first = inputs[i].first;
            result.tuples[result.count].seconds = malloc(sizeof(int));
            if (!result.tuples[result.count].seconds) {
                goto error_cleanup;
            }
            result.tuples[result.count].seconds[0] = inputs[i].second;
            result.tuples[result.count].count = 1;
            result.count++;
        }
    }

    struct OutputTuple *shrunk_tuples = realloc(result.tuples, result.count * sizeof(struct OutputTuple));
    if (shrunk_tuples) {
        result.tuples = shrunk_tuples;
    }

    return result;

error_cleanup:
    for (size_t k = 0; k < result.count; k++) {
        free(result.tuples[k].seconds);
    }
    free(result.tuples);
    result.tuples = NULL;
    result.count = 0;
    return result;
}

void free_output_tuples(struct OutputTupleArray *array) {
    if (!array || !array->tuples) {
        return;
    }
    for (size_t i = 0; i < array->count; i++) {
        free(array->tuples[i].seconds);
    }
    free(array->tuples);
    array->tuples = NULL;
    array->count = 0;
}

int main(void) {
    struct InputTuple inputs[] = {
        {1, 2},
        {1, 3},
        {2, 4},
        {3, 5},
        {2, 6}
    };
    size_t input_count = sizeof(inputs) / sizeof(inputs[0]);

    struct OutputTupleArray result = join_tuples(inputs, input_count);

    if (!result.tuples && input_count > 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result.count; i++) {
        printf("(%d", result.tuples[i].first);
        for (size_t j = 0; j < result.tuples[i].count; j++) {
            printf(", %d", result.tuples[i].seconds[j]);
        }
        printf(")\n");
    }

    free_output_tuples(&result);

    return EXIT_SUCCESS;
}