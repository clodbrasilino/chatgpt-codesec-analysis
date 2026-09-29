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
    int count1 = 0;
    int count2 = 0;
    int mismatch10 = 0;
    int mismatch01 = 0;

    for (size_t i = 0; i < len; ++i) {
        if (s1[i] == '1') {
            count1++;
        } else if (s1[i] != '0') {
            return -1;
        }

        if (s2[i] == '1') {
            count2++;
        } else if (s2[i] != '0') {
            return -1;
        }

        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                mismatch10++;
            } else {
                mismatch01++;
            }
        }
    }

    if (count1 != count2) {
        return -1;
    }

    return (mismatch10 / 2) + (mismatch01 / 2);
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <binary_string1> <binary_string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = min_swaps_binary(argv[1], argv[2]);

    if (result == -1) {
        fprintf(stderr, "Invalid input or unequal number of set bits.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}