#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *word_start = str;
    char *temp = str;
    int len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) return;
    result[len] = '\0';
    while (*temp) {
        temp++;
        if (*temp == ' ' || *temp == '\0') {
            while (temp > word_start) {
                len--;
                result[len] = *--temp;
            }
            while (*temp == ' ') {
                result[len--] = *temp++;
            }
            word_start = temp;
        }
    }
    strcpy(str, result);
    free(result);
}

int main() {
    char str[] = "Hello World This is C";
    reverseWords(str);
    printf("%s\n", str);
    return 0;
}