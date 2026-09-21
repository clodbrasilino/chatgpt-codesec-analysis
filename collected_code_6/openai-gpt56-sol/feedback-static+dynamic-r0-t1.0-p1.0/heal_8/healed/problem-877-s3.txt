#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { INPUT_CAPACITY = 4096 };

static int compare_chars(const void *left, const void *right)
{
    const unsigned char a = *(const unsigned char *)left;
    const unsigned char b = *(const unsigned char *)right;

    return (a > b) - (a < b);
}

static int discard_line(FILE *stream)
{
    int ch;

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }

    return ch == EOF && ferror(stream) ? -1 : 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            if (used == 0) {
                free(buffer);
                return 0;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used >= INPUT_CAPACITY) {
            if (discard_line(stream) != 0) {
                free(buffer);
                return -1;
            }

            free(buffer);
            return -1;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity = capacity * 2;

            if (new_capacity > INPUT_CAPACITY + 1U) {
                new_capacity = INPUT_CAPACITY + 1U;
            }

            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return 1;
}

static void sort_string(char *string, size_t length)
{
    qsort(string, length, sizeof *string, compare_chars);
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    int status = read_line(stdin, &input, &length);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    sort_string(input, length);

    if (fwrite(input, sizeof *input, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    return EXIT_SUCCESS;
}