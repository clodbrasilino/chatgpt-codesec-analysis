#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int check_digit_frequency(const char *input) {
    if (input == NULL) {
        return 0;
    }

    size_t len = strlen(input);
    if (len == 0) {
        return 1;
    }

    size_t counts[10] = {0};

    for (size_t i = 0; i < len; i++) {
        if (isdigit((unsigned char)input[i])) {
            size_t digit = input[i] - '0';
            if (counts[digit] < SIZE_MAX) {
                counts[digit]++;
            }
        }
    }

    for (size_t i = 0; i < 10; i++) {
        if (counts[i] > i) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = check_digit_frequency(argv[1]);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}