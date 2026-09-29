#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* find_first_max_even_word(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char* buffer = (char*)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        buffer[i] = str[i];
    }
    buffer[len] = '\0';

    size_t max_len = 0;
    char* result = NULL;

    char* token = strtok(buffer, " \t\n\r");
    while (token != NULL) {
        size_t token_len = 0;
        while (token[token_len] != '\0') {
            token_len++;
        }

        if (token_len % 2 == 0) {
            if (token_len > max_len) {
                max_len = token_len;
                if (result != NULL) {
                    free(result);
                }
                result = (char*)malloc(token_len + 1);
                if (result == NULL) {
                    free(buffer);
                    return NULL;
                }
                for (size_t i = 0; i < token_len; i++) {
                    result[i] = token[i];
                }
                result[token_len] = '\0';
            }
        }
        token = strtok(NULL, " \t\n\r");
    }

    free(buffer);
    return result;
}

int main(void) {
    const char* text = "This is a simple test string with some even and odd length words";
    char* max_even_word = find_first_max_even_word(text);

    if (max_even_word != NULL) {
        printf("First maximum length even word: %s\n", max_even_word);
        free(max_even_word);
    } else {
        printf("No even length word found.\n");
    }

    return 0;
}