#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 4096

bool matches_word_at_end(const char *str, const char *word)
{
    size_t str_len;
    size_t word_len;
    size_t end;

    if (str == NULL || word == NULL) {
        return false;
    }

    str_len = strnlen(str, MAX_INPUT_LEN);
    if (str_len == MAX_INPUT_LEN && str[MAX_INPUT_LEN - 1] != '\0') {
        return false;
    }

    word_len = strnlen(word, MAX_INPUT_LEN);
    if (word_len == MAX_INPUT_LEN && word[MAX_INPUT_LEN - 1] != '\0') {
        return false;
    }

    if (word_len == 0 || str_len < word_len) {
        return false;
    }

    end = str_len;
    while (end > 0 && ispunct((unsigned char)str[end - 1])) {
        end--;
    }

    if (end < word_len) {
        return false;
    }

    if (strncmp(str + (end - word_len), word, word_len) != 0) {
        return false;
    }

    if (end > word_len) {
        unsigned char before = (unsigned char)str[end - word_len - 1];
        if (isalnum(before) || before == '_') {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *tests[][2] = {
        { "Hello world", "world" },
        { "Hello world!", "world" },
        { "Hello world...", "world" },
        { "Hello worldly", "world" },
        { "world", "world" },
        { "Say hello", "world" },
        { "", "world" }
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        bool result = matches_word_at_end(tests[i][0], tests[i][1]);
        if (printf("\"%s\" ends with \"%s\": %s\n",
                   tests[i][0], tests[i][1],
                   result ? "yes" : "no") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}