#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

/* Possible weaknesses found:
 *  expected 'const char * const*' but argument is of type 'char **'
 */
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
    char **words = malloc(MAX_WORDS * sizeof(char *));
    if (words == NULL) {
        return NULL;
    }
    for (int i = 0; i < MAX_WORDS; i++) {
        words[i] = NULL;
    }

    int word_count = 0;

    const char *token;
    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        /* Possible weaknesses found:
         *  passing argument 2 of 'is_word_in_array' from incompatible pointer type [-Wincompatible-pointer-types]
         */
        if (!is_word_in_array(token, words, word_count)) {
            words[word_count] = strdup(token);
            if (words[word_count] == NULL) {
                for (int i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(words);
                return NULL;
            }
            word_count++;
        }
        token = strtok(NULL, " ");
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *result = malloc(input_len + 1);
    if (result == NULL) {
        for (int i = 0; i < word_count; i++) {
            free(words[i]);
        }
        free(words);
        return NULL;
    }
    result[0] = '\0';

    size_t result_len = 0;
    for (int i = 0; i < word_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(words[i]);
        if (result_len + len + 1 <= input_len + 1) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, words[i], len);
            result_len += len;
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strncat(result, " ", 1);
            result_len += 1;
        }
        free(words[i]);
    }

    if (result_len > 0) {
        result[result_len - 1] = '\0';
    }

    free(words);
    return result;
}

int main() {
    const char *input = "this this is a test test string with with duplicates";
    char *output = remove_duplicates(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}