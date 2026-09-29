#include <stdio.h>
#include <string.h>

int findRotations(char *str) {
    int len = strlen(str);
    char temp[2*len + 1];
    strcpy(temp, str);
    strcat(temp, str);
    int minRotations = len;
    for (int i = 0; i < len; i++) {
        int j;
        for (j = 0; j < len; j++) {
            if (str[j] != temp[i + j])
                break;
        }
        if (j == len && i < minRotations)
            minRotations = i;
    }
    return minRotations;
}

int main() {
    char str[] = "abcabc";
    printf("%d\n", findRotations(str));
    return 0;
}