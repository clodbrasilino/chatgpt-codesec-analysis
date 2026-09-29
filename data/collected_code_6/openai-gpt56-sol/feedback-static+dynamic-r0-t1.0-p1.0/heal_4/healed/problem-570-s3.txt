#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_separator(char c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

static void free_string_list(char **list, size_t count)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(list[i]);
    }

    free(list);
}

static int word_contains_pattern(const char *word, size_t word_len,
                                 const char *pattern, size_t pattern_len)
{
    if (pattern_len == 0) {
        return 1;
    }

    if (pattern_len > word_len) {
        return 0;
    }

    for (size_t i = 0; i <= word_len - pattern_len; ++i) {
        if (memcmp(word + i, pattern, pattern_len) == 0) {
            return 1;
        }
    }

    return 0;
}

static int append_bytes(char *destination, size_t capacity, size_t *position,
                        const char *source, size_t length)
{
    if (destination == NULL || position == NULL ||
        (source == NULL && length != 0) ||
        *position > capacity || length > capacity - *position) {
        return 0;
    }

    if (length > 0) {
        memmove(destination + *position, source, length);
        *position += length;
    }

    return 1;
}

static char *remove_matching_words(const char *input, size_t input_len,
                                   const char *pattern, size_t pattern_len)
{
    size_t read_pos = 0;
    size_t write_pos = 0;

    if ((input == NULL && input_len != 0) ||
        (pattern == NULL && pattern_len != 0) ||
        input_len == SIZE_MAX) {
        return NULL;
    }

    char *output = malloc(input_len + 1);
    if (output == NULL) {
        return NULL;
    }

    while (read_pos < input_len) {
        size_t separator_start = read_pos;

        while (read_pos < input_len && is_separator(input[read_pos])) {
            ++read_pos;
        }

        size_t word_start = read_pos;

        while (read_pos < input_len && !is_separator(input[read_pos])) {
            ++read_pos;
        }

        size_t word_end = read_pos;
        size_t separator_len = word_start - separator_start;
        size_t word_len = word_end - word_start;

        if (word_len == 0) {
            if (!append_bytes(output, input_len, &write_pos,
                              input + separator_start, separator_len)) {
                free(output);
                return NULL;
            }
            break;
        }

        if (!word_contains_pattern(input + word_start, word_len,
                                   pattern, pattern_len)) {
            if (!append_bytes(output, input_len, &write_pos,
                              input + separator_start, separator_len) ||
                !append_bytes(output, input_len, &write_pos,
                              input + word_start, word_len)) {
                free(output);
                return NULL;
            }
        }
    }

    output[write_pos] = '\0';
    return output;
}

static char **filter_string_list(const char *const *list,
                                 const size_t *lengths, size_t count,
                                 const char *pattern, size_t pattern_len)
{
    size_t allocation_count = count == 0 ? 1 : count;

    if ((count != 0 && (list == NULL || lengths == NULL)) ||
        (pattern == NULL && pattern_len != 0) ||
        allocation_count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    char **result = calloc(allocation_count, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (list[i] == NULL && lengths[i] != 0) {
            free_string_list(result, i);
            return NULL;
        }

        result[i] = remove_matching_words(list[i], lengths[i],
                                          pattern, pattern_len);
        if (result[i] == NULL) {
            free_string_list(result, i);
            return NULL;
        }
    }

    return result;
}

int main(void)
{
    static const char string0[] = "apple banana apricot cherry";
    static const char string1[] = "cat dog caterpillar bird";
    static const char string2[] = "alpha beta gamma delta";
    static const char pattern[] = "cat";

    const char *strings[] = {
        string0,
        string1,
        string2
    };

    const size_t lengths[] = {
        sizeof(string0) - 1,
        sizeof(string1) - 1,
        sizeof(string2) - 1
    };

    const size_t count = sizeof(strings) / sizeof(strings[0]);

    char **filtered = filter_string_list(strings, lengths, count,
                                         pattern, sizeof(pattern) - 1);
    if (filtered == NULL) {
        fputs("Failed to filter strings.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (puts(filtered[i]) == EOF) {
            free_string_list(filtered, count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(filtered, count);
    return EXIT_SUCCESS;
}