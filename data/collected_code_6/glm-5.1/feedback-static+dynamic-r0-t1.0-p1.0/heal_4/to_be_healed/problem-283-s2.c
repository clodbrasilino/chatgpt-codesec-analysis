#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int check_digit_frequency(const char *input, size_t max_len) {
    if (input == NULL) {
        return 0;
    }

    size_t len = strnlen(input, max_len);
    
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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char const * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = check_digit_frequency(argv[1], 1024);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}