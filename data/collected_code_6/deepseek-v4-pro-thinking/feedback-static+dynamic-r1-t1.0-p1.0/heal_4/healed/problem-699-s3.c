#include <stdio.h>
#include <string.h>
#include <stddef.h>

static const char *minSwaps(const char *s1, size_t len1, const char *s2, size_t len2) {
    static char buf[64];

    if (s1 == NULL || s2 == NULL) {
        return "Not Possible";
    }

    if (len1 != len2) {
        return "Not Possible";
    }

    size_t ones1 = 0, ones2 = 0, mismatches = 0;

    for (size_t i = 0; i < len1; ++i) {
        if (s1[i] != '0' && s1[i] != '1') return "Not Possible";
        if (s2[i] != '0' && s2[i] != '1') return "Not Possible";

        if (s1[i] == '1') ++ones1;
        if (s2[i] == '1') ++ones2;
        if (s1[i] != s2[i]) ++mismatches;
    }

    if (ones1 != ones2) return "Not Possible";

    size_t swaps = mismatches / 2;
    int written = snprintf(buf, sizeof(buf), "%zu", swaps);
    if (written < 0 || (size_t)written >= sizeof(buf)) {
        return "Error";
    }
    return buf;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: program <binary_string1> <binary_string2>\n");
        return 1;
    }

    printf("%s\n", minSwaps(argv[1], strlen(argv[1]), argv[2], strlen(argv[2])));
    return 0;
}