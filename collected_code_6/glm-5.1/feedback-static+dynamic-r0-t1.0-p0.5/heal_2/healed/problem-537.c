#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256

char *find_first_repeated_word(const char *str) {
    char (*words)[MAX_WORD_LEN] = malloc(MAX_WORDS * MAX_WORD_LEN);
    if (words == NULL) {
        return NULL;
    }
    int count = 0;
    char buffer[MAX_WORD_LEN];
    int buf_idx = 0;

    if (str == NULL) {
        free(words);
        return NULL;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            if (buf_idx < MAX_WORD_LEN - 1) {
                buffer[buf_idx++] = tolower((unsigned char)str[i]);
            }
        } else {
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                for (int j = 0; j < count; j++) {
                    if (strcmp(words[j], buffer) == 0) {
                        char *result = malloc(buf_idx + 1);
                        if (result == NULL) {
                            free(words);
                            return NULL;
                        }
                        memcpy(result, buffer, buf_idx + 1);
                        free(words);
                        return result;
                    }
                }
                if (count < MAX_WORDS) {
                    memcpy(words[count], buffer, buf_idx + 1);
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
                char *result = malloc(buf_idx + 1);
                if (result == NULL) {
                    free(words);
                    return NULL;
                }
                memcpy(result, buffer, buf_idx + 1);
                free(words);
                return result;
            }
        }
    }

    free(words);
    return NULL;
}

int main() {
    const char str[] = "This is a test string this is another test";
    char *repeated = find_first_repeated_word(str);
    
    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found\n");
    }
    
    return 0;
}