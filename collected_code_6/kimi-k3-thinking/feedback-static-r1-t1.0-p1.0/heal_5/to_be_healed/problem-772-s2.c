#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

#define READ_CHUNK_SIZE 128

char *remove_words_of_length(const char *str, size_t str_size, size_t k)
{
    if (str == NULL || str_size == 0) {
        return NULL;
    }

    size_t str_len = strnlen(str, str_size);
    if (str_len == SIZE_MAX) {
        return NULL;
    }

    const size_t capacity = str_len + 1u;

    char *result = malloc(capacity);
    if (result == NULL) {
        return NULL;
    }

    const char *read_ptr = str;
    const char *str_end = str + str_len;
    char *write_ptr = result;
    int separator_needed = 0;

    while (read_ptr < str_end) {
        while (read_ptr < str_end && isspace((unsigned char)*read_ptr)) {
            read_ptr++;
        }
        if (read_ptr == str_end) {
            break;
        }

        const char *word_start = read_ptr;
        while (read_ptr < str_end && !isspace((unsigned char)*read_ptr)) {
            read_ptr++;
        }

        size_t word_len = (size_t)(read_ptr - word_start);

        if (word_len != k) {
            size_t used = (size_t)(write_ptr - result);
            size_t available = capacity - used - 1u;
            size_t separator = (size_t)separator_needed;

            if (word_len > available || separator > available - word_len) {
                free(result);
                return NULL;
            }

            if (separator_needed) {
                *write_ptr = ' ';
                write_ptr++;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(write_ptr, word_start, word_len);
            write_ptr += word_len;
            separator_needed = 1;
        }
    }

    *write_ptr = '\0';

    return result;
}

static char *read_line(FILE *stream, size_t *out_length)
{
    size_t capacity = READ_CHUNK_SIZE;
    size_t length = 0;

    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }
    buffer[0] = '\0';

    for (;;) {
        size_t space = capacity - length;

        if (fgets(buffer + length, (int)space, stream) == NULL) {
            if (length == 0 || ferror(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        length += strnlen(buffer + length, space);

        if (length > 0 && buffer[length - 1] == '\n') {
            length--;
            break;
        }

        if (feof(stream)) {
            break;
        }

        if (capacity > (size_t)INT_MAX / 2u) {
            free(buffer);
            return NULL;
        }

        size_t new_capacity = capacity * 2u;
        char *new_buffer = realloc(buffer, new_capacity);
        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }
        buffer = new_buffer;
        capacity = new_capacity;
    }

    buffer[length] = '\0';

    if (out_length != NULL) {
        *out_length = length;
    }

    return buffer;
}

int main(void)
{
    printf("Enter a string: ");
    fflush(stdout);

    size_t input_length = 0;
    char *input = read_line(stdin, &input_length);
    if (input == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the word length to remove: ");
    fflush(stdout);

    char *number_buffer = read_line(stdin, NULL);
    if (number_buffer == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    const char *check_ptr = number_buffer;
    while (isspace((unsigned char)*check_ptr)) {
        check_ptr++;
    }
    if (*check_ptr == '-' || *check_ptr == '\0') {
        fprintf(stderr, "Error: invalid number.\n");
        free(number_buffer);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr = NULL;
    unsigned long long value = strtoull(check_ptr, &endptr, 10);
    if (errno != 0 || endptr == check_ptr) {
        fprintf(stderr, "Error: invalid number.\n");
        free(number_buffer);
        free(input);
        return EXIT_FAILURE;
    }
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Error: invalid number.\n");
            free(number_buffer);
            free(input);
            return EXIT_FAILURE;
        }
        endptr++;
    }

    size_t k = (size_t)value;
    if ((unsigned long long)k != value) {
        fprintf(stderr, "Error: invalid number.\n");
        free(number_buffer);
        free(input);
        return EXIT_FAILURE;
    }

    free(number_buffer);
    number_buffer = NULL;

    size_t input_size = input_length + 1u;
    char *result = remove_words_of_length(input, input_size, k);
    if (result == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Result: \"%s\"\n", result);

    free(result);
    result = NULL;
    free(input);
    input = NULL;

    return EXIT_SUCCESS;
}