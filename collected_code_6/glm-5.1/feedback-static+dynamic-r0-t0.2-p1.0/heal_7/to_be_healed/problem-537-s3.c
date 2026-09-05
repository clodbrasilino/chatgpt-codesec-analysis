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

    strncpy(buffer, str, len + 1);
    buffer[len] = '\0';

    char** words = (char**)malloc((len + 1) * sizeof(char*));
    if (words == NULL) {
        free(buffer);
        return NULL;
    }

    size_t word_count = 0;
    char* token = strtok(buffer, " \t\n\r.,;:!?()-");
    while (token != NULL) {
        for (size_t i = 0; token[i]; i++) {
            token[i] = tolower((unsigned char)token[i]);
        }
        words[word_count++] = token;
        token = strtok(NULL, " \t\n\r.,;:!?()-");
    }

    for (size_t i = 0; i < word_count; i++) {
        for (size_t j = 0; j < i; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                size_t res_len = strlen(words[i]) + 1;
                char* result = (char*)malloc(res_len);
                if (result != NULL) {
                    strncpy(result, words[i], res_len);
                    result[res_len - 1] = '\0';
                } else {
                    free(words);
                    free(buffer);
                    return NULL;
                }
                free(words);
                free(buffer);
                return result;
            }
        }
    }

    free(words);
    free(buffer);
    return NULL;
}

int main() {
    char str[] = "Hello world! This is a test. Hello again.";
    char* repeated = find_first_repeated_word(str);

    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}