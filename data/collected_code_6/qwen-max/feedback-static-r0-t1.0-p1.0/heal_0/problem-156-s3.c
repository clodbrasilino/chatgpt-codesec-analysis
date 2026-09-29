#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* string_tuple_to_int(const char *str[], size_t len, size_t *out_len) {
    int *result = (int *)malloc(len * sizeof(int));
    if (!result) return NULL;
    *out_len = 0;

    for (size_t i = 0; i < len; ++i) {
        char *endptr;
        long tmp = strtol(str[i], &endptr, 10);
        if (tmp == 0 && endptr == str[i]) {
            free(result);
            return NULL;
        }
        result[(*out_len)++] = (int)tmp;
    }
    return result;
}

void free_int_tuple(int *tuple) {
    free(tuple);
}

int main() {
    const char *input[] = {"123", "456", "789"};
    size_t input_len = 3;
    size_t output_len;

    int *output = string_tuple_to_int(input, input_len, &output_len);

    if (output == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < output_len; ++i) {
        printf("%d ", output[i]);
    }
    printf("\n");

    free_int_tuple(output);
    return EXIT_SUCCESS;
}