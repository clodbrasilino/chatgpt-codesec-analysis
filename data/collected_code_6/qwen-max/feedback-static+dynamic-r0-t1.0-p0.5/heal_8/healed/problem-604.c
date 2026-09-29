#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseWords(char *str) {
    char *word = strtok(str, " ");
    size_t max_words = 50;
    char **reversed = malloc(max_words * sizeof(char *));
    if (reversed == NULL) return;
    int i = 0;

    while (word != NULL && i < max_words) {
        size_t len = strlen(word);
        reversed[i] = (char *)malloc((len + 1) * sizeof(char));
        if (reversed[i] == NULL) break;
        snprintf(reversed[i], len + 1, "%s", word);
        word = strtok(NULL, " ");
        i++;
    }

    for (int j = 0; j < i / 2; j++) {
        char *temp = reversed[j];
        reversed[j] = reversed[i - j - 1];
        reversed[i - j - 1] = temp;
    }

    str[0] = '\0';
    for (int j = 0; j < i; j++) {
        size_t len = strlen(str);
        size_t word_len = strlen(reversed[j]);
        if (len + word_len + (j < i - 1 ? 1 : 0) < 50) {
            strncat(str, reversed[j], 50 - len - 1);
            if (j < i - 1) {
                strncat(str, " ", 1);
            }
        }
        free(reversed[j]);
    }
    free(reversed);
}

int main() {
    char str[] = "Hello World This is C";
    reverseWords(str);
    printf("%s\n", str);
    return 0;
}