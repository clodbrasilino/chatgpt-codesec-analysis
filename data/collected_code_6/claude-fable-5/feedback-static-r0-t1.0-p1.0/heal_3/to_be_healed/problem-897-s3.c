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

    if (s == NULL || max_size == 0U) {
        return;
    }

    len = strnlen(s, max_size);
    if (len > 0U && s[len - 1U] == '\n') {
        s[len - 1U] = '\0';
    }
}

static int read_line(const char *prompt, char *buffer, size_t size)
{
    if (buffer == NULL || size == 0U) {
        return -1;
    }

    memset(buffer, 0, size);

    if (prompt != NULL) {
        printf("%s", prompt);
        (void)fflush(stdout);
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1U] = '\0';
    strip_newline(buffer, size);
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[MAX_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_LEN];

    if (read_line("Enter a sentence: ", sentence, sizeof(sentence)) != 0) {
        fprintf(stderr, "Error reading sentence.\n");
        return EXIT_FAILURE;
    }

    if (read_line("Enter a word: ", word, sizeof(word)) != 0) {
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