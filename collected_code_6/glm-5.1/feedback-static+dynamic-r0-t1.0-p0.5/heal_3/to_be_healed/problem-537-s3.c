#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char* find_first_repeated_word(char* str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char* buffer = (char*)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    char** words = (char**)malloc((len + 1) * sizeof(char*));
    if (words == NULL) {
        free(buffer);
        return NULL;
    }

    size_t word_count = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        while (str[i] != '\0' && !isalpha((unsigned char)str[i])) {
            i++;
        }
        if (str[i] == '\0') {
            break;
        }
        size_t j = 0;
        while (str[i] != '\0' && isalpha((unsigned char)str[i])) {
            buffer[j++] = tolower((unsigned char)str[i]);
            i++;
        }
        buffer[j] = '\0';

        char* word = (char*)malloc(j + 1);
        if (word == NULL) {
            for (size_t k = 0; k < word_count; k++) {
                free(words[k]);
            }
            free(words);
            free(buffer);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, buffer, j + 1);

        for (size_t k = 0; k < word_count; k++) {
            if (strcmp(words[k], word) == 0) {
                char* result = (char*)malloc(j + 1);
                if (result == NULL) {
                    free(word);
                    for (size_t m = 0; m < word_count; m++) {
                        free(words[m]);
                    }
                    free(words);
                    free(buffer);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result, word, j + 1);
                free(word);
                for (size_t m = 0; m < word_count; m++) {
                    free(words[m]);
                }
                free(words);
                free(buffer);
                return result;
            }
        }

        words[word_count++] = word;
    }

    for (size_t k = 0; k < word_count; k++) {
        free(words[k]);
    }
    free(words);
    free(buffer);
    return NULL;
}

int main(void) {
    char str[] = "This is a test this is only a test";
    char* repeated = find_first_repeated_word(str);
    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found\n");
    }
    return 0;
}