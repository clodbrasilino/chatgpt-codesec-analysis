#include <stdio.h>
#include <string.h>

int findMinRotations(const char *str) {
    int n = strlen(str);
    char temp[2*n + 1];
    snprintf(temp, sizeof(temp), "%s%s", str, str);

    for (int i = 1; i <= n; i++) {
        if (strncmp(temp + i, str, n) == 0) {
            return i;
        }
    }
    return n;
}

int main() {
    char str[] = "abcde";
    printf("Minimum rotations: %d\n", findMinRotations(str));
    return 0;
}