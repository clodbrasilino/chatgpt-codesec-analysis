#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_lowercase_substrings(const char *input)
{
    char *result;
    size_t read_index;
    size_t write_index;
    size_t length;

    if (input == NULL) {
        return NULL;
    }

    length = strlen(input);
    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    write_index = 0U;

    for (read_index = 0U; read_index < length; ++read_index) {
        unsigned char character = (unsigned char)input[read_index];

        if (islower(character) == 0) {
            result[write_index] = input[read_index];
            ++write_index;
        }
    }

    result[write_index] = '\0';

    return result;
}

int main(void)
{
    char input[1024];
    char *result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    input[strcspn(input, "\n")] = '\0';

    result = remove_lowercase_substrings(input);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}