#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

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

    len1 = strnlen(s1, MAX_INPUT_LEN);
    len2 = strnlen(s2, MAX_INPUT_LEN);

    if (len1 >= MAX_INPUT_LEN || len2 >= MAX_INPUT_LEN) {
        return -1;
    }

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

int main(void)
{
    const char *a = "1101";
    const char *b = "1011";
    int result;

    result = min_swaps(a, b);

    if (result < 0) {
        if (printf("Conversion not possible\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Minimum swaps: %d\n", result) < 0) {
            return 1;
        }
    }

    return 0;
}