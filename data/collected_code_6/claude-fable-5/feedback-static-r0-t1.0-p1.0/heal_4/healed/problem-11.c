#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256U

static void flush_stdin(void)
{
    int input_char;

    do {
        input_char = fgetc(stdin);
    } while (input_char != '\n' && input_char != EOF);
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size == 0U) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1U] = '\0';

    len = strnlen(buffer, size);
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    } else if (len == size - 1U) {
        flush_stdin();
    }

    return 0;
}

void remove_first_last(char *str, size_t max_len, char ch)
{
    size_t len;
    char *first;
    char *last;
    size_t tail_len;

    if (str == NULL || max_len == 0U) {
        return;
    }

    len = strnlen(str, max_len);
    if (len == 0U || len >= max_len) {
        return;
    }

    first = memchr(str, (int)(unsigned char)ch, len);
    if (first == NULL) {
        return;
    }

    last = strrchr(str, (int)(unsigned char)ch);

    if (last != NULL && last != first) {
        tail_len = len - (size_t)(last - str) - 1U;
        memmove(last, last + 1, tail_len + 1U);
        len -= 1U;
    }

    tail_len = len - (size_t)(first - str) - 1U;
    memmove(first, first + 1, tail_len + 1U);
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

    printf("Enter the character to remove: ");
    input_char = fgetc(stdin);
    if (input_char == EOF || input_char == '\n') {
        fprintf(stderr, "Error reading character\n");
        return EXIT_FAILURE;
    }
    target = (char)input_char;

    remove_first_last(buffer, sizeof(buffer), target);

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}