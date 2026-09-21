#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_odd(int number) {
    return (number & 1) != 0;
}

int main(void) {
    char *input = NULL;
    size_t len = 0;

    if (getline(&input, &len, stdin) != -1) {
        char *endptr;
        long parsed_val = strtol(input, &endptr, 10);

        if (endptr == input || (*endptr != '\n' && *endptr != '\0')) {
            free(input);
            return EXIT_FAILURE;
        }

        int number = (int)parsed_val;

        if (is_odd(number)) {
            printf("Odd\n");
        } else {
            printf("Even\n");
        }

        free(input);
        return EXIT_SUCCESS;
    }

    free(input);
    return EXIT_FAILURE;
}