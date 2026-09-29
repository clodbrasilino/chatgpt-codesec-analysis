#include <stdio.h>
#include <string.h>

long countSubstrings(char *str, size_t len) {
    long count = 0;
    int ascii[256] = {0};

    for (size_t i = 0; i < len; i++) {
        ascii[(unsigned char)str[i]]++;
    }

    for (int i = 0; i < 256; i++) {
        if (ascii[i] > 0) {
            count += (long)ascii[i] * (ascii[i] + 1L) / 2;
        }
    }

    return count;
}

int main() {
    char str[] = "abcab";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    printf("Total substrings: %ld\n", countSubstrings(str, len));
    return 0;
}