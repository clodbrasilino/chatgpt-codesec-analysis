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
    return position <= length &&
           length - position >= 4U &&
           (position == 0U ||
            is_word_boundary((unsigned char)input[position - 1U])) &&
           tolower((unsigned char)input[position]) == 'r' &&
           tolower((unsigned char)input[position + 1U]) == 'o' &&
           tolower((unsigned char)input[position + 2U]) == 'a' &&
           tolower((unsigned char)input[position + 3U]) == 'd' &&
           is_word_boundary((unsigned char)input[position + 4U]);
}

static char *abbreviate_road(const char *input, size_t input_length)
{
    static const char replacement[] = "rd.";
    const size_t word_length = 4U;
    const size_t replacement_length = sizeof(replacement) - 1U;
    size_t match_count = 0U;
    size_t output_length;
    size_t i;
    size_t j;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    for (i = 0U; i < input_length;) {
        if (matches_road(input, input_length, i)) {
            ++match_count;
            i += word_length;
        } else {
            ++i;
        }
    }

    if (match_count > input_length / (word_length - replacement_length)) {
        return NULL;
    }

    output_length =
        input_length - match_count * (word_length - replacement_length);

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    i = 0U;
    j = 0U;

    while (i < input_length) {
        if (matches_road(input, input_length, i)) {
            if (replacement_length > output_length - j) {
                free(output);
                return NULL;
            }

            memcpy(output + j, replacement, replacement_length);
            i += word_length;
            j += replacement_length;
        } else {
            if (j >= output_length) {
                free(output);
                return NULL;
            }

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
    char *buffer = malloc(capacity);
    int ch;

    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (used + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && used == 0U) {
        free(buffer);
        *length = 0U;
        return NULL;
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
    size_t input_length;
    char *input;
    char *result;

    input = read_line(stdin, &input_length);
    if (input == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    result = abbreviate_road(input, input_length);
    free(input);

    if (result == NULL) {
        fprintf(stderr, "Failed to abbreviate input.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}