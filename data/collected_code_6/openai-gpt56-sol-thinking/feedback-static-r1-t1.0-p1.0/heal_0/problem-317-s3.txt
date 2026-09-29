#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} RleItem;

typedef struct {
    RleItem *items;
    size_t length;
} RleEncoding;

typedef enum {
    RLE_SUCCESS = 0,
    RLE_INVALID_ARGUMENT,
    RLE_ALLOCATION_FAILURE
} RleStatus;

RleStatus modified_run_length_encode(const int *list, size_t length, RleEncoding *encoding)
{
    RleItem *items;
    size_t input_index;
    size_t output_index;

    if (encoding == NULL) {
        return RLE_INVALID_ARGUMENT;
    }

    encoding->items = NULL;
    encoding->length = 0;

    if (length == 0) {
        return RLE_SUCCESS;
    }

    if (list == NULL || length > SIZE_MAX / sizeof(*items)) {
        return RLE_INVALID_ARGUMENT;
    }

    items = malloc(length * sizeof(*items));
    if (items == NULL) {
        return RLE_ALLOCATION_FAILURE;
    }

    input_index = 0;
    output_index = 0;

    while (input_index < length) {
        size_t run_end = input_index + 1;

        while (run_end < length && list[run_end] == list[input_index]) {
            ++run_end;
        }

        items[output_index].value = list[input_index];
        items[output_index].count = run_end - input_index;
        ++output_index;
        input_index = run_end;
    }

    encoding->items = items;
    encoding->length = output_index;
    return RLE_SUCCESS;
}

void free_rle_encoding(RleEncoding *encoding)
{
    if (encoding != NULL) {
        free(encoding->items);
        encoding->items = NULL;
        encoding->length = 0;
    }
}

static int print_rle_encoding(const RleEncoding *encoding)
{
    size_t index;

    if (encoding == NULL) {
        return 0;
    }

    if (fputc('[', stdout) == EOF) {
        return 0;
    }

    for (index = 0; index < encoding->length; ++index) {
        int result;

        if (index != 0 && fputs(", ", stdout) == EOF) {
            return 0;
        }

        if (encoding->items[index].count == 1) {
            result = printf("%d", encoding->items[index].value);
        } else {
            result = printf("(%zu %d)",
                            encoding->items[index].count,
                            encoding->items[index].value);
        }

        if (result < 0) {
            return 0;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int list[] = {1, 1, 1, 1, 2, 3, 3, 1, 1, 4, 5, 5, 5, 5};
    const size_t length = sizeof(list) / sizeof(list[0]);
    RleEncoding encoding = {NULL, 0};
    RleStatus status;

    status = modified_run_length_encode(list, length, &encoding);
    if (status != RLE_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (!print_rle_encoding(&encoding)) {
        free_rle_encoding(&encoding);
        return EXIT_FAILURE;
    }

    free_rle_encoding(&encoding);
    return EXIT_SUCCESS;
}