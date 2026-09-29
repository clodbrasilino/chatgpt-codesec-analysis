#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char* remove_duplicates(const char *input) {
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    int word_count = 0;
    const char *token;
    char *output = NULL;
    char *temp_output = NULL;

    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        int i;
        for (i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                break;
            }
        }
        if (i == word_count) {
            strncpy(words[word_count], token, MAX_WORD_LENGTH - 1);
            word_count++;
        }
        token = strtok(NULL, " ");
    }

    temp_output = (char *)malloc(MAX_WORD_LENGTH * word_count + word_count);
    if (temp_output == NULL) {
        return NULL;
    }

    output = temp_output;
    for (int i = 0; i < word_count; i++) {
        strcpy(temp_output, words[i]);
        temp_output += strlen(words[i]);
        *temp_output++ = ' ';
    }
    *(temp_output - 1) = '\0';

    return output;
}

int main() {
    const char *input = "this is a test this is only a test";
    char *result = remove_duplicates(input);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}