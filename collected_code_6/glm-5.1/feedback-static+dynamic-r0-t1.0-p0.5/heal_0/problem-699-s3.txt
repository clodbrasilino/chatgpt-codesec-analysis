#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps_binary(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        return -1;
    }

    size_t len = len1;
    size_t mismatch0 = 0;
    size_t mismatch1 = 0;

    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0') {
                mismatch0++;
            } else {
                mismatch1++;
            }
        }
    }

    if (mismatch0 != mismatch1) {
        return -1;
    }

    return mismatch0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <binary_string1> <binary_string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strlen(argv[1]) == 0) {
        fprintf(stderr, "Error: Input strings cannot be empty.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < strlen(argv[1]); i++) {
        if (argv[1][i] != '0' && argv[1][i] != '1') {
            fprintf(stderr, "Error: First argument contains non-binary characters.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < strlen(argv[2]); i++) {
        if (argv[2][i] != '0' && argv[2][i] != '1') {
            fprintf(stderr, "Error: Second argument contains non-binary characters.\n");
            return EXIT_FAILURE;
        }
    }

    int result = min_swaps_binary(argv[1], argv[2]);

    if (result == -1) {
        fprintf(stderr, "Error: Strings are not convertible.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}