#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordList;

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int word_exists(WordList *list, const char *word) {
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_word(WordList *list, const char *word) {
    if (list->count < MAX_WORDS) {
        strncpy(list->words[list->count], word, MAX_WORD_LEN - 1);
        list->words[list->count][MAX_WORD_LEN - 1] = '\0';
        list->count++;
    }
}

char *remove_duplicate_words(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    WordList seen = {0};
    char *result = malloc(strlen(input) + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    char *temp = malloc(strlen(input) + 1);
    if (temp == NULL) {
        free(result);
        return NULL;
    }
    strcpy(temp, input);

    char *token = strtok(temp, " \t\n\r");
    int first = 1;

    while (token != NULL) {
        char lower_word[MAX_WORD_LEN];
        strncpy(lower_word, token, MAX_WORD_LEN - 1);
        lower_word[MAX_WORD_LEN - 1] = '\0';
        to_lowercase(lower_word);

        if (!word_exists(&seen, lower_word)) {
            add_word(&seen, lower_word);
            if (!first) {
                strcat(result, " ");
            }
            strcat(result, token);
            first = 0;
        }
        token = strtok(NULL, " \t\n\r");
    }

    free(temp);
    return result;
}

int main(void) {
    char input[1024];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    char *result = remove_duplicate_words(input);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Result: %s\n", result);
    free(result);

    return 0;
}