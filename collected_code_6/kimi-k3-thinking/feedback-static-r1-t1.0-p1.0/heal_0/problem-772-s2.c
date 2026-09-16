#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 1024

char *remove_words_of_length(const char *str, size_t k)
{
    if (str == NULL) {
        return NULL;
    }

    char *result = malloc(strlen(str) + 1);
    if (result == NULL) {
        return NULL;
    }

    const char *read_ptr = str;
    char *write_ptr = result;
    int separator_needed = 0;

    while (*read_ptr != '\0') {
        while (*read_ptr != '\0' && isspace((unsigned char)*read_ptr)) {
            read_ptr++;
        }
        if (*read_ptr == '\0') {
            break;
        }

        const char *word_start = read_ptr;
        while (*read_ptr != '\0' && !isspace((unsigned char)*read_ptr)) {
            read_ptr++;
        }

        size_t word_len = (size_t)(read_ptr - word_start);

        if (word_len != k) {
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
    size_t k = 0;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }
    input[strcspn(input, "\n")] = '\0';

    printf("Enter the word length to remove: ");
    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Error: invalid number.\n");
        return EXIT_FAILURE;
    }

    char *result = remove_words_of_length(input, k);
    if (result == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Result: \"%s\"\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}