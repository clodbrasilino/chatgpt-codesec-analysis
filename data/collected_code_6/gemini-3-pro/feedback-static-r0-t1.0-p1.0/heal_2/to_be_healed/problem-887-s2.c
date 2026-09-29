#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_odd(int number) {
    return (number & 1) != 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *endptr;
        int number = (int)strtol(input, &endptr, 10);

        if (endptr == input || (*endptr != '\n' && *endptr != '\0')) {
            return EXIT_FAILURE;
        }

        if (is_odd(number)) {
            printf("Odd\n");
        } else {
            printf("Even\n");
        }

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}