#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *remove_duplicate_words(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    if (len == 0) {
        char *empty_result = malloc(1);
        if (empty_result) empty_result[0] = '\0';
        return empty_result;
    }

    char *temp = malloc(len + 1);
    if (temp == NULL) {
        return NULL;
    }
    strcpy(temp, input);

    char **words = malloc((len / 2 + 1) * sizeof(char *));
    if (words == NULL) {
        free(temp);
        return NULL;
    }

    size_t word_count = 0;
    size_t buffer_capacity = len + 1;
    char *buffer = malloc(buffer_capacity);
    if (buffer == NULL) {
        free(words);
        free(temp);
        return NULL;
    }

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
        }

        token = strtok(NULL, " \t\n\r");
    }

    size_t buffer_len = 0;
    buffer[0] = '\0';
    for (size_t i = 0; i < word_count; i++) {
        size_t word_len = strlen(words[i]);
        if (buffer_len + word_len + (i > 0 ? 1 : 0) >= buffer_capacity) {
            break;
        }
        if (i > 0) {
            buffer[buffer_len++] = ' ';
            buffer[buffer_len] = '\0';
        }
        memcpy(buffer + buffer_len, words[i], word_len);
        buffer_len += word_len;
        buffer[buffer_len] = '\0';
    }

    size_t result_len = strlen(buffer);
    char *result = malloc(result_len + 1);
    if (result != NULL) {
        memcpy(result, buffer, result_len + 1);
    }

    free(temp);
    free(words);
    free(buffer);

    return result;
}

int main(void) {
    char str[] = "hello world hello there world again";
    char *cleaned = remove_duplicate_words(str);

    if (cleaned != NULL) {
        printf("Original: %s\n", str);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        printf("Memory allocation failed for cleaned string.\n");
    }

    char *null_test = remove_duplicate_words(NULL);
    if (null_test == NULL) {
        printf("NULL input handled safely.\n");
    } else {
        free(null_test);
    }

    return 0;
}