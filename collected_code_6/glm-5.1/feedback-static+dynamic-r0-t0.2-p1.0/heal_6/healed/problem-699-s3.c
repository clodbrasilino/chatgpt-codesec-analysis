#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps_binary(const char *s1, const char *s2) {
    size_t len = strlen(s1);
    if (len != strlen(s2)) {
        return -1;
    }
    if (len == 0) {
        return 0;
    }

    int count1 = 0;
    int count2 = 0;
    int mismatch_1_0 = 0;
    int mismatch_0_1 = 0;

    for (size_t i = 0; i < len; i++) {
        if (s1[i] != '0' && s1[i] != '1') {
            return -1;
        }
        if (s2[i] != '0' && s2[i] != '1') {
            return -1;
        }

        if (s1[i] == '1') {
            count1++;
        }
        if (s2[i] == '1') {
            count2++;
        }

        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                mismatch_1_0++;
            } else {
                mismatch_0_1++;
            }
        }
    }

    if (count1 != count2) {
        return -1;
    }

    return mismatch_1_0;
}

int main(int argc, char * const * const argv) {
    (void)argc;
    if (argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <binary_string1> <binary_string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = min_swaps_binary(argv[1], argv[2]);

    if (result == -1) {
        fprintf(stderr, "Invalid input or unequal number of 1s.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}