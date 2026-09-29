#include <stdio.h>
#include <string.h>

long long minSwaps(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return -1;
    }

    size_t n = strlen(s);
    if (n != strlen(t)) {
        return -1;
    }

    size_t ones_s = 0;
    size_t ones_t = 0;

    for (size_t i = 0; i < n; i++) {
        if ((s[i] != '0' && s[i] != '1') ||
            (t[i] != '0' && t[i] != '1')) {
            return -1;
        }
        if (s[i] == '1') {
            ones_s++;
        }
        if (t[i] == '1') {
            ones_t++;
        }
    }

    if (ones_s != ones_t) {
        return -1;
    }

    size_t i = 0;
    size_t j = 0;
    long long swaps = 0;

    while (i < n && j < n) {
        while (i < n && s[i] != '1') {
            i++;
        }
        while (j < n && t[j] != '1') {
            j++;
        }

        if (i == n || j == n) {
            break;
        }

        swaps += (i > j) ? (long long)(i - j) : (long long)(j - i);
        i++;
        j++;
    }

    return swaps;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: program <binary_string1> <binary_string2>\n");
        return 1;
    }

    long long result = minSwaps(argv[1], argv[2]);
    if (result < 0) {
        fprintf(stderr, "Conversion is not possible\n");
        return 1;
    }

    printf("%lld\n", result);
    return 0;
}