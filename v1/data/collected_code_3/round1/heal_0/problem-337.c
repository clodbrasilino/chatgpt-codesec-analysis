#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_end_word(const char *str, const char *word) {
    int str_len = strlen(str);
    int word_len = strlen(word);

    if (word_len > str_len)
        return 0;

    str += str_len - word_len;

    if (strcmp(str, word) == 0)
        return 1;

    if (word_len < str_len && !isalnum((unsigned char)str[-1]))
        return strcmp(str, word) == 0;

    return 0;
}

int main() {
    const char *str = "Hello, world!";
    const char *word = "world!";

    if (match_end_word(str, word))
        printf("Match found\n");
    else
        printf("Match not found\n");

    return 0;
}