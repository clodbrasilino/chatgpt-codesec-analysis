#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 1024

static int is_word_present(const char *sentence, const char *word)
{
    size_t word_len;
    const char *p;

    if (sentence == NULL || word == NULL) {
        return 0;
    }

    word_len = strnlen(word, MAX_LEN);
    if (word_len == 0U || word_len >= MAX_LEN) {
        return 0;
    }

    p = sentence;
    while (*p != '\0') {
        while (*p != '\0' && !isalnum((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        const char *start = p;
        while (*p != '\0' && isalnum((unsigned char)*p)) {
            p++;
        }
        size_t token_len = (size_t)(p - start);
        if (token_len == word_len && strncmp(start, word, word_len) == 0) {
            return 1;
        }
    }
    return 0;
}

static void strip_newline(char *s, size_t max_size)
{
    size_t len;

    if (s == NULL) {
        return;
    }

    len = strnlen(s, max_size);
    if (len > 0U && s[len - 1U] == '\n') {
        s[len - 1U] = '\0';
    }
}

int main(void)
{
    char sentence[MAX_LEN];
    char word[MAX_LEN];

    memset(sentence, 0, sizeof(sentence));
    memset(word, 0, sizeof(word));

    printf("Enter a sentence: ");
    if (fgets(sentence, (int)sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence.\n");
        return EXIT_FAILURE;
    }
    sentence[sizeof(sentence) - 1U] = '\0';
    strip_newline(sentence, sizeof(sentence));

    printf("Enter a word: ");
    if (fgets(word, (int)sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word.\n");
        return EXIT_FAILURE;
    }
    word[sizeof(word) - 1U] = '\0';
    strip_newline(word, sizeof(word));

    if (is_word_present(sentence, word) == 1) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return EXIT_SUCCESS;
}