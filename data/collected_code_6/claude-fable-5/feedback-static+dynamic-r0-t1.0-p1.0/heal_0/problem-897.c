#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_word_present(const char *sentence, const char *word)
{
    size_t word_len;
    size_t i;
    size_t sent_len;

    if (sentence == NULL || word == NULL) {
        return 0;
    }

    word_len = strlen(word);
    if (word_len == 0U) {
        return 0;
    }

    sent_len = strlen(sentence);
    if (sent_len < word_len) {
        return 0;
    }

    for (i = 0U; i + word_len <= sent_len; i++) {
        int start_ok;
        int end_ok;

        if (strncmp(&sentence[i], word, word_len) != 0) {
            continue;
        }

        start_ok = (i == 0U) ||
                   (isalnum((unsigned char)sentence[i - 1U]) == 0);
        end_ok = (sentence[i + word_len] == '\0') ||
                 (isalnum((unsigned char)sentence[i + word_len]) == 0);

        if ((start_ok != 0) && (end_ok != 0)) {
            return 1;
        }
    }

    return 0;
}

static void strip_newline(char *str)
{
    size_t len;

    if (str == NULL) {
        return;
    }

    len = strlen(str);
    if (len > 0U && str[len - 1U] == '\n') {
        str[len - 1U] = '\0';
    }
}

int main(void)
{
    char sentence[1024];
    char word[256];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence.\n");
        return EXIT_FAILURE;
    }
    strip_newline(sentence);

    printf("Enter a word: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word.\n");
        return EXIT_FAILURE;
    }
    strip_newline(word);

    if (is_word_present(sentence, word) != 0) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return EXIT_SUCCESS;
}