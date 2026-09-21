#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str, size_t len) {
    char *copy = malloc(len + 1);
    if (copy == NULL) return;
    memcpy(copy, str, len);
    copy[len] = '\0';

    char *word = strtok(copy, " ");
    char **reversed = malloc(50 * sizeof(char *));
    if (reversed == NULL) {
        free(copy);
        return;
    }
    int i = 0;

    while (word != NULL && i < 50) {
        reversed[i] = strdup(word);
        if (reversed[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(reversed[j]);
            }
            free(reversed);
            free(copy);
            return;
        }
        i++;
        word = strtok(NULL, " ");
    }

    str[0] = '\0';
    for (int j = i - 1; j >= 0; j--) {
        size_t space = strlen(str);
        size_t word_len = strlen(reversed[j]);
        if (space + word_len + 1 <= len) {
            strncat(str, reversed[j], len - space - 1);
            if (j > 0 && space + word_len + 2 <= len) {
                strncat(str, " ", len - space - word_len - 1);
            }
        }
        free(reversed[j]);
    }

    free(copy);
    free(reversed);
}

int main() {
    char str[] = "Hello World This is C";
    reverseWords(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}