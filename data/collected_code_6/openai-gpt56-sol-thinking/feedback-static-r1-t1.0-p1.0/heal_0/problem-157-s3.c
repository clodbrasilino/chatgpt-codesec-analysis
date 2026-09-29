#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} RleEntry;

typedef enum {
    RLE_SUCCESS,
    RLE_INVALID_ARGUMENT,
    RLE_ALLOCATION_FAILURE
} RleStatus;

RleStatus run_length_encode(const int *list, size_t length,
                            RleEntry **encoded, size_t *encoded_length)
{
    RleEntry *entries;
    size_t entry_count = 0;
    size_t run_count = 1;

    if (encoded == NULL || encoded_length == NULL) {
        return RLE_INVALID_ARGUMENT;
    }

    *encoded = NULL;
    *encoded_length = 0;

    if (length == 0) {
        return RLE_SUCCESS;
    }

    if (list == NULL || length > SIZE_MAX / sizeof(*entries)) {
        return RLE_INVALID_ARGUMENT;
    }

    entries = malloc(length * sizeof(*entries));
    if (entries == NULL) {
        return RLE_ALLOCATION_FAILURE;
    }

    for (size_t i = 1; i < length; ++i) {
        if (list[i] == list[i - 1]) {
            ++run_count;
        } else {
            entries[entry_count].value = list[i - 1];
            entries[entry_count].count = run_count;
            ++entry_count;
            run_count = 1;
        }
    }

    entries[entry_count].value = list[length - 1];
    entries[entry_count].count = run_count;
    ++entry_count;

    *encoded = entries;
    *encoded_length = entry_count;

    return RLE_SUCCESS;
}

int main(void)
{
    const int list[] = {1, 1, 1, 2, 2, 3, 4, 4, 4, 4, 5};
    const size_t length = sizeof(list) / sizeof(list[0]);
    RleEntry *encoded = NULL;
    size_t encoded_length = 0;

    RleStatus status = run_length_encode(
        list, length, &encoded, &encoded_length
    );

    if (status != RLE_SUCCESS) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < encoded_length; ++i) {
        if (printf("(%d, %zu)\n", encoded[i].value, encoded[i].count) < 0) {
            free(encoded);
            return EXIT_FAILURE;
        }
    }

    free(encoded);
    return EXIT_SUCCESS;
}