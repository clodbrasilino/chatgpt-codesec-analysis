#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

static int is_space_char(char c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

static int word_seen(char **seen, size_t count, const char *word)
{
    size_t i;

    for (i = 0; i < count; i++) {
        if (strcmp(seen[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

char *remove_duplicate_words(const char *input)
{
    char **seen = NULL;
    char *result = NULL;
    size_t seen_count = 0;
    size_t seen_capacity = 0;
    size_t result_len = 0;
    size_t input_len;
    size_t pos = 0;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_len = strlen(input);

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    seen_capacity = INITIAL_CAPACITY;
    seen = malloc(seen_capacity * sizeof(*seen));
    if (seen == NULL) {
        free(result);
        return NULL;
    }

    while (pos < input_len) {
        size_t start;
        size_t word_len;
        char *word;

        while (pos < input_len && is_space_char(input[pos])) {
            pos++;
        }
        if (pos >= input_len) {
            break;
        }

        start = pos;
        while (pos < input_len && !is_space_char(input[pos])) {
            pos++;
        }
        word_len = pos - start;

        word = malloc(word_len + 1);
        if (word == NULL) {
            goto fail;
        }
        memcpy(word, input + start, word_len);
        word[word_len] = '\0';

        if (word_seen(seen, seen_count, word)) {
            free(word);
        } else {
            if (seen_count == seen_capacity) {
                size_t new_capacity = seen_capacity * 2;
                char **new_seen = realloc(seen, new_capacity * sizeof(*new_seen));
                if (new_seen == NULL) {
                    free(word);
                    goto fail;
                }
                seen = new_seen;
                seen_capacity = new_capacity;
            }
            seen[seen_count++] = word;

            if (result_len > 0) {
                result[result_len++] = ' ';
            }
            memcpy(result + result_len, word, word_len);
            result_len += word_len;
            result[result_len] = '\0';
        }
    }

    for (i = 0; i < seen_count; i++) {
        free(seen[i]);
    }
    free(seen);
    return result;

fail:
    for (i = 0; i < seen_count; i++) {
        free(seen[i]);
    }
    free(seen);
    free(result);
    return NULL;
}

static char *read_standard_input(void)
{
    size_t capacity = 256;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int ch;

    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = getchar()) != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[length++] = (char)ch;
    }
    buffer[length] = '\0';

    return buffer;
}

static char *join_arguments(int argc, char **argv)
{
    size_t total = 0;
    size_t offset = 0;
    char *buffer;
    int i;

    for (i = 1; i < argc; i++) {
        total += strlen(argv[i]);
    }
    total += (size_t)(argc - 1);

    buffer = malloc(total);
    if (buffer == NULL) {
        return NULL;
    }

    for (i = 1; i < argc; i++) {
        size_t len = strlen(argv[i]);
        if (offset > 0) {
            buffer[offset++] = ' ';
        }
        memcpy(buffer + offset, argv[i], len);
        offset += len;
    }
    buffer[offset] = '\0';

    return buffer;
}

static void strip_surrounding_quotes(char *text)
{
    size_t len;

    if (text == NULL) {
        return;
    }

    len = strlen(text);
    if (len >= 2 && text[0] == '"' && text[len - 1] == '"') {
        memmove(text, text + 1, len - 2);
        text[len - 2] = '\0';
    }
}

int main(int argc, char **argv)
{
    char *input;
    char *deduped;

    if (argc > 1) {
        input = join_arguments(argc, argv);
    } else {
        input = read_standard_input();
    }

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    strip_surrounding_quotes(input);

    deduped = remove_duplicate_words(input);
    free(input);

    if (deduped == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", deduped);
    free(deduped);

    return EXIT_SUCCESS;
}