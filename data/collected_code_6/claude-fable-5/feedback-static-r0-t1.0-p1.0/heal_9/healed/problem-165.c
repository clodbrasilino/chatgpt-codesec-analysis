#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define BUFFER_SIZE 256

size_t count_position_matches(const char *str, size_t max_len)
{
    size_t count = 0;
    size_t len;
    size_t i;

    if (str == NULL || max_len == 0) {
        return 0;
    }

    len = strnlen(str, max_len);

    for (i = 0; i < len && i < 26; i++) {
        char c = str[i];
        if (c == (char)('a' + i) || c == (char)('A' + i)) {
            count++;
        }
    }

    return count;
}

static int discard_remaining_input(void)
{
    int ch;

    do {
        ch = getchar();
        if (ch == EOF) {
            return -1;
        }
    } while (ch != '\n');

    return 0;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t result;
    size_t len;

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return 1;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        if (discard_remaining_input() != 0 && ferror(stdin)) {
            fprintf(stderr, "Error reading input\n");
            return 1;
        }
    }

    result = count_position_matches(buffer, sizeof(buffer));

    printf("Characters at same position as in alphabet: %zu\n", result);

    return 0;
}