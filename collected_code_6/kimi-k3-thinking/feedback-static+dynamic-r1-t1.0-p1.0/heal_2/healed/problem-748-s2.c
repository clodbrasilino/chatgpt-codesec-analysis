#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <sys/types.h>

#define MAX_INPUT_LENGTH 65536

char *insert_spaces_before_capitals(const char *input)
{
    char *result;
    size_t input_len;
    size_t capital_count;
    size_t read_pos;
    size_t write_pos;
    size_t alloc_size;

    if (input == NULL)
        return NULL;

    input_len = strnlen(input, MAX_INPUT_LENGTH);

    capital_count = 0;
    for (read_pos = 0; read_pos < input_len; read_pos++) {
        if (read_pos > 0 &&
            isupper((unsigned char)input[read_pos]) &&
            input[read_pos - 1] != ' ') {
            capital_count++;
        }
    }

    if (capital_count > SIZE_MAX - 1 ||
        input_len > SIZE_MAX - capital_count - 1)
        return NULL;

    alloc_size = input_len + capital_count + 1;

    result = malloc(alloc_size);
    if (result == NULL)
        return NULL;

    write_pos = 0;
    for (read_pos = 0; read_pos < input_len; read_pos++) {
        if (read_pos > 0 &&
            isupper((unsigned char)input[read_pos]) &&
            input[read_pos - 1] != ' ') {
            result[write_pos++] = ' ';
        }
        result[write_pos++] = input[read_pos];
    }
    result[write_pos] = '\0';

    return result;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;
    char *result;

    printf("Enter a string: ");

    read_len = getline(&buffer, &buffer_size, stdin);
    if (read_len < 0) {
        fprintf(stderr, "Failed to read input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if ((size_t)read_len > MAX_INPUT_LENGTH) {
        fprintf(stderr, "Input too long\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = insert_spaces_before_capitals(buffer);
    if (result == NULL) {
        fprintf(stderr, "Failed to process the string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", result);

    free(result);
    free(buffer);
    return EXIT_SUCCESS;
}