#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_WORD_LENGTH 256

int find_words(const char *str, char ***words, int *count) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "\\b[a-zA-Z]{4,}\\b";
    const char *cursor = str;
    int capacity = 10;
    int ret;

    *count = 0;
    *words = malloc(capacity * sizeof(char *));
    if (*words == NULL) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        free(*words);
        *words = NULL;
        return -1;
    }

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        int length = match[0].rm_eo - match[0].rm_so;
        
        if (length >= MAX_WORD_LENGTH) {
            regfree(&regex);
            for (int i = 0; i < *count; i++) {
                free((*words)[i]);
            }
            free(*words);
            *words = NULL;
            *count = 0;
            return -1;
        }

        if (*count >= capacity) {
            capacity *= 2;
            char **temp = realloc(*words, capacity * sizeof(char *));
            if (temp == NULL) {
                regfree(&regex);
                for (int i = 0; i < *count; i++) {
                    free((*words)[i]);
                }
                free(*words);
                *words = NULL;
                *count = 0;
                return -1;
            }
            *words = temp;
        }

        (*words)[*count] = malloc((length + 1) * sizeof(char));
        if ((*words)[*count] == NULL) {
            regfree(&regex);
            for (int i = 0; i < *count; i++) {
                free((*words)[i]);
            }
            free(*words);
            *words = NULL;
            *count = 0;
            return -1;
        }

        strncpy((*words)[*count], cursor + match[0].rm_so, length);
        (*words)[*count][length] = '\0';
        (*count)++;

        cursor += match[0].rm_eo;
    }

    regfree(&regex);
    return 0;
}

void free_words(char **words, int count) {
    if (words == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    const char *input = "The quick brown fox jumps over the lazy dog and runs through the forest";
    char **words = NULL;
    int count = 0;

    if (find_words(input, &words, &count) != 0) {
        fprintf(stderr, "Error: Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Found %d words with at least 4 characters:\n", count);
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    free_words(words, count);
    return EXIT_SUCCESS;
}