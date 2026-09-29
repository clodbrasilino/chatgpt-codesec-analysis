#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1024

void remove_non_alnum(const char *input, char *output, size_t output_size) {
    size_t out_idx = 0;
    size_t i;

    if (input == NULL || output == NULL || output_size == 0) {
        return;
    }

    for (i = 0; input[i] != '\0' && out_idx < output_size - 1; i++) {
        if (isalnum((unsigned char)input[i])) {
            output[out_idx++] = input[i];
        }
    }
    output[out_idx] = '\0';
}

int main(void) {
    char input[MAX_INPUT];
    char output[MAX_INPUT];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    remove_non_alnum(input, output, sizeof(output));

    printf("Result: %s\n", output);

    return EXIT_SUCCESS;
}