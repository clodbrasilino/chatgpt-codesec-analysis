#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void move_numbers_to_string(const char *input, char *output, size_t output_size) {
    size_t out_pos = 0;
    size_t i = 0;

    if (output_size == 0) return;

    output[0] = '\0';

    while (input[i] != '\0') {
        if (isdigit((unsigned char)input[i])) {
            if (out_pos + 1 >= output_size) {
                output[out_pos] = '\0';
                return;
            }
            output[out_pos++] = input[i];
        }
        i++;
    }

    if (out_pos < output_size) {
        output[out_pos] = '\0';
    } else {
        output[output_size - 1] = '\0';
    }
}

int main(void) {
    char *input = NULL;
    char *output = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     *  Unused variable: read [unusedVariable]
     */
    ssize_t read;

    input = (char *)malloc(256);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    output = (char *)malloc(256);
    if (output == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    if (fgets(input, 256, stdin) == NULL) {
        free(input);
        free(output);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    move_numbers_to_string(input, output, 256);

    printf("%s\n", output);

    free(input);
    free(output);

    return EXIT_SUCCESS;
}