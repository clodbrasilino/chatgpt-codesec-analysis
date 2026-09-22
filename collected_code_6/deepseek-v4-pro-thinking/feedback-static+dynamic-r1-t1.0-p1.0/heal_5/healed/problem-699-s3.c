#include <stdio.h>
#include <string.h>
#include <stddef.h>

static long long minSwaps(const char *s1, size_t len1, const char *s2, size_t len2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }
    if (len1 != len2) {
        return -1;
    }

    size_t ones1 = 0, ones2 = 0, mismatches = 0;

    for (size_t i = 0; i < len1; ++i) {
        if (s1[i] != '0' && s1[i] != '1') return -1;
        if (s2[i] != '0' && s2[i] != '1') return -1;

        if (s1[i] == '1') ++ones1;
        if (s2[i] == '1') ++ones2;
        if (s1[i] != s2[i]) ++mismatches;
    }

    if (ones1 != ones2) return -1;

    size_t swaps = mismatches / 2;
    return (long long)swaps;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: program <binary_string1> <binary_string2>\n");
        return 1;
    }

    long long result = minSwaps(argv[1], strlen(argv[1]), argv[2], strlen(argv[2]));
    if (result < 0) {
        printf("Not Possible\n");
    } else {
        printf("%lld\n", result);
    }
    return 0;
}