#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int find_max_difference(const char *binary_string) {
    if (binary_string == NULL) {
        return -1;
    }

    size_t length = strlen(binary_string);
    if (length == 0) {
        return -1;
    }

    int max_diff = 0;
    int current_diff = 0;

    for (size_t i = 0; i < length; ++i) {
        int val = (binary_string[i] == '0') ? 1 : -1;

        current_diff += val;

        if (current_diff > max_diff) {
            max_diff = current_diff;
        }

        if (current_diff < 0) {
            current_diff = 0;
        }
    }

    if (max_diff == 0) {
        int has_zero = 0;
        for (size_t i = 0; i < length; ++i) {
            if (binary_string[i] == '0') {
                has_zero = 1;
                break;
            }
        }
        if (!has_zero) {
            return -1;
        }
    }

    return max_diff;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_string = argv[1];
    size_t valid_length = 0;
    for (size_t i = 0; input_string[i] != '\0'; ++i) {
        if (input_string[i] != '0' && input_string[i] != '1') {
            fprintf(stderr, "Invalid character detected in input. Only '0' and '1' are allowed.\n");
            return EXIT_FAILURE;
        }
        valid_length++;
        if (valid_length > SIZE_MAX - 1) {
            fprintf(stderr, "Input string too long.\n");
            return EXIT_FAILURE;
        }
    }

    int result = find_max_difference(input_string);

    if (result == -1) {
        printf("No valid substring with more 0s than 1s exists.\n");
    } else {
        printf("Maximum difference between 0s and 1s: %d\n", result);
    }

    return EXIT_SUCCESS;
}