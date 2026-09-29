#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

/* Possible weaknesses found:
 *  expected 'const char **' but argument is of type 'char **'
 */
int is_word_in_array(const char *word, const char *array[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(word, array[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

char* remove_duplicates(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *words[MAX_WORDS] = {NULL};
    int word_count = 0;

    const char *token;
    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        /* Possible weaknesses found:
         *  passing argument 2 of 'is_word_in_array' from incompatible pointer type [-Wincompatible-pointer-types]
         */
        if (!is_word_in_array(token, words, word_count)) {
            words[word_count++] = strdup(token);
        }
        token = strtok(NULL, " ");
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_size = strlen(input) + 1;
    char *result = (char *)malloc(result_size);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    for (int i = 0; i < word_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining_space = result_size - strlen(result) - 1;
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, words[i], remaining_space);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        remaining_space -= strlen(words[i]);
        if (remaining_space > 0) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strncat(result, " ", remaining_space);
        }
        free(words[i]);
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(result) > 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result[strlen(result) - 1] = '\0';
    }

    return result;
}

int main() {
    const char *input = "this this is a test test string with with duplicates";
    char *output = remove_duplicates(input);
    printf("%s\n", output);
    free(output);
    return 0;
}