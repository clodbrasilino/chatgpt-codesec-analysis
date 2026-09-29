#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char* find_first_repeated_word(const char* input_string) {
    if (!input_string) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input_string);
    char* str_copy = (char*)malloc(len + 1);
    char** words = NULL;
    size_t word_count = 0;
    size_t words_capacity = 10;
    char* result = NULL;

    if (!str_copy) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str_copy, input_string);

    for (size_t i = 0; i < len; ++i) {
        str_copy[i] = tolower((unsigned char)str_copy[i]);
    }

    words = (char**)malloc(words_capacity * sizeof(char*));
    if (!words) {
        free(str_copy);
        return NULL;
    }

    char* context = NULL;
    char* token = strtok_r(str_copy, " \t\n\r.,!?;:", &context);

    while (token != NULL) {
        if (word_count >= words_capacity) {
            words_capacity *= 2;
            char** temp = (char**)realloc(words, words_capacity * sizeof(char*));
            if (!temp) {
                free(words);
                free(str_copy);
                return NULL;
            }
            words = temp;
        }
        words[word_count++] = token;

        for (size_t i = 0; i < word_count - 1; ++i) {
            if (strcmp(words[i], token) == 0) {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                result = (char*)malloc(strlen(token) + 1);
                if (result) {
                    /* Possible weaknesses found:
                     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                     */
                    strcpy(result, token);
                }
                free(words);
                free(str_copy);
                return result;
            }
        }

        token = strtok_r(NULL, " \t\n\r.,!?;:", &context);
    }

    free(words);
    free(str_copy);
    return NULL;
}

int main(void) {
    const char* test_string = "This is a test string to test the function.";
    char* repeated_word = find_first_repeated_word(test_string);

    if (repeated_word) {
        printf("First repeated word: %s\n", repeated_word);
        free(repeated_word);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}