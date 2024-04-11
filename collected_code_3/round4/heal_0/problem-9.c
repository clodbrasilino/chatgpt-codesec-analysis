#include <stdio.h>
#include <string.h>

int minRotations(char *str) {
    int n = strlen(str);
    char temp[2*n+1];
    strcpy(temp, str);
    strcat(temp, str);
    int minRotations = n;

    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < n; j++) {
            if (str[j] != temp[i+j])
                break;
        }
        if (j == n && i < minRotations)
            minRotations = i;
    }
    return minRotations;
}

int main() {
    char str[] = "geeks";
    printf("%d", minRotations(str));
    return 0;
}