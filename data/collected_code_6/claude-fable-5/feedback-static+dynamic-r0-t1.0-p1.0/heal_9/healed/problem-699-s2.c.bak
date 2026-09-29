#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compute_min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    int diff10 = 0;
    int diff01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] == '1' && s2[i] == '0') {
            diff10++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            diff01++;
        }
    }

    if (diff10 != diff01) {
        return -1;
    }

    return diff10;
}

int min_swaps(const char *s1, const char *s2, char *out, size_t out_size)
{
    int result;
    int written;

    if (out == NULL || out_size == 0) {
        return -1;
    }

    result = compute_min_swaps(s1, s2);

    if (result < 0) {
        written = snprintf(out, out_size, "Not Possible");
    } else {
        written = snprintf(out, out_size, "%d", result);
    }

    if (written < 0 || (size_t)written >= out_size) {
        return -1;
    }

    return 0;
}

int print_result(const char *result)
{
    if (result == NULL) {
        return -1;
    }

    if (strcmp(result, "Not Possible") == 0) {
        if (printf("Not Possible\n") < 0) {
            return -1;
        }
    } else {
        if (printf("Minimum swaps required: %s\n", result) < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const char *str1 = "1101";
    const char *str2 = "0011";
    char result[64];

    if (min_swaps(str1, str2, result, sizeof(result)) < 0) {
        if (printf("Not Possible\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (print_result(result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}