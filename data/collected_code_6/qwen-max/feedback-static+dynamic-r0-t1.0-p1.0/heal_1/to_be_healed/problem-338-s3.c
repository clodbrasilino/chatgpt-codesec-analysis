#include <stdio.h>
#include <string.h>

long countSubstrings(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(str);
    long count = 0;
    int ascii[256] = {0};

    for (int i = 0; i < n; i++) {
        ascii[str[i]]++;
    }

    for (int i = 0; i < 256; i++) {
        if (ascii[i] > 0) {
            count += (ascii[i] * (ascii[i] + 1L)) / 2;
        }
    }

    return count;
}

int main() {
    char str[] = "abcab";
    printf("Total substrings: %ld\n", countSubstrings(str));
    return 0;
}