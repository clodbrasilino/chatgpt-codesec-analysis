#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_word_at_end(const char *text, const char *word)
{
    size_t text_len;
    size_t word_len;
    size_t end;

    if (text == NULL || word == NULL || word[0] == '\0') {
        return false;
    }

    text_len = strlen(text);
    word_len = strlen(word);
    end = text_len;

    while (end > 0U && isspace((unsigned char)text[end - 1U]) != 0) {
        --end;
    }

    if (end > 0U && ispunct((unsigned char)text[end - 1U]) != 0) {
        --end;
    }

    while (end > 0U && isspace((unsigned char)text[end - 1U]) != 0) {
        --end;
    }

    if (word_len > end) {
        return false;
    }

    if (memcmp(text + end - word_len, word, word_len) != 0) {
        return false;
    }

    return end == word_len ||
           !(isalnum((unsigned char)text[end - word_len - 1U]) != 0 ||
             text[end - word_len - 1U] == '_');
}

int main(void)
{
    char text[1024];
    char word[256];

    if (fgets(text, sizeof text, stdin) == NULL) {
        return 1;
    }

    if (fgets(word, sizeof word, stdin) == NULL) {
        return 1;
    }

    text[strcspn(text, "\r\n")] = '\0';
    word[strcspn(word, "\r\n")] = '\0';

    if (word[0] == '\0') {
        return 1;
    }

    puts(matches_word_at_end(text, word) ? "match" : "no match");
    return 0;
}