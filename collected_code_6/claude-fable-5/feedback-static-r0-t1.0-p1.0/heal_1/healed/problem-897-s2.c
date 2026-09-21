#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SENTENCE_MAX 256
#define WORD_MAX 64

int is_word_present(const char *sentence, const char *word);
static int read_line(char *buffer, size_t size, const char *prompt);

int is_word_present(const char *sentence, const char *word)
{
    size_t word_len;
    size_t i;

    if (sentence == NULL || word == NULL) {
        return 0;
    }

    word_len = strnlen(word, WORD_MAX);
    if (word_len == 0U || word_len >= WORD_MAX) {
        return 0;
    }

    i = 0U;
    while (i < SENTENCE_MAX && sentence[i] != '\0') {
        while (i < SENTENCE_MAX && sentence[i] != '\0' &&
               !isalnum((unsigned char)sentence[i])) {
            i++;
        }
        if (i >= SENTENCE_MAX || sentence[i] == '\0') {
            break;
        }

        size_t start = i;
        while (i < SENTENCE_MAX && sentence[i] != '\0' &&
               isalnum((unsigned char)sentence[i])) {
            i++;
        }
        size_t token_len = i - start;

        if (token_len == word_len &&
            strncmp(&sentence[start], word, word_len) == 0) {
            return 1;
        }
    }

    return 0;
}

static int read_line(char *buffer, size_t size, const char *prompt)
{
    size_t len;

    if (buffer == NULL || size == 0U || prompt == NULL) {
        return -1;
    }

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    len = strcspn(buffer, "\n");
    if (buffer[len] == '\n') {
        buffer[len] = '\0';
    } else if (len == size - 1U) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }
    buffer[size - 1U] = '\0';

    return 0;
}

int main(void)
{
    char sentence[SENTENCE_MAX] = {0};
    char word[WORD_MAX] = {0};

    if (read_line(sentence, sizeof(sentence), "Enter a sentence: ") != 0) {
        fprintf(stderr, "Error reading sentence.\n");
        return EXIT_FAILURE;
    }

    if (read_line(word, sizeof(word), "Enter a word to search: ") != 0) {
        fprintf(stderr, "Error reading word.\n");
        return EXIT_FAILURE;
    }

    if (is_word_present(sentence, word) == 1) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return EXIT_SUCCESS;
}