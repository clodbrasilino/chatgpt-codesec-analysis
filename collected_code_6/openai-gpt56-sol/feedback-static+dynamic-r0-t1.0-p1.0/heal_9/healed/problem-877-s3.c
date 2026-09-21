#include <stdio.h>
#include <stdlib.h>

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

    do {
        ch = fgetc(stream);
    } while (ch != '\n' && ch != EOF);

    return (ch == EOF && ferror(stream)) ? -1 : 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    char *buffer;
    size_t used = 0;
    int ch;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc((size_t)INPUT_CAPACITY + 1U);
    if (buffer == NULL) {
        return -1;
    }

    while (used < (size_t)INPUT_CAPACITY &&
           (ch = fgetc(stream)) != '\n' &&
           ch != EOF) {
        buffer[used++] = (char)(unsigned char)ch;
    }

    if (used == (size_t)INPUT_CAPACITY) {
        ch = fgetc(stream);

        if (ch != '\n' && ch != EOF) {
            if (discard_line(stream) != 0) {
                free(buffer);
                return -1;
            }

            free(buffer);
            return -1;
        }
    }

    if (ch == EOF) {
        if (ferror(stream)) {
            free(buffer);
            return -1;
        }

        if (used == 0U) {
            free(buffer);
            return 0;
        }
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;

    return 1;
}

static void sort_string(char *string, size_t length)
{
    if (string != NULL && length > 1U) {
        qsort(string, length, sizeof *string, compare_chars);
    }
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