#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *remove_duplicate_words(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    char **words = (char **)malloc((len / 2 + 1) * sizeof(char *));
    if (words == NULL) {
        free(buffer);
        return NULL;
    }

    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) {
        free(buffer);
        free(words);
        return NULL;
    }

    memcpy(temp, input, len + 1);

    size_t word_count = 0;
    char *rest = temp;
    char *token = strtok_r(temp, " \t\n\r", &rest);
    while (token != NULL) {
        bool found = false;
        for (size_t i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                found = true;
                break;
            }
        }

        if (!found) {
            words[word_count] = token;
            word_count++;
        }

        token = strtok_r(NULL, " \t\n\r", &rest);
    }

    size_t current_len = 0;
    buffer[0] = '\0';
    for (size_t i = 0; i < word_count; i++) {
        size_t word_len = strlen(words[i]);
        if (current_len + word_len <= len) {
            memcpy(buffer + current_len, words[i], word_len);
            current_len += word_len;
        } else {
            memcpy(buffer + current_len, words[i], len - current_len);
            current_len = len;
        }
        buffer[current_len] = '\0';

        if (i < word_count - 1) {
            if (current_len + 1 <= len) {
                buffer[current_len++] = ' ';
                buffer[current_len] = '\0';
            }
        }
    }

    size_t result_len = strlen(buffer);
    char *result = (char *)malloc(result_len + 1);
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
    }

    char *null_test = remove_duplicate_words(NULL);
    if (null_test == NULL) {
        printf("NULL input handled safely.\n");
    } else {
        free(null_test);
    }

    return 0;
}