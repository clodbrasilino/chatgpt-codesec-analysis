#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int roman_value(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

int roman_to_int(const char *s) {
    if (s == NULL) {
        return 0;
    }

    size_t len = strnlen(s, 16);
    if (len == 0) {
        return 0;
    }

    int result = 0;

    for (size_t i = 0; i < len; i++) {
        int current = roman_value(s[i]);
        if (current == 0) {
            return 0;
        }

        if (i + 1 < len) {
            int next = roman_value(s[i + 1]);
            if (next == 0) {
                return 0;
            }

            if (current < next) {
                result -= current;
            } else {
                result += current;
            }
        } else {
            result += current;
        }
    }

    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <roman_numeral>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t input_len = strnlen(argv[1], 16);
    char *buffer = malloc(input_len + 1);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }
    memcpy(buffer, argv[1], input_len + 1);

    int val = roman_to_int(buffer);
    printf("%d\n", val);

    free(buffer);

    return EXIT_SUCCESS;
}