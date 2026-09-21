#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_repeated_word(char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    char* buffer = (char*)malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    errno_t err = memcpy_s(buffer, len + 1, str, len + 1);
    if (err != 0) {
        free(buffer);
        return NULL;
    }

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

    char* result = NULL;
    for (size_t i = 0; i < word_count; i++) {
        for (size_t j = 0; j < i; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                size_t res_len = strnlen(words[i], len + 1) + 1;
                result = (char*)malloc(res_len);
                if (result != NULL) {
                    errno_t res_err = memcpy_s(result, res_len, words[i], res_len);
                    if (res_err != 0) {
                        free(result);
                        result = NULL;
                    }
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