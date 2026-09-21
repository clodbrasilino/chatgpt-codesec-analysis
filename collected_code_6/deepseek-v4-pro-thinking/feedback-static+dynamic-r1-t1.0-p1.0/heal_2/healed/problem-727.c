#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum remove_status {
    REMOVE_OK = 0,
    REMOVE_EINVAL = -1,
    REMOVE_ESMALLBUF = -2
};

int remove_non_alphanumeric(const char *input, size_t input_len, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size == 0) {
        return REMOVE_EINVAL;
    }

    size_t out_pos = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (isalnum((unsigned char)input[i])) {
            if (out_pos >= output_size - 1) {
                return REMOVE_ESMALLBUF;
            }
            output[out_pos++] = input[i];
        }
    }

    output[out_pos] = '\0';
    return REMOVE_OK;
}

int main(void) {
    const char input[] = "Hello, World! 123";
    size_t input_len = sizeof(input) - 1;
    char *output = malloc(input_len + 1);

    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    int result = remove_non_alphanumeric(input, input_len, output, input_len + 1);
    if (result != REMOVE_OK) {
        fprintf(stderr, "Error: %d\n", result);
        free(output);
        return EXIT_FAILURE;
    }

    printf("%s\n", output);
    free(output);
    return EXIT_SUCCESS;
}