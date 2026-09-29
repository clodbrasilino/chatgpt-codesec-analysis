#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *remove_duplicate_words(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, SIZE_MAX);
    if (len == SIZE_MAX) {
        return NULL;
    }

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

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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
        size_t word_len = strnlen(words[i], len + 1);
        if (current_len + word_len <= len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + current_len, words[i], word_len);
            current_len += word_len;
        } else {
            size_t copy_len = len - current_len;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + current_len, words[i], copy_len);
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

    size_t result_len = strnlen(buffer, len + 1);
    char *result = (char *)malloc(result_len + 1);
    if (result != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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

    /* Possible weaknesses found:
     *  Assignment 'null_test=remove_duplicate_words(NULL)', assigned value is 0
     *  Calling function 'remove_duplicate_words' returns 0
     */
    char *null_test = remove_duplicate_words(NULL);
    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_test == NULL) {
        printf("NULL input handled safely.\n");
    } else {
        free(null_test);
    }

    return 0;
}