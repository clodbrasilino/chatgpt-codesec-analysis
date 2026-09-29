#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char* remove_duplicates(const char *input) {
    char words[MAX_WORDS][MAX_WORD_LENGTH + 1] = {0};
    int word_count = 0;
    const char *token;
    char *output = NULL;
    size_t total_length = 0;

    token = strtok((char *)input, " ");
    while (token && word_count < MAX_WORDS) {
        int i;
        for (i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                break;
            }
        }
        if (i == word_count) {
            size_t length = strnlen(token, MAX_WORD_LENGTH);
            if (length < MAX_WORD_LENGTH) {
                strncpy(words[word_count], token, length);
                words[word_count][length] = '\0';
                word_count++;
                total_length += length + 1;
            }
        }
        token = strtok(NULL, " ");
    }

    output = (char *)malloc(total_length + 1);
    if (output == NULL) {
        return NULL;
    }

    char *temp_output = output;
    for (int i = 0; i < word_count; i++) {
        size_t length = strnlen(words[i], MAX_WORD_LENGTH);
        memcpy(temp_output, words[i], length);
        temp_output += length;
        *temp_output++ = ' ';
    }
    if (word_count > 0) {
        *(temp_output - 1) = '\0';
    }

    return output;
}

int main() {
    const char *input = "Python Exercises Practice Solution Python";
    char *result = remove_duplicates(input);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}