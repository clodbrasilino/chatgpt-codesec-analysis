#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int minRotationRequired(const char *s) {
    size_t n = strlen(s);
    char *tmp = malloc(n + 1);
    if (tmp == NULL) return -1;
    int minRot = n;
    for (int i = 0; i < n; ++i) {
        size_t len1 = n - i;
        size_t len2 = i;
        memcpy(tmp, s + i, len1);
        memcpy(tmp + len1, s, len2);
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