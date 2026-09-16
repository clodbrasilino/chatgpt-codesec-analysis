#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool is_word_character(unsigned char character)
{
    return isalnum(character) != 0 || character == '_';
}

static bool contains_word(const char *sentence, const char *word)
{
    size_t sentence_length;
    size_t word_length;

    if (sentence == NULL || word == NULL || word[0] == '\0') {
        return false;
    }

    sentence_length = strlen(sentence);
    word_length = strlen(word);

    if (word_length > sentence_length) {
        return false;
    }

    for (size_t i = 0; i <= sentence_length - word_length; ++i) {
        bool left_boundary = i == 0 ||
                             !is_word_character((unsigned char)sentence[i - 1]);
        bool right_boundary =
            i + word_length == sentence_length ||
            !is_word_character((unsigned char)sentence[i + word_length]);

        if (left_boundary && right_boundary &&
            memcmp(sentence + i, word, word_length) == 0) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char sentence[1024];
    char word[256];

    if (fgets(sentence, sizeof sentence, stdin) == NULL) {
        return 1;
    }

    if (fgets(word, sizeof word, stdin) == NULL) {
        return 1;
    }

    sentence[strcspn(sentence, "\r\n")] = '\0';
    word[strcspn(word, "\r\n")] = '\0';

    if (word[0] == '\0') {
        return 1;
    }

    if (contains_word(sentence, word)) {
        puts("Word is present.");
    } else {
        puts("Word is not present.");
    }

    return 0;
}