#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canRearrange(const char *s, size_t n) {
    int count[26] = {0};

    for (size_t i = 0; i < n; ++i) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            count[s[i] - 'a']++;
        }
    }

    int max_count = 0;
    for (size_t i = 0; i < 26; ++i) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }

    return max_count <= (n + 1) / 2;
}

int main(void) {
    const char s[] = "aab";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    bool result = canRearrange(s, strlen(s));

    printf("%s\n", result ? "Yes" : "No");

    return 0;
}