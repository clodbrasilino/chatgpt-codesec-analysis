#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int match_word_at_end(const char *str, const char *word) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = str ? strlen(str) : 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = word ? strlen(word) : 0;

    while (str_len > 0 && isspace(str[str_len - 1])) {
        --str_len;
    }
    while (str_len > word_len && (str[str_len - 1] == '.' || str[str_len - 1] == ',' || str[str_len - 1] == '!' || str[str_len - 1] == '?' || str[str_len - 1] == ';' || str[str_len - 1] == ':')) {
        --str_len;
    }

    if (str_len < word_len) {
        return 0;
    }

    return strncmp(&str[str_len - word_len], word, word_len) == 0;
}

int main() {
    const char *sentence = "Hello world!";
    const char *word = "world";

    if (match_word_at_end(sentence, word)) {
        printf("Match found.\n");
    } else {
        printf("No match found.\n");
    }

    return 0;
}