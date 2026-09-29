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

    size_t word_count = 0;

    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) {
        free(buffer);
        free(words);
        return NULL;
    }

    if (len > 0) {
        memcpy(buffer, input, len + 1);
        memcpy(temp, input, len + 1);
    } else {
        temp[0] = '\0';
        buffer[0] = '\0';
    }

    char *rest = NULL;
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
            buffer[current_len] = '\0';
        }
        if (i < word_count - 1) {
            if (current_len < len) {
                buffer[current_len++] = ' ';
                buffer[current_len] = '\0';
            }
        }
    }

    size_t result_len = strlen(buffer);

    char *result = (char *)malloc(result_len + 1);
    if (result != NULL) {
        if (result_len > 0) {
            memcpy(result, buffer, result_len + 1);
        } else {
            result[0] = '\0';
        }
    }

    free(temp);
    free(words);
    free(buffer);

    return result;
}

int main(void) {
    const char str[] = "Python Exercises Practice Solution Python Exercises";
    char *cleaned = remove_duplicate_words(str);

    if (cleaned != NULL) {
        printf("%s\n", cleaned);
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