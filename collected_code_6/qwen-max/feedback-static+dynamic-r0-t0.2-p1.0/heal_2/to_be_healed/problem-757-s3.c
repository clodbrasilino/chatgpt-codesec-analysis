#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_reverse_pairs(char *strings[], int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len1 = strlen(strings[i]);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len2 = strlen(strings[j]);
            if (len1 == len2) {
                int is_reverse = 1;
                for (size_t k = 0; k < len1; ++k) {
                    if (strings[i][k] != strings[j][len1 - k - 1]) {
                        is_reverse = 0;
                        break;
                    }
                }
                if (is_reverse) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    char *strings[] = {"abc", "cba", "bca", "xyz", "zyx", "yxz"};
    int n = sizeof(strings) / sizeof(strings[0]);
    int result = count_reverse_pairs(strings, n);
    printf("Number of reverse string pairs: %d\n", result);
    return 0;
}