#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char *remove_duplicate_words(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (input[len] != '\0' && len < SIZE_MAX) {
        len++;
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

    size_t word_count = 0;

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
        size_t word_len = 0;
        while (words[i][word_len] != '\0' && word_len < len + 1) {
            word_len++;
        }
        if (current_len + word_len < len + 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + current_len, words[i], word_len);
            current_len += word_len;
            buffer[current_len] = '\0';
        }
        if (i < word_count - 1) {
            if (current_len + 1 < len + 1) {
                buffer[current_len++] = ' ';
                buffer[current_len] = '\0';
            }
        }
    }

    size_t result_len = 0;
    /* Possible weaknesses found:
     *  Array index 'result_len' is used before limits check. [arrayIndexThenCheck]
     */
    while (buffer[result_len] != '\0' && result_len < len + 1) {
        result_len++;
    }

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
    /* Possible weaknesses found:
     *  Variable 'str' can be declared as const array [constVariable]
     */
    char str[] = "Python Exercises Practice Solution Python Exercises";
    char *cleaned = remove_duplicate_words(str);

    if (cleaned != NULL) {
        printf("%s\n", cleaned);
        free(cleaned);
    }

    /* Possible weaknesses found:
     *  Assignment 'null_test=remove_duplicate_words(NULL)', assigned value is 0
     *  Calling function 'remove_duplicate_words' returns 0
     */
    const char *null_test = remove_duplicate_words(NULL);
    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'null_test==NULL' is always true
     */
    if (null_test == NULL) {
        printf("NULL input handled safely.\n");
    }

    return 0;
}