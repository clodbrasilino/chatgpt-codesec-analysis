#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char* return_none(void) {
    char* none = (char*)malloc(5);
    if (none) {
        snprintf(none, 5, "None");
    }
    return none;
}

char* find_first_repeated_word(const char* input_string) {
    if (!input_string) {
        return return_none();
    }

    size_t len = 0;
    while (input_string[len] != '\0') {
        len++;
    }

    char* str_copy = (char*)malloc(len + 1);
    if (!str_copy) {
        return return_none();
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str_copy, input_string, len);
    str_copy[len] = '\0';

    for (size_t i = 0; i < len; ++i) {
        str_copy[i] = tolower((unsigned char)str_copy[i]);
    }

    size_t words_capacity = 10;
    char** words = (char**)malloc(words_capacity * sizeof(char*));
    if (!words) {
        free(str_copy);
        return return_none();
    }

    size_t word_count = 0;
    char* context = NULL;
    char* token = strtok_r(str_copy, " \t\n\r.,!?;:-", &context);

    while (token != NULL) {
        for (size_t i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) {
                size_t token_len = 0;
                while (token[token_len] != '\0') {
                    token_len++;
                }

                char* result = (char*)malloc(token_len + 1);
                if (result) {
                    snprintf(result, token_len + 1, "%s", token);
                }
                free(words);
                free(str_copy);
                return result ? result : return_none();
            }
        }

        if (word_count >= words_capacity) {
            words_capacity *= 2;
            char** temp = (char**)realloc(words, words_capacity * sizeof(char*));
            if (!temp) {
                free(words);
                free(str_copy);
                return return_none();
            }
            words = temp;
        }
        words[word_count++] = token;

        token = strtok_r(NULL, " \t\n\r.,!?;:-", &context);
    }

    free(words);
    free(str_copy);
    return return_none();
}

int main(void) {
    size_t buffer_size = 4096;
    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        return 1;
    }

    size_t len = 0;
    
    while (len < (buffer_size - 1)) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int c = getchar();
        if (c == EOF) {
            break;
        }
        buffer[len++] = (char)c;
    }
    buffer[len] = '\0';
    
    if (len > 0) {
        char* repeated_word = find_first_repeated_word(buffer);
        if (repeated_word) {
            printf("%s", repeated_word);
            free(repeated_word);
        }
    }

    free(buffer);
    return 0;
}