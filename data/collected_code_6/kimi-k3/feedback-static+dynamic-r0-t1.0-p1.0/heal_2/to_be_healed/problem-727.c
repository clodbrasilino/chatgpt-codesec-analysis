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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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