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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_len = strlen(text);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char text[1024];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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