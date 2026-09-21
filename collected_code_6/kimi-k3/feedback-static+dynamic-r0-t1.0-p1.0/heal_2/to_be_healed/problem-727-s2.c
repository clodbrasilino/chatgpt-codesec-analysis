#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int remove_non_alnum(const char *input, char *output, size_t output_size) {
    size_t i;
    size_t out_idx = 0;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    for (i = 0; input[i] != '\0'; i++) {
        if (isalnum((unsigned char)input[i])) {
            if (out_idx + 1 >= output_size) {
                output[0] = '\0';
                return -1;
            }
            output[out_idx++] = input[i];
        }
    }

    output[out_idx] = '\0';
    return 0;
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output;
    size_t input_len;
    size_t output_size;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    output_size = input_len + 1;

    output = malloc(output_size);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (remove_non_alnum(input, output, output_size) == 0) {
        printf("Original: %s\n", input);
        printf("Filtered: %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error processing string\n");
        free(output);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}