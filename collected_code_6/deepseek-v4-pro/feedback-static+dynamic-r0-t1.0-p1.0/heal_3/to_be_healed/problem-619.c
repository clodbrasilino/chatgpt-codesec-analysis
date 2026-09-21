#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void move_numbers_to_string(const char *input, char *output, size_t output_size) {
    size_t i = 0;
    size_t out_pos = 0;

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

    output[out_pos] = '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[256] = {0};

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    move_numbers_to_string(input, output, sizeof(output));

    printf("%s\n", output);

    return EXIT_SUCCESS;
}