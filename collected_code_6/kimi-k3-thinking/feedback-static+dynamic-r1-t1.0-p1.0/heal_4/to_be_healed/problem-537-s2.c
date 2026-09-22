#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

typedef struct {
    char *text;
    size_t length;
} word_entry_t;

static int is_word_char(int c)
{
    return isalnum((unsigned char)c) || c == '_';
}

static char *copy_word(const char *start, size_t length)
{
    char *word;

    if (start == NULL || length == 0 || length >= SIZE_MAX) {
        return NULL;
    }

    word = malloc(length + 1);
    if (word == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(word, start, length);
    word[length] = '\0';

    return word;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 256;
    size_t length = 0;
    char *buffer;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            new_capacity = capacity * 2;

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[length] = (char)ch;
        length++;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    while (length > 0 && buffer[length - 1] == '\r') {
        length--;
    }
    buffer[length] = '\0';

    return buffer;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char *find_first_repeated_word(const char *str)
{
    word_entry_t *seen_words = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *p;
    char *result = NULL;
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    p = str;

    while (*p != '\0') {
        const char *start;
        size_t length;
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
            size_t new_capacity;
            word_entry_t *new_array;

            if (capacity > SIZE_MAX / 2) {
                break;
            }
            new_capacity = (capacity == 0) ? 8 : capacity * 2;

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

    for (i = 0; i < count; i++) {
        free(seen_words[i].text);
    }
    free(seen_words);

    return result;
}

int main(void)
{
    char *line;
    char *word;

    line = read_line(stdin);
    if (line == NULL) {
        printf("None\n");
        return 0;
    }

    word = find_first_repeated_word(line);
    free(line);

    if (word != NULL && word[0] != '\0') {
        printf("%s\n", word);
    } else {
        printf("None\n");
    }

    free(word);

    return 0;
}