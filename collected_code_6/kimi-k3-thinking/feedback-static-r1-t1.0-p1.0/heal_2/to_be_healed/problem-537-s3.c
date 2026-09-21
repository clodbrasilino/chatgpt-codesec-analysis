#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

struct word_entry {
    char *text;
    size_t length;
};

static int is_delimiter(char c)
{
    return isspace((unsigned char)c) || ispunct((unsigned char)c);
}

static char *copy_word(const char *start, size_t len)
{
    char *word;

    if (start == NULL) {
        return NULL;
    }

    word = malloc(len + 1);
    if (word == NULL) {
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, start, len);
    }
    word[len] = '\0';
    return word;
}

static void free_words(struct word_entry *words, size_t count)
{
    size_t i;
    for (i = 0; i < count; i++) {
        free(words[i].text);
    }
    free(words);
}

char *find_first_repeated_word(const char *str)
{
    size_t capacity = 16;
    size_t count = 0;
    struct word_entry *seen;
    struct word_entry *resized;
    const char *p;

    if (str == NULL || *str == '\0') {
        return NULL;
    }

    seen = malloc(capacity * sizeof(*seen));
    if (seen == NULL) {
        return NULL;
    }

    p = str;
    while (*p != '\0') {
        const char *start;
        size_t len;
        size_t i;

        while (*p != '\0' && is_delimiter(*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        start = p;
        while (*p != '\0' && !is_delimiter(*p)) {
            p++;
        }
        len = (size_t)(p - start);

        for (i = 0; i < count; i++) {
            if (seen[i].length == len &&
                memcmp(seen[i].text, start, len) == 0) {
                char *result = copy_word(start, len);
                free_words(seen, count);
                return result;
            }
        }

        if (count == capacity) {
            if (capacity > ((size_t)-1) / 2 / sizeof(*resized)) {
                free_words(seen, count);
                return NULL;
            }
            resized = realloc(seen, capacity * 2 * sizeof(*resized));
            if (resized == NULL) {
                free_words(seen, count);
                return NULL;
            }
            seen = resized;
            capacity *= 2;
        }

        seen[count].text = copy_word(start, len);
        if (seen[count].text == NULL) {
            free_words(seen, count);
            return NULL;
        }
        seen[count].length = len;
        count++;
    }

    free_words(seen, count);
    return NULL;
}

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t nread;
    char *word;

    printf("Enter a string: ");
    nread = getline(&input, &input_size, stdin);
    if (nread < 0) {
        fprintf(stderr, "Error: failed to read input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    word = find_first_repeated_word(input);
    if (word != NULL) {
        printf("First repeated word: %s\n", word);
        free(word);
    } else {
        printf("No repeated word found.\n");
    }

    free(input);
    return EXIT_SUCCESS;
}