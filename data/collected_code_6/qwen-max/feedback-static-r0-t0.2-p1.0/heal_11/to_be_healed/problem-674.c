#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

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
    const char *words[MAX_WORDS] = {NULL};
    int word_count = 0;

    char *input_copy = strdup(input);
    if (input_copy == NULL) {
        return NULL;
    }

    char *token = strtok(input_copy, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(token);
        if (len <= MAX_WORD_LENGTH && !is_word_in_array(token, (const char **)words, word_count)) {
            words[word_count] = strndup(token, len);
            if (words[word_count] == NULL) {
                free(input_copy);
                for (int i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                return NULL;
            }
            word_count++;
        }
        token = strtok(NULL, " ");
    }

    free(input_copy);

    size_t output_length = 0;
    for (int i = 0; i < word_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        output_length += strlen(words[i]) + 1;
    }

    char *result = (char *)malloc(output_length + 1);
    if (result == NULL) {
        for (int i = 0; i < word_count; i++) {
            free(words[i]);
        }
        return NULL;
    }
    *result = '\0';

    for (int i = 0; i < word_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, words[i], output_length - strlen(result));
        if (i < word_count - 1) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strncat(result, " ", output_length - strlen(result) - 1);
        }
        free(words[i]);
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