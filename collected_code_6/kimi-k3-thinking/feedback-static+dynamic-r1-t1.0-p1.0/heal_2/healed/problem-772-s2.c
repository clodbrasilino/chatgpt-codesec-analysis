#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 1024

static size_t bounded_strnlen(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

char *remove_words_of_length(const char *str, size_t str_max_len, size_t k)
{
    if (str == NULL || str_max_len == 0) {
        return NULL;
    }

    size_t str_len = bounded_strnlen(str, str_max_len);

    char *result = malloc(str_len + 1);
    if (result == NULL) {
        return NULL;
    }

    const char *read_ptr = str;
    const char *str_end = str + str_len;
    char *write_ptr = result;
    const char *result_end = result + str_len;
    int separator_needed = 0;

    while (read_ptr < str_end) {
        while (read_ptr < str_end && isspace((unsigned char)*read_ptr)) {
            read_ptr++;
        }
        if (read_ptr >= str_end) {
            break;
        }

        const char *word_start = read_ptr;
        while (read_ptr < str_end && !isspace((unsigned char)*read_ptr)) {
            read_ptr++;
        }

        size_t word_len = (size_t)(read_ptr - word_start);

        if (word_len != k) {
            size_t separator_len = separator_needed ? 1u : 0u;
            size_t remaining = (size_t)(result_end - write_ptr);

            if (separator_len > remaining || word_len > remaining - separator_len) {
                break;
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
    char *input = malloc(INPUT_BUFFER_SIZE);
    size_t k = 0;

    if (input == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    if (fgets(input, INPUT_BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        free(input);
        return EXIT_FAILURE;
    }
    input[strcspn(input, "\n")] = '\0';

    printf("Enter the word length to remove: ");
    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Error: invalid number.\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *result = remove_words_of_length(input, INPUT_BUFFER_SIZE, k);
    if (result == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Result: \"%s\"\n", result);

    free(input);
    input = NULL;
    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}