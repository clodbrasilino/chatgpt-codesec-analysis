#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_WORD_LEN 256
#define MAX_WORDS 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *words[MAX_WORDS];
    size_t count;
} WordList;

void free_word_list(WordList *list) {
    size_t i;
    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        free(list->words[i]);
        list->words[i] = NULL;
    }
    list->count = 0;
}

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
    memset(list->words, 0, sizeof(list->words));

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t len = (size_t)(match.rm_eo - match.rm_so);

        if (len == 0) {
            cursor += 1;
            continue;
        }

        if (len >= MAX_WORD_LEN || list->count >= MAX_WORDS) {
            regfree(&regex);
            free_word_list(list);
            return -1;
        }

        list->words[list->count] = (char *)malloc(len + 1);
        if (list->words[list->count] == NULL) {
            regfree(&regex);
            free_word_list(list);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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

    free_word_list(&list);
    return EXIT_SUCCESS;
}