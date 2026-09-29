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
    size_t word_length;
    const char *match;

    if (sentence == NULL || word == NULL || word[0] == '\0') {
        return false;
    }

    word_length = strlen(word);
    match = sentence;

    while ((match = strstr(match, word)) != NULL) {
        bool valid_start = match == sentence ||
                           !is_word_character((unsigned char)match[-1]);
        bool valid_end = !is_word_character((unsigned char)match[word_length]);

        if (valid_start && valid_end) {
            return true;
        }

        ++match;
    }

    return false;
}

int main(void)
{
    char sentence[1024];
    char word[256];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        return 1;
    }

    if (strchr(sentence, '\n') == NULL && !feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        fprintf(stderr, "Sentence is too long.\n");
        return 1;
    }

    sentence[strcspn(sentence, "\n")] = '\0';

    printf("Enter a word: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        return 1;
    }

    if (strchr(word, '\n') == NULL && !feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        fprintf(stderr, "Word is too long.\n");
        return 1;
    }

    word[strcspn(word, "\n")] = '\0';

    if (word[0] == '\0') {
        fprintf(stderr, "Word must not be empty.\n");
        return 1;
    }

    puts(contains_word(sentence, word) ? "Word is present." : "Word is not present.");

    return 0;
}