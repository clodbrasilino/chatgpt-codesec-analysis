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

static char *remove_matching_words(const char *input, const char *pattern)
{
    size_t input_len;
    size_t pattern_len;
    size_t read_pos = 0;
    size_t write_pos = 0;
    char *output;

    if (input == NULL || pattern == NULL) {
        return NULL;
    }

    input_len = strlen(input);
    pattern_len = strlen(pattern);

    if (input_len == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_len + 1);
    if (output == NULL) {
        return NULL;
    }

    while (read_pos < input_len) {
        size_t separator_start = read_pos;
        size_t word_start;
        size_t word_end;
        size_t separator_len;
        size_t word_len;

        while (read_pos < input_len && is_separator(input[read_pos])) {
            ++read_pos;
        }

        word_start = read_pos;

        while (read_pos < input_len && !is_separator(input[read_pos])) {
            ++read_pos;
        }

        word_end = read_pos;
        separator_len = word_start - separator_start;
        word_len = word_end - word_start;

        if (word_len == 0) {
            if (separator_len > input_len - write_pos) {
                free(output);
                return NULL;
            }

            memcpy(output + write_pos, input + separator_start, separator_len);
            write_pos += separator_len;
            break;
        }

        if (!word_contains_pattern(input + word_start, word_len,
                                   pattern, pattern_len)) {
            if (separator_len > input_len - write_pos) {
                free(output);
                return NULL;
            }

            memcpy(output + write_pos, input + separator_start, separator_len);
            write_pos += separator_len;

            if (word_len > input_len - write_pos) {
                free(output);
                return NULL;
            }

            memcpy(output + write_pos, input + word_start, word_len);
            write_pos += word_len;
        }
    }

    output[write_pos] = '\0';
    return output;
}

static char **filter_string_list(const char *const *list, size_t count,
                                 const char *pattern)
{
    char **result;
    size_t allocation_count;

    if ((list == NULL && count != 0) || pattern == NULL) {
        return NULL;
    }

    allocation_count = count == 0 ? 1 : count;

    if (allocation_count > SIZE_MAX / sizeof(*result)) {
        return NULL;
    }

    result = calloc(allocation_count, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        if (list[i] == NULL) {
            free_string_list(result, i);
            return NULL;
        }

        result[i] = remove_matching_words(list[i], pattern);
        if (result[i] == NULL) {
            free_string_list(result, i);
            return NULL;
        }
    }

    return result;
}

int main(void)
{
    const char *strings[] = {
        "apple banana apricot cherry",
        "cat dog caterpillar bird",
        "alpha beta gamma delta"
    };
    const char pattern[] = "cat";
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    char **filtered = filter_string_list(strings, count, pattern);

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