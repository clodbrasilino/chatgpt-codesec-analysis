#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256

char *find_first_repeated_word(const char *str) {
    char (*words)[MAX_WORD_LEN] = NULL;
    char *buffer = NULL;
    int count = 0;
    int buf_idx = 0;
    char *result = NULL;

    if (str == NULL) {
        return NULL;
    }

    words = malloc(MAX_WORDS * MAX_WORD_LEN);
    buffer = malloc(MAX_WORD_LEN);

    if (words == NULL || buffer == NULL) {
        free(words);
        free(buffer);
        return NULL;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            if (buf_idx < MAX_WORD_LEN - 1) {
                buffer[buf_idx++] = (char)tolower((unsigned char)str[i]);
            }
        } else {
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                for (int j = 0; j < count; j++) {
                    if (strcmp(words[j], buffer) == 0) {
                        size_t len = strlen(buffer);
                        result = malloc(len + 1);
                        if (result != NULL) {
                            memcpy(result, buffer, len + 1);
                        }
                        free(words);
                        free(buffer);
                        return result;
                    }
                }
                if (count < MAX_WORDS) {
                    memcpy(words[count], buffer, buf_idx + 1);
                    count++;
                } else {
                    break;
                }
                buf_idx = 0;
            }
        }
    }

    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        for (int j = 0; j < count; j++) {
            if (strcmp(words[j], buffer) == 0) {
                size_t len = strlen(buffer);
                result = malloc(len + 1);
                if (result != NULL) {
                    memcpy(result, buffer, len + 1);
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
    const char str[] = "This is a test test string to find repeated word.";
    char *repeated = find_first_repeated_word(str);

    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}