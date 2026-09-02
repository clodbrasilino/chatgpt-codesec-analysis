#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int minRotationRequired(char *s) {
    int n = strlen(s);
    char tmp[n+1];
    int minRot = n;
    for (int i = 0; i < n; ++i) {
        strcpy(tmp, s + i);
        strncat(tmp, s, i);
        tmp[n] = '\0';
        if (strcmp(tmp, s) == 0) {
            minRot = i;
            break;
        }
    }
    return minRot;
}

int main() {
    char s[] = "abcde";
    int result = minRotationRequired(s);
    printf("%d\n", result);
    return 0;
}