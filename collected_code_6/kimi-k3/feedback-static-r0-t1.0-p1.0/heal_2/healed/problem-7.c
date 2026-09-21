#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_WORD_LEN 256
#define MAX_WORDS 100

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN];
    size_t count;
} WordList;

int find_long_words(const char *str, WordList *list) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[a-zA-Z]{4,}";
    const char *cursor = str;
    int ret;

    if (str == NULL || list == NULL) {
        return -1;
    }

    list->count = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t len = (size_t)(match.rm_eo - match.rm_so);

        if (len >= MAX_WORD_LEN || list->count >= MAX_WORDS) {
            regfree(&regex);
            return -1;
        }

        memcpy(list->words[list->count], cursor + match.rm_so, len);
        list->words[list->count][len] = '\0';
        list->count++;

        cursor += match.rm_eo;
    }

    regfree(&regex);
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