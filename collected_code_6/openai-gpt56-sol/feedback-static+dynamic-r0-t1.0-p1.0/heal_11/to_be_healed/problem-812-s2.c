#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_word_boundary(unsigned char c)
{
    return c == '\0' || !isalnum(c);
}

static int matches_road(const char *input, size_t length, size_t position)
{
    if (input == NULL || position > length || length - position < 4U) {
        return 0;
    }

    if (position > 0U &&
        !is_word_boundary((unsigned char)input[position - 1U])) {
        return 0;
    }

    return tolower((unsigned char)input[position]) == 'r' &&
           tolower((unsigned char)input[position + 1U]) == 'o' &&
           tolower((unsigned char)input[position + 2U]) == 'a' &&
           tolower((unsigned char)input[position + 3U]) == 'd' &&
           (length - position == 4U ||
            is_word_boundary((unsigned char)input[position + 4U]));
}

static char *abbreviate_road(const char *input, size_t input_length)
{
    static const char replacement[] = "rd.";
    const size_t word_length = 4U;
    const size_t replacement_length = sizeof replacement - 1U;
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
            if (match_count == SIZE_MAX) {
                return NULL;
            }
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

    while (i < input_length) {
        if (matches_road(input, input_length, i)) {
            size_t k;

            for (k = 0U; k < replacement_length; ++k) {
                output[j++] = replacement[k];
            }
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

    if (stream == NULL || length == NULL) {
        return NULL;
    }

    *length = 0U;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch;

        if (used == capacity - 1U) {
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

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || used == 0U) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        buffer[used++] = (char)(unsigned char)ch;
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
    size_t input_length = 0U;
    char *input;
    char *result;

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