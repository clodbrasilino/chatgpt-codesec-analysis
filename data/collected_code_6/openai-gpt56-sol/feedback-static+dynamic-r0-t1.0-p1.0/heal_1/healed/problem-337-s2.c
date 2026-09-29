#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_word_at_end(const char *string, size_t string_size,
                                const char *word, size_t word_size)
{
    const char *string_end;
    const char *word_end;
    size_t string_length;
    size_t word_length;
    size_t end;

    if (string == NULL || word == NULL || string_size == 0U || word_size == 0U) {
        return false;
    }

    string_end = memchr(string, '\0', string_size);
    word_end = memchr(word, '\0', word_size);

    if (string_end == NULL || word_end == NULL || word_end == word) {
        return false;
    }

    string_length = (size_t)(string_end - string);
    word_length = (size_t)(word_end - word);
    end = string_length;

    while (end > 0U && isspace((unsigned char)string[end - 1U]) != 0) {
        --end;
    }

    while (end > 0U && ispunct((unsigned char)string[end - 1U]) != 0) {
        --end;
    }

    if (end < word_length) {
        return false;
    }

    if (memcmp(string + end - word_length, word, word_length) != 0) {
        return false;
    }

    return end == word_length ||
           isalnum((unsigned char)string[end - word_length - 1U]) == 0;
}

int main(void)
{
    static const char text[] = "The final word is example!";
    static const char word[] = "example";

    if (matches_word_at_end(text, sizeof text, word, sizeof word)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}