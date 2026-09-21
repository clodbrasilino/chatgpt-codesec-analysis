#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define INPUT_BUFFER_SIZE 1024
#define NUMBER_BUFFER_SIZE 64

char *remove_words_of_length(const char *str, size_t str_size, size_t k)
{
    if (str == NULL || str_size == 0) {
        return NULL;
    }

    size_t str_len = strnlen(str, str_size);

    char *result = malloc(str_len + 1);
    if (result == NULL) {
        return NULL;
    }

    const char *read_ptr = str;
    const char *str_end = str + str_len;
    char *write_ptr = result;
    const size_t capacity = str_len + 1;
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
            size_t needed = word_len + (size_t)separator_needed + 1u;
            if (used > capacity || needed > capacity - used) {
                free(result);
                return NULL;
            }
            if (separator_needed) {
                *write_ptr = ' ';
                write_ptr++;
            }
            memcpy(write_ptr, word_start, word_len);
            write_ptr += word_len;
            separator_needed = 1;
        }
    }
    *write_ptr = '\0';

    return result;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char number_buffer[NUMBER_BUFFER_SIZE];
    size_t k = 0;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }
    input[sizeof(input) - 1] = '\0';

    size_t newline_pos = strcspn(input, "\n");
    if (input[newline_pos] == '\0' && newline_pos == sizeof(input) - 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }
    input[newline_pos] = '\0';

    printf("Enter the word length to remove: ");
    if (fgets(number_buffer, sizeof(number_buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }
    number_buffer[sizeof(number_buffer) - 1] = '\0';

    const char *check_ptr = number_buffer;
    while (isspace((unsigned char)*check_ptr)) {
        check_ptr++;
    }
    if (*check_ptr == '-') {
        fprintf(stderr, "Error: invalid number.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr = NULL;
    unsigned long long value = strtoull(number_buffer, &endptr, 10);
    if (errno != 0 || endptr == number_buffer) {
        fprintf(stderr, "Error: invalid number.\n");
        return EXIT_FAILURE;
    }
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Error: invalid number.\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    k = (size_t)value;
    if ((unsigned long long)k != value) {
        fprintf(stderr, "Error: invalid number.\n");
        return EXIT_FAILURE;
    }

    char *result = remove_words_of_length(input, sizeof(input), k);
    if (result == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Result: \"%s\"\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}