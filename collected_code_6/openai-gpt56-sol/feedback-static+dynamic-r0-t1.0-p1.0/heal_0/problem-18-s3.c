#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_present_characters(const char *source, const char *characters)
{
    unsigned char present[256] = {0};
    size_t source_length;
    size_t write_index = 0;
    char *result;

    if (source == NULL || characters == NULL) {
        return NULL;
    }

    for (const unsigned char *p = (const unsigned char *)characters; *p != '\0'; ++p) {
        present[*p] = 1;
    }

    source_length = strlen(source);

    if (source_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(source_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t read_index = 0; read_index < source_length; ++read_index) {
        unsigned char current = (unsigned char)source[read_index];

        if (present[current] == 0) {
            result[write_index++] = source[read_index];
        }
    }

    result[write_index] = '\0';
    return result;
}

int main(void)
{
    char first[1024];
    char second[1024];
    char *result;

    if (fgets(first, sizeof first, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(first, '\n') == NULL && !feof(stdin)) {
        return EXIT_FAILURE;
    }

    first[strcspn(first, "\n")] = '\0';

    if (fgets(second, sizeof second, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(second, '\n') == NULL && !feof(stdin)) {
        return EXIT_FAILURE;
    }

    second[strcspn(second, "\n")] = '\0';

    result = remove_present_characters(first, second);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}