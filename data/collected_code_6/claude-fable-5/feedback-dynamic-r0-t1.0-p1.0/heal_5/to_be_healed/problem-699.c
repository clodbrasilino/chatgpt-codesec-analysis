#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    int count10 = 0;
    int count01 = 0;

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
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                count10++;
            } else {
                count01++;
            }
        }
    }

    if (count10 != count01) {
        return -1;
    }

    return count10;
}

int format_result(const char *s1, const char *s2, char *out, size_t out_size)
{
    int result;
    int written;

    if (out == NULL || out_size == 0) {
        return -1;
    }

    result = min_swaps(s1, s2);

    if (result < 0) {
        written = snprintf(out, out_size, "Not Possible");
    } else {
        written = snprintf(out, out_size, "Minimum swaps: %d", result);
    }

    if (written < 0 || (size_t)written >= out_size) {
        out[0] = '\0';
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *a = "1101";
    const char *b = "1011";
    char buffer[64];

    if (format_result(a, b, buffer, sizeof(buffer)) != 0) {
        if (printf("Not Possible\n") < 0) {
            return 1;
        }
        return 0;
    }

    if (printf("%s\n", buffer) < 0) {
        return 1;
    }

    return 0;
}