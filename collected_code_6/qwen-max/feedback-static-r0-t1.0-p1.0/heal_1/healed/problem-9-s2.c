#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int minRotationRequired(const char *s) {
    size_t n = strlen(s);
    char *tmp = (char *)malloc(n + 1);
    if (tmp == NULL) return -1;
    int minRot = n;
    for (int i = 0; i < n; ++i) {
        strncpy(tmp, s + i, n - i);
        tmp[n - i] = '\0';
        strncat(tmp, s, i);
        tmp[n] = '\0';
        if (strcmp(tmp, s) == 0) {
            minRot = i;
            break;
        }
    }
    free(tmp);
    return minRot;
}

int main() {
    char s[] = "abcde";
    int result = minRotationRequired(s);
    printf("%d\n", result);
    return 0;
}