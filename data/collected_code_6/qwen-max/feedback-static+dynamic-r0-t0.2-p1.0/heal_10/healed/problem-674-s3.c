#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1024
#define MAX_WORD_LENGTH 64

char *remove_duplicates(const char *input) {
    char *words[MAX_WORDS] = {NULL};
    int word_count = 0;
    const char *token, *end;
    char *output = NULL;
    char *new_word;
    size_t input_size = strnlen(input, MAX_WORDS * MAX_WORD_LENGTH);

    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        if (strnlen(token, MAX_WORD_LENGTH) >= MAX_WORD_LENGTH || (token - (char *)input + MAX_WORD_LENGTH > input_size)) {
            end = memchr(token, ' ', input_size - (token - (char *)input));
            if (end == NULL) end = (const char *)input + input_size;
            token = (char *)end;
            continue;
        }
        int found = 0;
        for (int i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            new_word = strndup(token, MAX_WORD_LENGTH);
            if (new_word == NULL) {
                for (int i = 0; i < word_count; ++i) {
                    free(words[i]);
                }
                return NULL;
            }
            words[word_count++] = new_word;
        }
        token = strtok(NULL, " ");
    }

    size_t output_size = 1;
    for (int i = 0; i < word_count; ++i) {
        output_size += strnlen(words[i], MAX_WORD_LENGTH) + 1;
    }
    output = (char *)malloc(output_size);
    if (output == NULL) {
        for (int i = 0; i < word_count; ++i) {
            free(words[i]);
        }
        return NULL;
    }
    output[0] = '\0';

    for (int i = 0; i < word_count; ++i) {
        size_t remaining = output_size - strnlen(output, output_size) - 1;
        strncat(output, words[i], remaining);
        if (i < word_count - 1) {
            strncat(output, " ", remaining - strnlen(words[i], MAX_WORD_LENGTH));
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