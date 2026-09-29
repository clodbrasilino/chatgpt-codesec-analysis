#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1024
#define MAX_WORD_LENGTH 64

char *remove_duplicates(const char *input) {
    char *words[MAX_WORDS] = {NULL};
    int word_count = 0;
    const char *token;
    char *output = NULL;

    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        int found = 0;
        for (int i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            words[word_count++] = strdup(token);
            if (words[word_count - 1] == NULL) {
                for (int i = 0; i < word_count - 1; ++i) {
                    free(words[i]);
                }
                return NULL;
            }
        }
        token = strtok(NULL, " ");
    }

    size_t total_length = 0;
    for (int i = 0; i < word_count; ++i) {
        total_length += strlen(words[i]) + 1;
    }

    output = (char *)malloc(total_length);
    if (output == NULL) {
        for (int i = 0; i < word_count; ++i) {
            free(words[i]);
        }
        return NULL;
    }
    output[0] = '\0';

    for (int i = 0; i < word_count; ++i) {
        strcat(output, words[i]);
        if (i < word_count - 1) {
            strcat(output, " ");
        }
        free(words[i]);
    }

    return output;
}

int main() {
    const char *input = "Python Exercises Practice Solution";
    char *result = remove_duplicates(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}