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

    size_t len = strnlen(str, 1024 * 1024);
    if (len == 0) {
        return NULL;
    }

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }
    snprintf(buffer, len + 1, "%s", str);

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
                for (size_t k = 0; k < word_count; k++) {
                    free(words[k]);
                }
                free(words);
                free(buffer);
                return NULL;
            }
            words = new_words;
        }
        for (size_t i = 0; token[i]; i++) {
            token[i] = tolower((unsigned char)token[i]);
        }
        
        char *word_copy = strdup(token);
        if (word_copy == NULL) {
            for (size_t k = 0; k < word_count; k++) {
                free(words[k]);
            }
            free(words);
            free(buffer);
            return NULL;
        }
        
        words[word_count++] = word_copy;
        token = strtok(NULL, " \t\n\r.,;:!?()-");
    }

    for (size_t i = 0; i < word_count; i++) {
        for (size_t j = 0; j < i; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                char *result = strdup(words[i]);
                for (size_t k = 0; k < word_count; k++) {
                    free(words[k]);
                }
                free(words);
                free(buffer);
                return result;
            }
        }
    }

    for (size_t k = 0; k < word_count; k++) {
        free(words[k]);
    }
    free(words);
    free(buffer);
    return NULL;
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

    const char *str2 = "No repeats here";
    char *repeated2 = find_first_repeated_word(str2);
    if (repeated2 != NULL) {
        printf("%s\n", repeated2);
        free(repeated2);
    } else {
        printf("No repeated word found.\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'repeated3=find_first_repeated_word(NULL)', assigned value is 0
     *  Calling function 'find_first_repeated_word' returns 0
     */
    char *repeated3 = find_first_repeated_word(NULL);
    /* Possible weaknesses found:
     *  Condition 'repeated3!=NULL' is always false
     *  Condition 'repeated3!=NULL' is always false [knownConditionTrueFalse]
     */
    if (repeated3 != NULL) {
        printf("%s\n", repeated3);
        free(repeated3);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}