#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

static int is_word_char(int c)
{
    return isalnum((unsigned char)c) || c == '_';
}

static char *copy_word(const char *start, size_t length)
{
    char *word;

    if (start == NULL || length >= SIZE_MAX) {
        return NULL;
    }

    word = malloc(length + 1);
    if (word == NULL) {
        return NULL;
    }

    memcpy(word, start, length);
    word[length] = '\0';
    return word;
}

typedef struct {
    char *text;
    size_t length;
} word_entry_t;

char *find_first_repeated_word(const char *str)
{
    word_entry_t *seen_words = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *p;
    char *result = NULL;

    if (str == NULL) {
        return NULL;
    }

    p = str;

    while (*p != '\0') {
        const char *start;
        size_t length;
        size_t i;
        int found = 0;

        while (*p != '\0' && !is_word_char((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        start = p;
        while (*p != '\0' && is_word_char((unsigned char)*p)) {
            p++;
        }
        length = (size_t)(p - start);

        for (i = 0; i < count; i++) {
            if (seen_words[i].length == length &&
                memcmp(seen_words[i].text, start, length) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            result = copy_word(start, length);
            break;
        }

        if (count == capacity) {
            size_t new_capacity = (capacity == 0) ? 8 : capacity * 2;
            word_entry_t *new_array;

            if (new_capacity > SIZE_MAX / sizeof(*seen_words)) {
                break;
            }

            new_array = realloc(seen_words,
                                new_capacity * sizeof(*new_array));
            if (new_array == NULL) {
                break;
            }
            seen_words = new_array;
            capacity = new_capacity;
        }

        seen_words[count].text = copy_word(start, length);
        if (seen_words[count].text == NULL) {
            break;
        }
        seen_words[count].length = length;
        count++;
    }

    for (size_t i = 0; i < count; i++) {
        free(seen_words[i].text);
    }
    free(seen_words);

    return result;
}

int main(void)
{
    char buffer[8192];
    size_t len;
    char *word;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("None\n");
        return 0;
    }

    len = strlen(buffer);
    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[--len] = '\0';
    }

    word = find_first_repeated_word(buffer);
    if (word != NULL) {
        printf("%s\n", word);
        free(word);
    } else {
        printf("None\n");
    }

    return 0;
}