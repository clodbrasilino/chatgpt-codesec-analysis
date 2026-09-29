#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

int min_swaps_to_equal(const char *s1, const char *s2)
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
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] == '1' && s2[i] == '0') {
            count10++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            count01++;
        }
    }

    if ((count10 % 2) != (count01 % 2)) {
        return -1;
    }

    return (count10 / 2) + (count01 / 2) + ((count10 % 2) * 2);
}

int main(void)
{
    const char *a1 = "1101";
    const char *b1 = "0011";
    const char *a2 = "1110000";
    const char *b2 = "0001111";
    const char *a3 = "10";
    const char *b3 = "01";
    const char *a4 = "110";
    const char *b4 = "001";
    int result;

    result = min_swaps_to_equal(a1, b1);
    if (printf("Strings: %s, %s -> Result: %d\n", a1, b1, result) < 0) {
        return 1;
    }

    result = min_swaps_to_equal(a2, b2);
    if (printf("Strings: %s, %s -> Result: %d\n", a2, b2, result) < 0) {
        return 1;
    }

    result = min_swaps_to_equal(a3, b3);
    if (printf("Strings: %s, %s -> Result: %d\n", a3, b3, result) < 0) {
        return 1;
    }

    result = min_swaps_to_equal(a4, b4);
    if (printf("Strings: %s, %s -> Result: %d\n", a4, b4, result) < 0) {
        return 1;
    }

    return 0;
}