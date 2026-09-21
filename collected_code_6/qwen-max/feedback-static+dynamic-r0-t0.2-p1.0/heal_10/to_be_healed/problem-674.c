#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

int is_word_in_array(const char *word, const char *const array[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(word, array[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 0 failed: expected 'Python Exercises Practice Solution', got <no output>
  *  test case 2 failed: expected 'Python Exercises Practice Solution', got <no output>
  */

char* remove_duplicates(const char *input) {
    char **words = malloc((MAX_WORDS + 1) * sizeof(char *));
    if (words == NULL) {
        return NULL;
    }
    for (int i = 0; i <= MAX_WORDS; i++) {
        words[i] = NULL;
    }

    int word_count = 0;

    char *input_copy = strdup(input);
    if (input_copy == NULL) {
        free(words);
        return NULL;
    }

    char *token = strtok(input_copy, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        if (!is_word_in_array(token, (const char *const *)words, word_count)) {
            words[word_count] = strdup(token);
            if (words[word_count] == NULL) {
                for (int i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(words);
                free(input_copy);
                return NULL;
            }
            word_count++;
        }
        token = strtok(NULL, " ");
    }

    size_t result_len = 0;
    for (int i = 0; i < word_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result_len += strlen(words[i]) + 1;
    }

    char *result = malloc(result_len + 1);
    if (result == NULL) {
        for (int i = 0; i < word_count; i++) {
            free(words[i]);
        }
        free(words);
        free(input_copy);
        return NULL;
    }
    result[0] = '\0';

    for (int i = 0; i < word_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        strncat(result, words[i], strlen(words[i]));
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strncat(result, " ", 1);
        free(words[i]);
    }

    if (result_len > 0) {
        result[result_len - 1] = '\0';
    } else {
        result[0] = '\0';
    }

    free(words);
    free(input_copy);
    return result;
}

int main() {
    const char *input = "Python Exercises Practice Solution";
    char *output = remove_duplicates(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}