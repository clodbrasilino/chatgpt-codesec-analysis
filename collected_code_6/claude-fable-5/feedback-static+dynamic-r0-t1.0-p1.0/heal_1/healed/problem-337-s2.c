#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 4096

bool matches_word_at_end(const char *text, const char *word);

bool matches_word_at_end(const char *text, const char *word)
{
    size_t text_len;
    size_t word_len;
    size_t end;

    if (text == NULL || word == NULL) {
        return false;
    }

    text_len = strnlen(text, MAX_INPUT_LEN);
    if (text_len == MAX_INPUT_LEN && text[MAX_INPUT_LEN - 1] != '\0') {
        return false;
    }

    word_len = strnlen(word, MAX_INPUT_LEN);
    if (word_len == MAX_INPUT_LEN && word[MAX_INPUT_LEN - 1] != '\0') {
        return false;
    }

    if (word_len == 0 || text_len < word_len) {
        return false;
    }

    end = text_len;
    while (end > 0 && ispunct((unsigned char)text[end - 1])) {
        end--;
    }

    if (end < word_len) {
        return false;
    }

    if (strncmp(text + (end - word_len), word, word_len) != 0) {
        return false;
    }

    if (end > word_len) {
        unsigned char before = (unsigned char)text[end - word_len - 1];
        if (!isspace(before)) {
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
        { "Hello world!!!", "world" },
        { "Hello worlds", "world" },
        { "world", "world" },
        { "Hello world", "Hello" },
        { "", "world" }
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        bool result = matches_word_at_end(tests[i][0], tests[i][1]);
        if (printf("Text: \"%s\" Word: \"%s\" -> %s\n",
                   tests[i][0], tests[i][1],
                   result ? "match" : "no match") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}