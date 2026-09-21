#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_substrings(const char *str, size_t len) {
    int total = 0;

    if (len == 0) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        int sum = 0;
        for (size_t j = i; j < len; j++) {
            sum += str[j] - '0';
            int sub_len = j - i + 1;
            if (sum == sub_len) {
                total++;
            }
        }
    }

    return total;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);

    for (size_t i = 0; i < input_len; i++) {
        if (input[i] < '0' || input[i] > '9') {
            fprintf(stderr, "Error: Input string must contain only digits.\n");
            return EXIT_FAILURE;
        }
    }

    int result = count_substrings(input, input_len);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}