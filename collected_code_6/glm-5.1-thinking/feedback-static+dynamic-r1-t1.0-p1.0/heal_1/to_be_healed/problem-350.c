#include <stdio.h>
#include <string.h>
#include <limits.h>

int minimizeLength(const char *s) {
    if (s == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    if (len == 0) {
        return 0;
    }
    int freq[UCHAR_MAX + 1] = {0};
    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)s[i]]++;
    }
    int max_freq = 0;
    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
        }
    }
    return (int)(len - max_freq);
}

int main(void) {
    const char *str = "abacaba";
    int result = minimizeLength(str);
    if (result >= 0) {
        printf("Minimal length: %d\n", result);
    } else {
        printf("Error\n");
    }
    return 0;
}