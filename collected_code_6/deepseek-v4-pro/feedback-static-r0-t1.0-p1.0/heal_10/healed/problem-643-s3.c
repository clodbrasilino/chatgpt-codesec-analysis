#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool match_word_with_internal_z(const char *text) {
    if (text == NULL) {
        return false;
    }

    const char *word_start = text;
    const char *p = text;

    while (*p != '\0') {
        if (isspace((unsigned char)*p)) {
            size_t len = (size_t)(p - word_start);
            if (len > 2) {
                const char *q = word_start + 1;
                const char *q_end = p - 1;
                for (; q < q_end; q++) {
                    if (*q == 'z' || *q == 'Z') {
                        return true;
                    }
                }
            }
            word_start = p + 1;
        }
        p++;
    }

    size_t len = (size_t)(p - word_start);
    if (len > 2) {
        const char *q = word_start + 1;
        const char *q_end = p - 1;
        for (; q < q_end; q++) {
            if (*q == 'z' || *q == 'Z') {
                return true;
            }
        }
    }

    return false;
}

#define INPUT_BUFFER_SIZE 1024

int main(void) {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    printf("Enter text: ");
    characters = getline(&input, &bufsize, stdin);
    if (characters == -1) {
        free(input);
        return 1;
    }

    if (characters > 0 && input[characters - 1] == '\n') {
        input[characters - 1] = '\0';
    }

    if (match_word_with_internal_z(input)) {
        printf("Match found.\n");
    } else {
        printf("No match found.\n");
    }

    free(input);
    return 0;
}