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
    static const char word[] = "road";
    size_t i;

    if (position > length || length - position < sizeof(word) - 1U) {
        return 0;
    }

    if (position != 0U &&
        !is_word_boundary((unsigned char)input[position - 1U])) {
        return 0;
    }

    for (i = 0U; i < sizeof(word) - 1U; ++i) {
        if (tolower((unsigned char)input[position + i]) !=
            (unsigned char)word[i]) {
            return 0;
        }
    }

    return is_word_boundary(
        (unsigned char)input[position + sizeof(word) - 1U]);
}

static char *abbreviate_road(const char *input, size_t input_length)
{
    static const char replacement[] = "rd.";
    const size_t word_length = sizeof("road") - 1U;
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
    char *buffer = malloc(capacity);
    int ch;

    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
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
    char *input;
    char *result;
    size_t input_length = 0U;

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

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}