#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int remove_non_alnum(const char *input, char *output, size_t output_size) {
    size_t out_idx = 0;
    size_t i;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    for (i = 0; input[i] != '\0'; i++) {
        if (isalnum((unsigned char)input[i])) {
            if (out_idx + 1 >= output_size) {
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
    char output[256];

    if (remove_non_alnum(input, output, sizeof(output)) == 0) {
        printf("Original: %s\n", input);
        printf("Filtered: %s\n", output);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}