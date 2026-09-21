#include <stdio.h>
#include <string.h>

void left_rotate(char *str, int d) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str);
    d = (d % (int)n + n) % n;  // Ensure d is wrapped around properly
    if (d == 0) return;

    memmove(str + d, str, n - d + 1);
    memmove(str, str + n - d, d);
}

int main() {
    char str[] = "abcdef";
    int d = 2;
    left_rotate(str, d);
    printf("%s\n", str);
    return 0;
}