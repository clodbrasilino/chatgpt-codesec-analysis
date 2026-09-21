#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 4096U

long min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    long count01;
    long count10;

    if (s1 == NULL || s2 == NULL) {
        return -1L;
    }

    len1 = strnlen(s1, MAX_INPUT_LEN);
    len2 = strnlen(s2, MAX_INPUT_LEN);

    if (len1 >= MAX_INPUT_LEN || len2 >= MAX_INPUT_LEN) {
        return -1L;
    }

    if (len1 != len2) {
        return -1L;
    }

    count01 = 0L;
    count10 = 0L;

    for (i = 0U; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return -1L;
        }
        if (s1[i] == '0' && s2[i] == '1') {
            count01++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            count10++;
        }
    }

    if (count01 != count10) {
        return -1L;
    }

    return count01;
}

int main(void)
{
    const char *a = "1101";
    const char *b = "1011";
    long result;

    result = min_swaps(a, b);

    if (result < 0L) {
        if (printf("Conversion not possible\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Minimum swaps required: %ld\n", result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}