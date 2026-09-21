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

    if (position > 0U &&
        !is_word_boundary((unsigned char)input[position - 1U])) {
        return 0;
    }

    for (i = 0U; i < word_length; ++i) {
        unsigned char c = (unsigned char)input[position + i];

        if ((unsigned char)tolower(c) != word[i]) {
            return 0;
        }
    }

    return position + word_length == length ||
           is_word_boundary((unsigned char)input[position + word_length]);
}

static char *abbreviate_road(const char *input, size_t input_length)
{
    static const char replacement[] = "rd.";
    const size_t word_length = sizeof("road") - 1U;
    const size_t replacement_length = sizeof(replacement) - 1U;
    const size_t reduction = word_length - replacement_length;
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

    if (match_count > input_length / reduction) {
        return NULL;
    }

    output_length = input_length - match_count * reduction;

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
            if (replacement_length > output_length - j) {
                free(output);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + j, replacement, replacement_length);
            j += replacement_length;
            i += word_length;
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

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || *buffer == NULL || capacity == NULL ||
        required <= *capacity) {
        return required <= (capacity == NULL ? 0U : *capacity);
    }

    new_capacity = *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = SIZE_MAX;
        } else {
            new_capacity *= 2U;
        }

        if (new_capacity < required && new_capacity == SIZE_MAX) {
            return 0;
        }
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

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

        if (used > SIZE_MAX - 2U) {
            free(buffer);
            return NULL;
        }

        if (!grow_buffer(&buffer, &capacity, used + 2U)) {
            free(buffer);
            return NULL;
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