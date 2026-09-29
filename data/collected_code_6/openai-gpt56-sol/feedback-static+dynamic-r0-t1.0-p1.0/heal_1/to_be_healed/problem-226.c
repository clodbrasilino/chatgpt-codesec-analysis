#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_odd_indices(char *string)
{
    size_t read_index;
    size_t write_index = 0;

    if (string == NULL) {
        return;
    }

    for (read_index = 0; string[read_index] != '\0'; read_index += 2) {
        string[write_index++] = string[read_index];
    }

    string[write_index] = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    input[strcspn(input, "\n")] = '\0';
    remove_odd_indices(input);

    if (puts(input) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}