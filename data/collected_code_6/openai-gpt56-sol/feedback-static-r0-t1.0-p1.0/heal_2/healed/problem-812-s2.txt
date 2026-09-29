#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_word_boundary(unsigned char c)
{
    return c == '\0' || !isalnum(c);
}

static int matches_road(const char *input, size_t length, size_t position)
{
    static const unsigned char word[] = "road";
    const size_t word_length = sizeof(word) - 1U;
    size_t i;

    if (input == NULL || position > length ||
        word_length > length - position) {
        return 0;
    }

    if (position != 0U &&
        !is_word_boundary((unsigned char)input[position - 1U])) {
        return 0;
    }

    for (i = 0U; i < word_length; ++i) {
        if ((unsigned char)tolower((unsigned char)input[position + i]) !=
            word[i]) {
            return 0;
        }
    }

    if (position + word_length == length) {
        return 1;
    }

    return is_word_boundary((unsigned char)input[position + word_length]);
}

static char *abbreviate_road(const char *input, size_t input_length)
{
    static const char replacement[] = "rd.";
    const size_t word_length = sizeof("road") - 1U;
    const size_t replacement_length = sizeof(replacement) - 1U;
    const size_t reduction_per_match = word_length - replacement_length;
    size_t match_count = 0U;
    size_t output_length;
    size_t i = 0U;
    size_t j = 0U;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    while (i < input_length) {
        if (matches_road(input, input_length, i)) {
            ++match_count;
            i += word_length;
        } else {
            ++i;
        }
    }

    if (match_count > input_length / reduction_per_match) {
        return NULL;
    }

    output_length = input_length - match_count * reduction_per_match;

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    i = 0U;

    while (i < input_length) {
        if (matches_road(input, input_length, i)) {
            memcpy(output + j, replacement, replacement_length);
            j += replacement_length;
            i += word_length;
        } else {
            output[j++] = input[i++];
        }
    }

    output[j] = '\0';
    return output;
}

static char *read_line(FILE *stream, size_t *length)
{
    size_t capacity = 128U;
    size_t used = 0U;
    char *buffer;
    int ch = EOF;

    if (stream == NULL || length == NULL) {
        return NULL;
    }

    *length = 0U;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (used == SIZE_MAX - 1U) {
            free(buffer);
            return NULL;
        }

        if (used + 1U >= capacity) {
            size_t required = used + 2U;
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity < required) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)(unsigned char)ch;
    }

    if (ch == EOF) {
        if (ferror(stream)) {
            free(buffer);
            return NULL;
        }

        if (used == 0U) {
            free(buffer);
            return NULL;
        }
    }

    if (used > 0U && buffer[used - 1U] == '\r') {
        --used;
    }

    buffer[used] = '\0';
    *length = used;
    return buffer;
}

int main(void)
{
    char *input;
    char *result;
    size_t input_length;

    input = read_line(stdin, &input_length);
    if (input == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    result = abbreviate_road(input, input_length);
    free(input);

    if (result == NULL) {
        fputs("Failed to abbreviate input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}