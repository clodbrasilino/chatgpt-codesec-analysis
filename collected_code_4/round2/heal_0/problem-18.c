#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeChars(char *str1, char *str2){
    int i = 0, j = 0, k = 0;

    while (str1[i]) {
        j = 0, k = 0;
        while (str2[k]) {
            if (str1[i] == str2[k]) {
                j = 1;
                break;
            }
            k++;
        }
        if (j == 0) {
            str1[j++] = str1[i];
        }
        i++;
    }

    str1[j] = '\0';
}

int main() {
    char str1[50], str2[50];

    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);

    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);

    str1[strlen(str1)-1] = '\0';
    str2[strlen(str2)-1] = '\0';

    removeChars(str1, str2);

    printf("Modified first string: %s\n", str1);

    return 0;
}