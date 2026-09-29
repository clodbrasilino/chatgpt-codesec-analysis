#include <stdio.h>
#include <string.h>

static const char* minSwaps(const char *s1, const char *s2) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static char buf[32];

    if (s1 == NULL || s2 == NULL) {
        return "Not Possible";
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);

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

    printf("%s\n", minSwaps(argv[1], argv[2]));
    return 0;
}