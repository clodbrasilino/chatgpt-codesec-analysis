#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

#define MAX_WORD_LEN 256
#define MAX_WORDS 100
#define MIN_WORD_LEN 4

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN];
    size_t count;
} WordList;

static bool is_valid_word_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static int find_long_words(const char *str, WordList *list) {
    const char *cursor;
    const char *word_start;
    size_t word_len;

    if (str == NULL || list == NULL) {
        return -1;
    }

    list->count = 0;
    cursor = str;

    while (*cursor != '\0' && list->count < MAX_WORDS) {
        while (*cursor != '\0' && !is_valid_word_char(*cursor)) {
            cursor++;
        }

        if (*cursor == '\0') {
            break;
        }

        word_start = cursor;
        word_len = 0;

        while (*cursor != '\0' && is_valid_word_char(*cursor) && word_len < MAX_WORD_LEN - 1) {
            cursor++;
            word_len++;
        }

        if (word_len >= MIN_WORD_LEN && word_len < MAX_WORD_LEN) {
            strncpy(list->words[list->count], word_start, word_len);
            list->words[list->count][word_len] = '\0';
            list->count++;
        }

        while (*cursor != '\0' && is_valid_word_char(*cursor)) {
            cursor++;
        }
    }

    return 0;
}

int main(void) {
    const char *text = "This is a simple example string with several words of varying lengths";
    WordList list;
    size_t i;

    if (find_long_words(text, &list) != 0) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Words with at least 4 characters:\n");
    for (i = 0; i < list.count; i++) {
        printf("%s\n", list.words[i]);
    }

    return EXIT_SUCCESS;
}