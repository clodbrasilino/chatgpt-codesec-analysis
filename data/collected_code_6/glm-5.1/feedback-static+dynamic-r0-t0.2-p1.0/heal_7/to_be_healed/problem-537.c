#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char* find_first_repeated_word(const char *str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(buffer, str);

    size_t capacity = 16;
    char **words = (char **)malloc(capacity * sizeof(char *));
    if (words == NULL) {
        free(buffer);
        return NULL;
    }

    size_t word_count = 0;
    char *token = strtok(buffer, " \t\n\r.,;:!?()-");
    while (token != NULL) {
        if (word_count >= capacity) {
            capacity *= 2;
            char **new_words = (char **)realloc(words, capacity * sizeof(char *));
            if (new_words == NULL) {
                free(words);
                free(buffer);
                return NULL;
            }
            words = new_words;
        }
        for (size_t i = 0; token[i]; i++) {
            token[i] = tolower((unsigned char)token[i]);
        }
        words[word_count++] = token;
        token = strtok(NULL, " \t\n\r.,;:!?()-");
    }

    char *result = NULL;
    for (size_t i = 0; i < word_count; i++) {
        for (size_t j = 0; j < i; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                result = strdup(words[i]);
                free(words);
                free(buffer);
                return result;
            }
        }
    }

    free(words);
    free(buffer);
    return result;
}

int main() {
    const char *str = "Hello world! This is a test. Hello again.";
    char *repeated = find_first_repeated_word(str);

    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}