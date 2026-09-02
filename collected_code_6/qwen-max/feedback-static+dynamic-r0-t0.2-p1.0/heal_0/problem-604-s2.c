#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *word = strtok(str, " ");
    char *temp = (char *)malloc(strlen(word) + 1);
    strcpy(temp, word);
    while (word != NULL) {
        word = strtok(NULL, " ");
        if (word != NULL) {
            strncat(str, " ", strlen(str) + 1 - strlen(str));
            strncat(str, word, strlen(str) + 1 - strlen(str));
        }
    }
    free(temp);
    temp = (char *)malloc(strlen(str) + 1);
    strcpy(temp, str);
    int i, j;
    for (i = 0; i < strlen(str); i++) {
        for (j = i + 1; j < strlen(str); j++) {
            if (str[j] == ' ') {
                int start = i, end = j - 1;
                while (start < end) {
                    char t = str[start];
                    str[start] = str[end];
                    str[end] = t;
                    start++;
                    end--;
                }
                i = j;
                break;
            }
        }
    }
    int start = i, end = strlen(str) - 1;
    while (start < end) {
        char t = str[start];
        str[start] = str[end];
        str[end] = t;
        start++;
        end--;
    }
    free(temp);
}

int main() {
    char str[] = "Hello World This is C";
    reverseWords(str);
    printf("%s\n", str);
    return 0;
}