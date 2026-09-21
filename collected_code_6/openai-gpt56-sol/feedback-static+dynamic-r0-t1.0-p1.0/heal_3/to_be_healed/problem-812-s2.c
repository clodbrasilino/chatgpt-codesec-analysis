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
    if (input == NULL || position > length || length - position < 4U) {
        return 0;
    }

    if (position != 0U &&
        !is_word_boundary((unsigned char)input[position - 1U])) {
        return 0;
    }

    return tolower((unsigned char)input[position]) == 'r' &&
           tolower((unsigned char)input[position + 1U]) == 'o' &&
           tolower((unsigned char)input[position + 2U]) == 'a' &&
           tolower((unsigned char)input[position + 3U]) == 'd' &&
           (position + 4U == length ||
            is_word_boundary((unsigned char)input[position + 4U]));
}

static char *abbreviate_road(const char *input, size_t input_length)
{
    static const char replacement[] = "rd.";
    const size_t word_length = 4U;
    const size_t replacement_length = sizeof(replacement) - 1U;
    size_t match_count = 0U;
    size_t reduction;
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

    if (match_count > SIZE_MAX / (word_length - replacement_length)) {
        return NULL;
    }

    reduction = match_count * (word_length - replacement_length);
    if (reduction > input_length) {
        return NULL;
    }

    output_length = input_length - reduction;
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
            if (j > output_length ||
                replacement_length > output_length - j) {
                free(output);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
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

    if (j != output_length) {
        free(output);
        return NULL;
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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (used >= capacity - 1U) {
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

        buffer[used++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && used == 0U) {
        free(buffer);
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