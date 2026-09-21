#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 64

static bool digit_frequency_valid(const char *number, size_t max_len)
{
    int counts[10] = {0};
    size_t i;
    size_t len = 0U;

    if (number == NULL || max_len == 0U) {
        return false;
    }

    while (len < max_len && number[len] != '\0') {
        len++;
    }

    if (len == 0U || len >= max_len) {
        return false;
    }

    for (i = 0U; i < len; i++) {
        if (!isdigit((unsigned char)number[i])) {
            return false;
        }
        counts[number[i] - '0']++;
    }

    for (i = 0U; i < 10U; i++) {
        if (counts[i] > (int)i) {
            return false;
        }
    }

    return true;
}

static void discard_remaining_input(void)
{
    int ch = 0;
    size_t guard = 0U;

    while (ch != '\n' && ch != EOF && guard < 4096U) {
        ch = getchar();
        guard++;
    }
}

static bool read_line(char *buffer, size_t size)
{
    size_t len = 0U;

    if (buffer == NULL || size < 2U) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }

    buffer[size - 1U] = '\0';

    while (len < size && buffer[len] != '\0') {
        len++;
    }

    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    } else if (len == size - 1U) {
        discard_remaining_input();
    }

    return true;
}

int main(void)
{
    char input[MAX_INPUT];

    memset(input, 0, sizeof(input));

    printf("Enter a number: ");

    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return 1;
    }

    if (!read_line(input, sizeof(input))) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    if (digit_frequency_valid(input, sizeof(input))) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}