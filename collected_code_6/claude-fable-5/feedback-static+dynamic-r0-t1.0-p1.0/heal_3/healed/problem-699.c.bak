#include <stdio.h>
#include <string.h>

int min_swaps(const char *s1, const char *s2, char *out, size_t out_size)
{
    size_t len1;
    size_t len2;
    size_t i;
    int count10 = 0;
    int count01 = 0;

    if (out == NULL || out_size == 0) {
        return -1;
    }

    if (s1 == NULL || s2 == NULL) {
        if (snprintf(out, out_size, "Not Possible") < 0) {
            return -1;
        }
        return 0;
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
        if (snprintf(out, out_size, "Not Possible") < 0) {
            return -1;
        }
        return 0;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            if (snprintf(out, out_size, "Not Possible") < 0) {
                return -1;
            }
            return 0;
        }
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                count10++;
            } else {
                count01++;
            }
        }
    }

    if (count10 != count01) {
        if (snprintf(out, out_size, "Not Possible") < 0) {
            return -1;
        }
        return 0;
    }

    if (snprintf(out, out_size, "%d", count10) < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *a = "1101";
    const char *b = "1011";
    char result[64];

    if (min_swaps(a, b, result, sizeof(result)) != 0) {
        return 1;
    }

    if (strcmp(result, "Not Possible") == 0) {
        if (printf("Not Possible\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Minimum swaps: %s\n", result) < 0) {
            return 1;
        }
    }

    return 0;
}