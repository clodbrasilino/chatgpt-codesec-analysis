#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    RLE_SINGLE,
    RLE_RUN
} RleType;

typedef struct {
    size_t count;
    int value;
} RleRun;

typedef struct {
    RleType type;
    union {
        int single;
        RleRun run;
    } data;
} RleItem;

int modified_run_length_encode(const int *input, size_t length, RleItem **output, size_t *output_length)
{
    if (output == NULL || output_length == NULL) {
        return -1;
    }
    if (*output != NULL) {
        return -1;
    }
    if (length > 0 && input == NULL) {
        return -1;
    }

    *output = NULL;
    *output_length = 0;

    if (length == 0) {
        return 0;
    }

    size_t run_count = 0;
    size_t i = 0;

    while (i < length) {
        size_t j = i + 1;
        while (j < length && input[j] == input[i]) {
            ++j;
        }
        ++run_count;
        i = j;
    }

    if (run_count > SIZE_MAX / sizeof(RleItem)) {
        return -1;
    }

    RleItem *items = malloc(run_count * sizeof(RleItem));
    if (items == NULL) {
        return -1;
    }

    i = 0;
    size_t item_index = 0;

    while (i < length) {
        size_t j = i + 1;
        while (j < length && input[j] == input[i]) {
            ++j;
        }

        size_t count = j - i;

        if (count == 1) {
            items[item_index].type = RLE_SINGLE;
            items[item_index].data.single = input[i];
        } else {
            items[item_index].type = RLE_RUN;
            items[item_index].data.run.count = count;
            items[item_index].data.run.value = input[i];
        }

        ++item_index;
        i = j;
    }

    *output = items;
    *output_length = run_count;

    return 0;
}

int main(void)
{
    int input[] = {1, 1, 1, 2, 3, 3, 1};
    size_t input_length = sizeof(input) / sizeof(input[0]);
    RleItem *encoded = NULL;
    size_t encoded_length = 0;

    if (modified_run_length_encode(input, input_length, &encoded, &encoded_length) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < encoded_length; ++i) {
        if (encoded[i].type == RLE_SINGLE) {
            printf("%d", encoded[i].data.single);
        } else {
            printf("[%zu,%d]", encoded[i].data.run.count, encoded[i].data.run.value);
        }

        if (i + 1 < encoded_length) {
            putchar(' ');
        }
    }

    putchar('\n');
    free(encoded);

    return EXIT_SUCCESS;
}