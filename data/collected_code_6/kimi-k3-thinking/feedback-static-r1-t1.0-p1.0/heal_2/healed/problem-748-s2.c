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
    size_t result_size;

    if (input == NULL)
        return NULL;

    input_len = strnlen(input, MAX_INPUT_LENGTH + 1);
    if (input_len > MAX_INPUT_LENGTH)
        return NULL;

    capital_count = 0;
    for (read_pos = 0; read_pos < input_len; read_pos++) {
        if (isupper((unsigned char)input[read_pos]) &&
            read_pos > 0 && input[read_pos - 1] != ' ')
            capital_count++;
    }

    if (capital_count > SIZE_MAX - input_len - 1)
        return NULL;
    result_size = input_len + capital_count + 1;

    result = malloc(result_size);
    if (result == NULL)
        return NULL;

    write_pos = 0;
    for (read_pos = 0; read_pos < input_len; read_pos++) {
        if (isupper((unsigned char)input[read_pos]) &&
            read_pos > 0 && input[read_pos - 1] != ' ')
            result[write_pos++] = ' ';
        result[write_pos++] = input[read_pos];
    }
    result[write_pos] = '\0';

    return result;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t nread;
    char *result;

    printf("Enter a string: ");

    nread = getline(&buffer, &buffer_size, stdin);
    if (nread < 0) {
        fprintf(stderr, "Failed to read input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (nread > 0 && buffer[nread - 1] == '\n') {
        buffer[nread - 1] = '\0';
        nread--;
    }

    if ((size_t)nread > MAX_INPUT_LENGTH) {
        fprintf(stderr, "Input too long\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    result = insert_spaces_before_capitals(buffer);
    free(buffer);

    if (result == NULL) {
        fprintf(stderr, "Failed to process the string\n");
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", result);

    free(result);
    return EXIT_SUCCESS;
}