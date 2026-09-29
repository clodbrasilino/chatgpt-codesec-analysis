#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 256U

void remove_first_last(char *str, char ch)
{
    size_t len;
    size_t tail_len;
    char *first;
    char *last;

    if (str == NULL || ch == '\0') {
        return;
    }

    len = strnlen(str, MAX_BUFFER_SIZE);
    if (len == 0U || len >= MAX_BUFFER_SIZE) {
        return;
    }

    first = strchr(str, (int)ch);
    if (first == NULL) {
        return;
    }

    last = strrchr(str, (int)ch);

    if (last != NULL && last != first) {
        tail_len = strnlen(last + 1, MAX_BUFFER_SIZE - (size_t)(last + 1 - str));
        memmove(last, last + 1, tail_len + 1U);
    }

    tail_len = strnlen(first + 1, MAX_BUFFER_SIZE - (size_t)(first + 1 - str));
    memmove(first, first + 1, tail_len + 1U);
}

int main(void)
{
    char buffer[MAX_BUFFER_SIZE];
    char target;
    int input_char;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input string\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    }

    printf("Enter the character to remove: ");
    input_char = getchar();
    if (input_char == EOF) {
        fprintf(stderr, "Error reading character\n");
        return EXIT_FAILURE;
    }
    target = (char)input_char;

    remove_first_last(buffer, target);

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}