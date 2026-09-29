#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    int value;
} EncodedItem;

static EncodedItem *modified_rle(const int *input, size_t length, size_t *out_length)
{
    EncodedItem *result;
    size_t i;
    size_t idx;

    if (input == NULL || out_length == NULL || length == 0U) {
        return NULL;
    }

    result = malloc(length * sizeof(EncodedItem));
    if (result == NULL) {
        return NULL;
    }

    idx = 0U;
    i = 0U;
    while (i < length) {
        int current = input[i];
        int count = 1;
        size_t j = i + 1U;

        while (j < length && input[j] == current) {
            count++;
            j++;
        }

        result[idx].count = count;
        result[idx].value = current;
        idx++;
        i = j;
    }

    *out_length = idx;
    return result;
}

static void print_encoded(const EncodedItem *items, size_t length)
{
    size_t i;

    if (items == NULL) {
        return;
    }

    printf("[");
    for (i = 0U; i < length; i++) {
        if (items[i].count == 1) {
            printf("%d", items[i].value);
        } else {
            printf("(%d, %d)", items[i].count, items[i].value);
        }
        if (i + 1U < length) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    int data[] = {1, 1, 2, 3, 4, 4, 5, 1};
    size_t data_length = sizeof(data) / sizeof(data[0]);
    size_t encoded_length = 0U;
    EncodedItem *encoded;

    encoded = modified_rle(data, data_length, &encoded_length);
    if (encoded == NULL) {
        fprintf(stderr, "Encoding failed\n");
        return EXIT_FAILURE;
    }

    print_encoded(encoded, encoded_length);
    free(encoded);

    return EXIT_SUCCESS;
}