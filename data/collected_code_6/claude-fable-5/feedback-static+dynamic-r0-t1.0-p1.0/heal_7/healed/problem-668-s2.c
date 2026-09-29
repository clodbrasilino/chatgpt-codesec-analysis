#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256U

void squeeze_char(char *str, size_t max_len, char ch);
static void flush_stdin(void);
static int read_line(char *buffer, size_t size);

void squeeze_char(char *str, size_t max_len, char ch)
{
    size_t read_idx;
    size_t write_idx;
    size_t len;

    if ((str == NULL) || (max_len == 0U)) {
        return;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        str[max_len - 1U] = '\0';
        len = max_len - 1U;
    }

    write_idx = 0U;

    for (read_idx = 0U; read_idx < len; read_idx++) {
        if ((str[read_idx] == ch) &&
            (read_idx > 0U) &&
            (str[read_idx - 1U] == ch)) {
            continue;
        }
        str[write_idx] = str[read_idx];
        write_idx++;
    }

    str[write_idx] = '\0';
}

static void flush_stdin(void)
{
    int input_char;

    do {
        input_char = getchar();
    } while ((input_char != EOF) && (input_char != (int)'\n'));
}

static int read_line(char *buffer, size_t size)
{
    size_t len;
    int read_size;

    if ((buffer == NULL) || (size == 0U)) {
        return -1;
    }

    if (size > (size_t)INT_MAX) {
        read_size = INT_MAX;
    } else {
        read_size = (int)size;
    }

    if (fgets(buffer, read_size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1U] = '\0';

    len = strnlen(buffer, size);
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    } else if (len == (size - 1U)) {
        flush_stdin();
    }

    return 0;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char target;
    int input_char;

    printf("Enter a string: ");
    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error reading input string\n");
        return EXIT_FAILURE;
    }

    printf("Enter character to squeeze: ");
    input_char = getchar();
    if (input_char == EOF) {
        fprintf(stderr, "Error reading character\n");
        return EXIT_FAILURE;
    }

    if (input_char != (int)'\n') {
        flush_stdin();
    }

    target = (char)input_char;

    squeeze_char(buffer, sizeof(buffer), target);

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}