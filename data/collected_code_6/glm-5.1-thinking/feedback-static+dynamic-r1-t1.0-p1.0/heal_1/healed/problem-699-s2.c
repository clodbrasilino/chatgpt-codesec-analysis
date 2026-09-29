#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 1048576

long long min_swaps_binary(const char *a, const char *b) {
    if (a == NULL || b == NULL) {
        return -1;
    }

    size_t len_a = 0;
    while (len_a < MAX_STR_LEN && a[len_a] != '\0') {
        len_a++;
    }
    if (len_a == MAX_STR_LEN) {
        return -1;
    }

    size_t len_b = 0;
    while (len_b < MAX_STR_LEN && b[len_b] != '\0') {
        len_b++;
    }
    if (len_b == MAX_STR_LEN) {
        return -1;
    }

    if (len_a != len_b) {
        return -1;
    }

    size_t count1_a = 0;
    size_t count1_b = 0;
    size_t m01 = 0;

    for (size_t i = 0; i < len_a; ++i) {
        if ((a[i] != '0' && a[i] != '1') || (b[i] != '0' && b[i] != '1')) {
            return -1;
        }

        if (a[i] == '1') {
            count1_a++;
        }
        if (b[i] == '1') {
            count1_b++;
        }

        if (a[i] == '0' && b[i] == '1') {
            m01++;
        }
    }

    if (count1_a != count1_b) {
        return -1;
    }

    return (long long)m01;
}

int main(void) {
    printf("%lld\n", min_swaps_binary("0101", "1010"));
    printf("%lld\n", min_swaps_binary("1001", "0110"));
    printf("%lld\n", min_swaps_binary("100", "001"));
    printf("%lld\n", min_swaps_binary("110", "001"));
    printf("%lld\n", min_swaps_binary(NULL, "001"));
    printf("%lld\n", min_swaps_binary("10", "011"));
    printf("%lld\n", min_swaps_binary("12", "01"));
    return 0;
}