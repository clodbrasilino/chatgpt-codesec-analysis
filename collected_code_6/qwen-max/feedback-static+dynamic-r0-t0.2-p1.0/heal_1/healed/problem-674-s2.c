#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char* remove_duplicates(const char *input) {
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {0};
    int word_count = 0;
    const char *token;
    char *output, *temp;
    int i;

    token = strtok((char *)input, " ");
    while (token != NULL && word_count < MAX_WORDS) {
        for (i = 0; i < word_count; ++i) {
            if (strcmp(words[i], token) == 0) {
                break;
            }
        }
        if (i == word_count) {
            strncpy(words[word_count++], token, MAX_WORD_LENGTH - 1);
        }
        token = strtok(NULL, " ");
    }

    temp = output = (char *)malloc(strlen(input) + 1);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < word_count; ++i) {
        strcpy(temp, words[i]);
        temp += strlen(words[i]);
        if (i < word_count - 1) {
            *temp++ = ' ';
        }
    }
    *temp = '\0';

    return output;
}

int main() {
    const char *inputs[] = {"this is a test this is only a test", 
                            "Python Exercises Practice Solution Python",
                            "Python Exercises Practice Solution",
                            "Python Exercises Practice Solution Python Exercises"};

    for (int k = 0; k < 4; k++) {
        char *result = remove_duplicates(inputs[k]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
        }
    }
    return 0;
}