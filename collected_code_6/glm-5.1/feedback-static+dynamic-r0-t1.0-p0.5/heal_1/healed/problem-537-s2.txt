#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256

char *find_first_repeated_word(const char *str) {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count = 0;
    char buffer[MAX_WORD_LEN];
    int buf_idx = 0;

    if (str == NULL) {
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
                        size_t len = strnlen(buffer, MAX_WORD_LEN);
                        char *result = malloc(len + 1);
                        if (result == NULL) {
                            return NULL;
                        }
                        snprintf(result, len + 1, "%s", buffer);
                        return result;
                    }
                }
                if (count < MAX_WORDS) {
                    snprintf(words[count], MAX_WORD_LEN, "%s", buffer);
                    count++;
                }
                buf_idx = 0;
            }
        }
    }

    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        for (int j = 0; j < count; j++) {
            if (strcmp(words[j], buffer) == 0) {
                size_t len = strnlen(buffer, MAX_WORD_LEN);
                char *result = malloc(len + 1);
                if (result == NULL) {
                    return NULL;
                }
                snprintf(result, len + 1, "%s", buffer);
                return result;
            }
        }
    }

    return NULL;
}

int main() {
    char str[] = "This is a test test string to find repeated word.";
    char *repeated = find_first_repeated_word(str);

    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}