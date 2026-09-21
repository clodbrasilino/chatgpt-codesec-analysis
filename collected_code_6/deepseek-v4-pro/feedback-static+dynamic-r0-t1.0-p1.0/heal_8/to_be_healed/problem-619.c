#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void move_numbers_to_string(const char *input, char *output, size_t output_size) {
    size_t i = 0;
    size_t out_pos = 0;

    if (output == NULL || output_size == 0) {
        return;
    }

    output[0] = '\0';

    if (input == NULL) {
        return;
    }

    while (input[i] != '\0' && out_pos + 1 < output_size) {
        if (isdigit((unsigned char)input[i])) {
            output[out_pos++] = input[i];
        }
        i++;
    }

    output[out_pos] = '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     *  The scope of the variable 'output' can be reduced. [variableScope]
     */
    char output[256];
    size_t input_len;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len >= sizeof(input)) {
        return EXIT_FAILURE;
    }

    input_len = len;

    if (input_len > 0) {
        move_numbers_to_string(input, output, sizeof(output));
        printf("%s\n", output);
    }

    return EXIT_SUCCESS;
}