#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canRearrange(char *str) {
    int count[26] = {0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(str);
    if (n == 1) return true;

    for (int i = 0; i < n; i++) {
        count[str[i] - 'a']++;
    }

    int max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }

    if (max_count > (n + 1) / 2) {
        return false;
    }

    return true;
}

int main() {
    char str[] = "abacaba";
    if (canRearrange(str)) {
        printf("The letters can be rearranged.\n");
    } else {
        printf("The letters cannot be rearranged.\n");
    }

    return 0;
}