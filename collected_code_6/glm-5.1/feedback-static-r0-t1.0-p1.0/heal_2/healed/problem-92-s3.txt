#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_undulating(long long num) {
    char buffer[24];
    snprintf(buffer, sizeof(buffer), "%lld", num);
    size_t len = strlen(buffer);

    if (len < 3) {
        return 0;
    }

    for (size_t i = 1; i < len; i++) {
        if (buffer[i] == buffer[i - 1]) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char const * const argv[]) {
    long long number;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    number = strtoll(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_undulating(number)) {
        printf("Undulating\n");
    } else {
        printf("Not undulating\n");
    }

    return EXIT_SUCCESS;
}