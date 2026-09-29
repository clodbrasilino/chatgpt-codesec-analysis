#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef enum {
    EXTRACT_SUCCESS = 0,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_OUT_OF_RANGE,
    EXTRACT_ALLOCATION_FAILURE
} ExtractResult;

static ExtractResult extract_contiguous(const int *list,
                                        size_t list_length,
                                        size_t start,
                                        size_t count,
                                        int **result)
{
    int *extracted;

    if (result == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *result = NULL;

    if (count == 0) {
        return EXTRACT_SUCCESS;
    }

    if (list == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    if (start > list_length || count > list_length - start) {
        return EXTRACT_OUT_OF_RANGE;
    }

    if (count > SIZE_MAX / sizeof(*extracted)) {
        return EXTRACT_ALLOCATION_FAILURE;
    }

    extracted = malloc(count * sizeof(*extracted));
    if (extracted == NULL) {
        return EXTRACT_ALLOCATION_FAILURE;
    }

    memcpy(extracted, list + start, count * sizeof(*extracted));
    *result = extracted;

    return EXTRACT_SUCCESS;
}

int main(void)
{
    const int list[] = {10, 20, 30, 40, 50, 60, 70};
    const size_t list_length = sizeof(list) / sizeof(list[0]);
    const size_t start = 2;
    const size_t count = 4;
    int *extracted = NULL;
    ExtractResult result;
    size_t i;

    result = extract_contiguous(list, list_length, start, count, &extracted);
    if (result != EXTRACT_SUCCESS) {
        if (fprintf(stderr, "Extraction failed with error code %d\n", result) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (printf("%d%s", extracted[i], i + 1 == count ? "\n" : " ") < 0) {
            free(extracted);
            return EXIT_FAILURE;
        }
    }

    free(extracted);
    return EXIT_SUCCESS;
}