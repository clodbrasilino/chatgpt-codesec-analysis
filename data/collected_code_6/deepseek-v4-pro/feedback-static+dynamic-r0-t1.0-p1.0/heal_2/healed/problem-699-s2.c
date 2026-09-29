#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

int min_swaps_to_convert(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    size_t len1 = strnlen(s1, 1025);
    size_t len2 = strnlen(s2, 1025);

    if (len1 != len2) {
        return -1;
    }

    if (len1 == 0) {
        return 0;
    }

    if (len1 > 1024) {
        return -1;
    }

    size_t len = len1;
    int count_s1 = 0;
    int count_s2 = 0;
    int mismatches = 0;
    int ones_mismatch = 0;

    for (size_t i = 0; i < len; i++) {
        if (s1[i] != '0' && s1[i] != '1') {
            return -1;
        }
        if (s2[i] != '0' && s2[i] != '1') {
            return -1;
        }

        if (s1[i] == '1') {
            count_s1++;
        }
        if (s2[i] == '1') {
            count_s2++;
        }
        if (s1[i] != s2[i]) {
            mismatches++;
            if (s1[i] == '1') {
                ones_mismatch++;
            }
        }
    }

    if (count_s1 != count_s2) {
        return -1;
    }

    return ones_mismatch < (mismatches - ones_mismatch) ? ones_mismatch : (mismatches - ones_mismatch);
}

int main(void) {
    int result;
    char *s1 = NULL;
    char *s2 = NULL;
    size_t s1_size = 0;
    size_t s2_size = 0;
    ssize_t s1_read;
    ssize_t s2_read;

    printf("Enter first binary string: ");
    s1_read = getline(&s1, &s1_size, stdin);
    if (s1_read == -1) {
        free(s1);
        return 1;
    }

    if (s1_read > 0 && s1[s1_read - 1] == '\n') {
        s1[s1_read - 1] = '\0';
        s1_read--;
    }

    if ((size_t)s1_read > 1024) {
        free(s1);
        return 1;
    }

    printf("Enter second binary string: ");
    s2_read = getline(&s2, &s2_size, stdin);
    if (s2_read == -1) {
        free(s1);
        free(s2);
        return 1;
    }

    if (s2_read > 0 && s2[s2_read - 1] == '\n') {
        s2[s2_read - 1] = '\0';
        s2_read--;
    }

    if ((size_t)s2_read > 1024) {
        free(s1);
        free(s2);
        return 1;
    }

    result = min_swaps_to_convert(s1, s2);

    if (result == -1) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }

    free(s1);
    free(s2);

    return 0;
}