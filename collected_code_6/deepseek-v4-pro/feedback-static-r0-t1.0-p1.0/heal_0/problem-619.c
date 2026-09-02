#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void move_numbers_to_string(const char *input, char *output, size_t output_size) {
    size_t in_len = strlen(input);
    size_t out_pos = 0;
    size_t i = 0;

    if (output_size == 0) return;

    output[0] = '\0';

    while (i < in_len) {
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
    char input[256];
    char output[256];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    move_numbers_to_string(input, output, sizeof(output));

    printf("%s\n", output);

    return EXIT_SUCCESS;
}