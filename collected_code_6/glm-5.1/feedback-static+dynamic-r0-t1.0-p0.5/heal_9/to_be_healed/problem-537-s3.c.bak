#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char* find_first_repeated_word(char* str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }

    size_t len = strlen(str);
    char* buffer = (char*)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    char** words = (char**)malloc((len / 2 + 2) * sizeof(char*));
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

        if (j == 0) {
            continue;
        }

        for (size_t k = 0; k < word_count; k++) {
            if (strcmp(words[k], buffer) == 0) {
                char* result = (char*)malloc(j + 1);
                if (result != NULL) {
                    strcpy(result, buffer);
                }
                for (size_t m = 0; m < word_count; m++) {
                    free(words[m]);
                }
                free(words);
                free(buffer);
                return result;
            }
        }

        words[word_count] = (char*)malloc(j + 1);
        if (words[word_count] == NULL) {
            for (size_t k = 0; k < word_count; k++) {
                free(words[k]);
            }
            free(words);
            free(buffer);
            return NULL;
        }
        strcpy(words[word_count], buffer);
        word_count++;
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