#include <stdio.h>
#include <string.h>

int findRotations(char *str) {
    int n = strlen(str);
    char temp[2*n+1];
    strcpy(temp, str);
    strcat(temp, str);
    for (int i = 1; i <= n; i++) {
        char substring[n+1];
        strncpy(substring, temp+i,n);
        substring[n] = '\0';
        if (strncmp(substring, str, n) == 0) {
            return i;
        }
    }
    return n;
}

int main() {
    char str[] = "abc";
    printf("%d\n", findRotations(str));
    return 0;
}