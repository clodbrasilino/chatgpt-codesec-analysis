#include <stdio.h>
#include <string.h>

int findRotations(char *str) {
    int len = strlen(str);
    char temp[2*len + 1];
    strcpy(temp, str);
    strcat(temp, str);
    int i;
    for (i = 1; i <= len; i++) {
        if (strncmp(str, temp + i, len) == 0) {
            return i;
        }
    }
    return len;
}

int main() {
    char str[] = "abcabc";
    printf("%d", findRotations(str));
    return 0;
}