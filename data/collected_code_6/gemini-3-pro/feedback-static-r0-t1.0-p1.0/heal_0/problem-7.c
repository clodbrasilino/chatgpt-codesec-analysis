#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **find_words_min_length_4(const char *text, size_t *out_count);
void free_words(char **words, size_t count);

char **find_words_min_length_4(const char *text, size_t *out_count) {
    if (!text || !out_count) {
        return NULL;
    }

    *out_count = 0;

    regex_t regex;
    if (regcomp(&regex, "[a-zA-Z]{4,}", REG_