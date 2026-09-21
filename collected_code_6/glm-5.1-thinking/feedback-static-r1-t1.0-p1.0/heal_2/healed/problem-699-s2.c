#include <stdio.h>
#include <string.h>

long long min_swaps_binary(const char *a, size_t len_a, const char *b, size_t len_b) {
    if (a == NULL || b == NULL) {
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
    printf("%lld\n", min_swaps_binary("0101", sizeof("0101") - 1, "1010", sizeof("1010") - 1));
    printf("%lld\n", min_swaps_binary("1001", sizeof("1001") - 1, "0110", sizeof("0110") - 1));
    printf("%lld\n", min_swaps_binary("100", sizeof("100") - 1, "001", sizeof("001") - 1));
    printf("%lld\n", min_swaps_binary("110", sizeof("110") - 1, "001", sizeof("001") - 1));
    printf("%lld\n", min_swaps_binary(NULL, 0, "001", sizeof("001") - 1));
    printf("%lld\n", min_swaps_binary("10", sizeof("10") - 1, "011", sizeof("011") - 1));
    printf("%lld\n", min_swaps_binary("12", sizeof("12") - 1, "01", sizeof("01") - 1));
    return 0;
}