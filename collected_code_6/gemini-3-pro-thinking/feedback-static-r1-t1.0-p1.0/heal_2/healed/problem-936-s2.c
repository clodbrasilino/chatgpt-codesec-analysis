#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char data[64];
} Tuple;

int rearrange_tuples(const Tuple *input, size_t input_len, const int *order, size_t order_len, Tuple **output, size_t *output_len) {
    if (!input || !order || !output || !output_len) {
        return -1;
    }

    if (order_len == 0) {
        *output = NULL;
        *output_len = 0;
        return 0;
    }

    *output = (Tuple *)malloc(order_len * sizeof(Tuple));
    if (!*output) {
        return -1;
    }

    size_t count = 0;
    for (size_t i = 0; i < order_len; i++) {
        for (size_t j = 0; j < input_len; j++) {
            if (input[j].id == order[i]) {
                (*output)[count].id = input[j].id;
                snprintf((*output)[count].data, sizeof((*output)[count].data), "%s", input[j].data);
                count++;
                break;
            }
        }
    }

    if (count == 0) {
        free(*output);
        *output = NULL;
        *output_len = 0;
        return 0;
    }

    if (count < order_len) {
        Tuple *temp = (Tuple *)realloc(*output, count * sizeof(Tuple));
        if (!temp) {
            free(*output);
            *output = NULL;
            return -1;
        }
        *output = temp;
    }

    *output_len = count;
    return 0;
}

int main(void) {
    Tuple input[] = {
        {3, "Apple"},
        {1, "Banana"},
        {4, "Cherry"},
        {2, "Date"}
    };
    size_t input_len = sizeof(input) / sizeof(input[0]);

    int order[] = {2, 4, 1, 3, 5};
    size_t order_len = sizeof(order) / sizeof(order[0]);

    Tuple *output = NULL;
    size_t output_len = 0;

    int status = rearrange_tuples(input, input_len, order, order_len, &output, &output_len);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < output_len; i++) {
        printf("%d: %s\n", output[i].id, output[i].data);
    }

    free(output);
    return EXIT_SUCCESS;
}