#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1024
#define WORD_LENGTH 64

char* remove_duplicate_words(const char *input) {
    char words[MAX_WORDS][WORD_LENGTH] = {0};
    int word_count = 0;
    const char *token;
    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        int is_new_word = 1;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                is_new_word = 0;
                break;
            }
        }
        if (is_new_word) {
            strncpy(words[word_count], token, WORD_LENGTH);
            word_count++;
        }
        token = strtok(NULL, " ");
    }

    char *result = (char *)malloc(WORD_LENGTH * word_count + word_count - 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    for (int i = 0; i < word_count; i++) {
        strncat(result, words[i], WORD_LENGTH);
        if (i < word_count - 1) {
            strncat(result, " ", WORD_LENGTH);
        }
    }
    return result;
}

int main() {
    const char *input = "this is a test test of of the duplicate duplicate word removal";
    char *output = remove_duplicate_words(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }
    return 0;
}