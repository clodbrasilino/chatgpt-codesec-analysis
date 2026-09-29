#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256

char *find_first_repeated_word(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    char (*words)[MAX_WORD_LEN] = calloc(MAX_WORDS, MAX_WORD_LEN);
    if (words == NULL) {
        return NULL;
    }

    int count = 0;
    char buffer[MAX_WORD_LEN];
    int buf_idx = 0;
    
    char *input_copy = strdup(str);
    if (input_copy == NULL) {
        free(words);
        return NULL;
    }

    size_t input_len = strlen(input_copy);

    for (size_t i = 0; i < input_len; i++) {
        if (isalpha((unsigned char)input_copy[i])) {
            if (buf_idx < MAX_WORD_LEN - 1) {
                buffer[buf_idx++] = tolower((unsigned char)input_copy[i]);
            }
        } else {
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                for (int j = 0; j < count; j++) {
                    if (strcmp(words[j], buffer) == 0) {
                        char *result = malloc(buf_idx + 1);
                        if (result == NULL) {
                            free(words);
                            free(input_copy);
                            return NULL;
                        }
                        snprintf(result, buf_idx + 1, "%s", buffer);
                        free(words);
                        free(input_copy);
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
                char *result = malloc(buf_idx + 1);
                if (result == NULL) {
                    free(words);
                    free(input_copy);
                    return NULL;
                }
                snprintf(result, buf_idx + 1, "%s", buffer);
                free(words);
                free(input_copy);
                return result;
            }
        }
    }

    free(words);
    free(input_copy);
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