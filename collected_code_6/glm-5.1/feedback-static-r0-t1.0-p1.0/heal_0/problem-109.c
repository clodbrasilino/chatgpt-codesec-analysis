#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *str) {
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    size_t ones = 0;
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == '1') {
            ones++;
        }
    }

    int count = 0;
    if (ones % 2 != 0) {
        count++;
    }

    size_t hamming_dist = ones;
    for (size_t i = 1; i < len; ++i) {
        if (str[i - 1] == '1' && str[i] == '0') {
            hamming_dist--;
        }
        if (str[i - 1] == '0' && str[i] == '1') {
            hamming_dist++;
        }
        if (hamming_dist % 2 != 0) {
            count++;
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    size_t len = strlen(input);

    for (size_t i = 0; i < len; ++i) {
        if (input[i] != '0' && input[i] != '1') {
            fprintf(stderr, "Error: Input must be a binary string.\n");
            return EXIT_FAILURE;
        }
    }

    int result = count_odd_rotations(input);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}