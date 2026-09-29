#include <stdio.h>
#include <string.h>

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *a, int l, int r) {
    if (l == r)
        printf("%s\n", a);
    else {
        for (int i = l; i <= r; i++) {
            swap(a + l, a + i);
            permute(a, l + 1, r);
            swap(a + l, a + i);
        }
    }
}

int main() {
    char str[] = "aab";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str);
    if (str[n-1] == '\0') {
        permute(str, 0, n - 2);
    } else {
        permute(str, 0, n - 1);
    }
    return 0;
}