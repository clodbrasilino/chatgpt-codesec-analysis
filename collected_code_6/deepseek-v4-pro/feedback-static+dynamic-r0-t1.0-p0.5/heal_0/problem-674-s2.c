#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordCollection;

void init_collection(WordCollection *collection) {
    collection->count = 0;
}

int contains_word(WordCollection *collection, const char *word) {
    for (int i = 0; i < collection->count; i++) {
        if (strcmp(collection->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_word(WordCollection *collection, const char *word) {
    if (collection->count < MAX_WORDS && !contains_word(collection, word)) {
        strncpy(collection->words[collection->count], word, MAX_WORD_LEN - 1);
        collection->words[collection->count][MAX_WORD_LEN - 1] = '\0';
        collection->count++;
    }
}

void remove_duplicate_words(char *str) {
    if (str == NULL) {
        return;
    }

    WordCollection collection;
    init_collection(&collection);

    char *result = (char *)malloc(strlen(str) + 1);
    if (result == NULL) {
        return;
    }
    result[0] = '\0';

    char *token;
    char *rest = str;
    char *delimiters = " \t\n\r\f\v";

    while ((token = strtok_r(rest, delimiters, &rest)) != NULL) {
        if (!contains_word(&collection, token)) {
            add_word(&collection, token);
            if (result[0] != '\0') {
                strcat(result, " ");
            }
            strcat(result, token);
        }
    }

    strcpy(str, result);
    free(result);
}

int main() {
    char str[1000];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    remove_duplicate_words(str);

    printf("String after removing duplicates: %s\n", str);

    return 0;
}