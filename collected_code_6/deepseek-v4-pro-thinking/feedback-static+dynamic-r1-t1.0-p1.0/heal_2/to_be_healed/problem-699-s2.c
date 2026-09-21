#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

long long minSwaps(const char *s, const char *t) {
    if (s == NULL || t == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(s);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (n != strlen(t)) {
        return -1;
    }
    size_t ones_s = 0;
    size_t ones_t = 0;
    size_t mismatches = 0;
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
        if (s[i] != t[i]) {
            mismatches++;
        }
    }
    if (ones_s != ones_t) {
        return -1;
    }
    return (long long)mismatches / 2;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: program <binary_string1> <binary_string2>\n");
        return 1;
    }
    long long result = minSwaps(argv[1], argv[2]);
    if (result < 0) {
        printf("Not Possible\n");
        return 0;
    }
    printf("%lld\n", result);
    return 0;
}