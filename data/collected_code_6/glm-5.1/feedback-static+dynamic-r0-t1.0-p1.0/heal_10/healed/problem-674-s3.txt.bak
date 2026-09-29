#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

char *remove_duplicate_words(const char *input) {
    if (input == NULL) return NULL;
    if (*input == '\0') {
        char *empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    size_t len = strlen(input);
    char *temp = malloc(len + 1);
    if (temp == NULL) return NULL;
    strcpy(temp, input);

    char **words = malloc((len / 2 + 1) * sizeof(char *));
    if (words == NULL) {
        free(temp);
        return NULL;
    }

    size_t word_count = 0;
    size_t result_len = 0;

    char *token = strtok(temp, " \t\n\r");
    while (token != NULL) {
        bool found = false;
        for (size_t i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                found = true;
                break;
            }
        }

        if (!found) {
            words[word_count++] = token;
            result_len += strlen(token);
        }

        token = strtok(NULL, " \t\n\r");
    }

    if (word_count == 0) {
        free(words);
        free(temp);
        char *empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    result_len += word_count - 1;

    char *result = malloc(result_len + 1);
    if (result == NULL) {
        free(words);
        free(temp);
        return NULL;
    }

    result[0] = '\0';
    for (size_t i = 0; i < word_count; i++) {
        strcat(result, words[i]);
        if (i < word_count - 1) {
            strcat(result, " ");
        }
    }

    free(words);
    free(temp);

    return result;
}

int main(void) {
    char str[] = "hello world hello there world again";
    char *cleaned = remove_duplicate_words(str);

    if (cleaned != NULL) {
        printf("Original: %s\n", str);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    }

    const char *null_input = NULL;
    char *null_test = remove_duplicate_words(null_input);
    
    if (null_test != NULL) {
        printf("NULL input returned a non-NULL pointer.\n");
        free(null_test);
    } else {
        printf("NULL input handled safely.\n");
    }

    return 0;
}