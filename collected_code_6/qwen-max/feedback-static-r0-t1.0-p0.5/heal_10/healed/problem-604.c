#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *saveptr;
    char *word = strtok_r(str, " ", &saveptr);
    char **reversed = (char **)malloc(50 * sizeof(char *));
    if (reversed == NULL) exit(EXIT_FAILURE);
    int i = 0;

    while (word != NULL && i < 50) {
        reversed[i] = strdup(word);
        if (reversed[i] == NULL) exit(EXIT_FAILURE);
        word = strtok_r(NULL, " ", &saveptr);
        i++;
    }

    for (int j = 0; j < i / 2; j++) {
        char *temp = reversed[j];
        reversed[j] = reversed[i - j - 1];
        reversed[i - j - 1] = temp;
    }

    str[0] = '\0';
    size_t current_len = 0;
    size_t max_len = 500;
    for (int j = 0; j < i; j++) {
        size_t word_len = strlen(reversed[j]);
        if (current_len + word_len + 1 > max_len) break;
        strncat(str, reversed[j], max_len - 1 - current_len);
        current_len += word_len;
        if (j < i - 1) {
            strncat(str, " ", max_len - 1 - current_len);
            current_len++;
        }
        free(reversed[j]);
    }
    free(reversed);
}

int main() {
    char str[] = "Hello World This is C";
    char *newStr = (char *)malloc(strlen(str) + 1);
    if (newStr == NULL) return EXIT_FAILURE;
    snprintf(newStr, strlen(str) + 1, "%s", str);
    reverseWords(newStr);
    printf("%s\n", newStr);
    free(newStr);
    return 0;
}