#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} RlePair;

typedef struct {
    RlePair *pairs;
    size_t length;
} RleResult;

static int rle_encode(const int *input, size_t input_len, RleResult *result)
{
    size_t i;
    size_t out_index;
    RlePair *buffer;
    RlePair *shrunk;

    if (result == NULL) {
        return -1;
    }

    result->pairs = NULL;
    result->length = 0;

    if (input == NULL || input_len == 0) {
        return -1;
    }

    if (input_len > SIZE_MAX / sizeof(RlePair)) {
        return -1;
    }

    buffer = malloc(input_len * sizeof(RlePair));
    if (buffer == NULL) {
        return -1;
    }

    out_index = 0;
    buffer[0].value = input[0];
    buffer[0].count = 1;

    for (i = 1; i < input_len; i++) {
        if (input[i] == buffer[out_index].value) {
            buffer[out_index].count++;
        } else {
            out_index++;
            buffer[out_index].value = input[i];
            buffer[out_index].count = 1;
        }
    }

    result->length = out_index + 1;

    shrunk = realloc(buffer, result->length * sizeof(RlePair));
    if (shrunk != NULL) {
        result->pairs = shrunk;
    } else {
        result->pairs = buffer;
    }

    return 0;
}

static void rle_free(RleResult *result)
{
    if (result != NULL) {
        free(result->pairs);
        result->pairs = NULL;
        result->length = 0;
    }
}

int main(void)
{
    int data[] = {1, 1, 2, 2, 2, 3, 4, 4, 4, 4, 5};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    RleResult result;
    size_t i;

    if (rle_encode(data, data_len, &result) != 0) {
        if (fprintf(stderr, "Encoding failed\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < result.length; i++) {
        if (printf("(%d, %zu)\n", result.pairs[i].value, result.pairs[i].count) < 0) {
            rle_free(&result);
            return EXIT_FAILURE;
        }
    }

    rle_free(&result);
    return EXIT_SUCCESS;
}