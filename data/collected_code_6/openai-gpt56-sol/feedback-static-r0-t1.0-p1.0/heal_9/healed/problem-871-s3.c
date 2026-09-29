#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 1023U

static bool discard_line(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

static bool read_line(char **line, size_t *length)
{
    if (line == NULL || length == NULL) {
        return false;
    }

    *line = NULL;
    *length = 0U;

    char *buffer = malloc(MAX_INPUT_LENGTH + 2U);
    if (buffer == NULL) {
        return false;
    }

    if (fgets(buffer, (int)(MAX_INPUT_LENGTH + 2U), stdin) == NULL) {
        free(buffer);
        return false;
    }

    size_t used = strlen(buffer);

    if (used > 0U && buffer[used - 1U] == '\n') {
        buffer[--used] = '\0';
    } else if (used > MAX_INPUT_LENGTH) {
        discard_line();
        free(buffer);
        return false;
    } else {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            discard_line();
            free(buffer);
            return false;
        }

        if (ch == EOF && ferror(stdin)) {
            free(buffer);
            return false;
        }
    }

    *line = buffer;
    *length = used;
    return true;
}

static bool are_rotations(const char *first, size_t first_length,
                          const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    for (size_t offset = 0U; offset < first_length; ++offset) {
        size_t index = 0U;

        while (index < first_length &&
               first[(offset + index) % first_length] == second[index]) {
            ++index;
        }

        if (index == first_length) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    size_t first_length = 0U;
    size_t second_length = 0U;

    if (!read_line(&first, &first_length) ||
        !read_line(&second, &second_length)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    bool result = are_rotations(first, first_length, second, second_length);

    free(first);
    free(second);

    if (puts(result ? "Yes" : "No") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}