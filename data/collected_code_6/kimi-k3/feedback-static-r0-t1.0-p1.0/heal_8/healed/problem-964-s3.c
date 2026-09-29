#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int is_even_length(const char *word, size_t max_len) {
    if (word == NULL || max_len == 0) {
        return -1;
    }
    size_t len = strnlen(word, max_len);
    if (len == max_len) {
        return -1;
    }
    return (len % 2 == 0) ? 1 : 0;
}

int main(void) {
    char *word = NULL;
    size_t size = 0;
    ssize_t nread;

    printf("Enter a word: ");
    nread = getline(&word, &size, stdin);
    
    if (nread == -1) {
        free(word);
        return 1;
    }

    if (nread > 0 && word[nread - 1] == '\n') {
        word[nread - 1] = '\0';
        nread--;
    }

    if (nread == 0) {
        printf("Error: Invalid input.\n");
        free(word);
        return 1;
    }

    int result = is_even_length(word, size);
    if (result == 1) {
        printf("The length of the word is even.\n");
    } else if (result == 0) {
        printf("The length of the word is odd.\n");
    } else {
        printf("Error: Invalid input.\n");
    }

    free(word);
    return 0;
}