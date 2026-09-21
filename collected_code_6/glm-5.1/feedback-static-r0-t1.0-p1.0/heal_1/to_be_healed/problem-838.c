#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps(char *s1, char *s2) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len2 = strlen(s2);
    if (len1 != len2) {
        return -1;
    }
    int n = len1;
    int x = 0;
    int y = 0;
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                x++;
            } else {
                y++;
            }
        }
    }
    if ((x + y) % 2 != 0) {
        return -1;
    }
    return (x / 2) + (y / 2) + (x % 2) * 2;
}

int main() {
    char s1[] = "1001";
    char s2[] = "0110";
    int result = min_swaps(s1, s2);
    printf("%d\n", result);
    return 0;
}