#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

char *replace_spaces(const char *input)
{
    size_t len;
    size_t space_count;
    size_t new_len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN) {
        return NULL;
    }

    space_count = 0;
    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            space_count++;
        }
    }

    if (space_count > (SIZE_MAX - len - 1) / 2) {
        return NULL;
    }

    new_len = len + (space_count * 2);

    result = malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            result[j] = '%';
            result[j + 1] = '2';
            result[j + 2] = '0';
            j += 3;
        } else {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(int argc, char *argv[])
{
    char buffer[MAX_INPUT_LEN];
    const char *input;
    char *converted;

    if (argc > 1) {
        input = argv[1];
    } else {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Failed to read input\n");
            return EXIT_FAILURE;
        }
        buffer[sizeof(buffer) - 1] = '\0';
        size_t len = strnlen(buffer, sizeof(buffer));
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        input = buffer;
    }

    converted = replace_spaces(input);
    if (converted == NULL) {
        fprintf(stderr, "Failed to replace spaces\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", converted) < 0) {
        free(converted);
        return EXIT_FAILURE;
    }

    free(converted);
    converted = NULL;

    return EXIT_SUCCESS;
}